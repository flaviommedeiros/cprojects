int cps_pm_enter_state(enum cps_pm_state state)
{
	unsigned cpu = smp_processor_id();
	unsigned core = current_cpu_data.core;
	unsigned online, left;
	cpumask_t *coupled_mask = this_cpu_ptr(&online_coupled);
	u32 *core_ready_count, *nc_core_ready_count;
	void *nc_addr;
	cps_nc_entry_fn entry;
	struct core_boot_config *core_cfg;
	struct vpe_boot_config *vpe_cfg;

	/* Check that there is an entry function for this state */
	entry = per_cpu(nc_asm_enter, core)[state];
	if (!entry)
		return -EINVAL;

	/* Calculate which coupled CPUs (VPEs) are online */
#ifdef CONFIG_MIPS_MT
	if (cpu_online(cpu)) {
		cpumask_and(coupled_mask, cpu_online_mask,
			    &cpu_sibling_map[cpu]);
		online = cpumask_weight(coupled_mask);
		cpumask_clear_cpu(cpu, coupled_mask);
	} else
#endif
	{
		cpumask_clear(coupled_mask);
		online = 1;
	}

	/* Setup the VPE to run mips_cps_pm_restore when started again */
	if (config_enabled(CONFIG_CPU_PM) && state == CPS_PM_POWER_GATED) {
		/* Power gating relies upon CPS SMP */
		if (!mips_cps_smp_in_use())
			return -EINVAL;

		core_cfg = &mips_cps_core_bootcfg[core];
		vpe_cfg = &core_cfg->vpe_config[cpu_vpe_id(&current_cpu_data)];
		vpe_cfg->pc = (unsigned long)mips_cps_pm_restore;
		vpe_cfg->gp = (unsigned long)current_thread_info();
		vpe_cfg->sp = 0;
	}

	/* Indicate that this CPU might not be coherent */
	cpumask_clear_cpu(cpu, &cpu_coherent_mask);
	smp_mb__after_atomic();

	/* Create a non-coherent mapping of the core ready_count */
	core_ready_count = per_cpu(ready_count, core);
	nc_addr = kmap_noncoherent(virt_to_page(core_ready_count),
				   (unsigned long)core_ready_count);
	nc_addr += ((unsigned long)core_ready_count & ~PAGE_MASK);
	nc_core_ready_count = nc_addr;

	/* Ensure ready_count is zero-initialised before the assembly runs */
	ACCESS_ONCE(*nc_core_ready_count) = 0;
	coupled_barrier(&per_cpu(pm_barrier, core), online);

	/* Run the generated entry code */
	left = entry(online, nc_core_ready_count);

	/* Remove the non-coherent mapping of ready_count */
	kunmap_noncoherent();

	/* Indicate that this CPU is definitely coherent */
	cpumask_set_cpu(cpu, &cpu_coherent_mask);

	/*
	 * If this VPE is the first to leave the non-coherent wait state then
	 * it needs to wake up any coupled VPEs still running their wait
	 * instruction so that they return to cpuidle, which can then complete
	 * coordination between the coupled VPEs & provide the governor with
	 * a chance to reflect on the length of time the VPEs were in the
	 * idle state.
	 */
	if (coupled_coherence && (state == CPS_PM_NC_WAIT) && (left == online))
		arch_send_call_function_ipi_mask(coupled_mask);

	return 0;
}
