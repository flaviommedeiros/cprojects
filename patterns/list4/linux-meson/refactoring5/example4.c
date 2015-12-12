#ifdef CONFIG_KEXEC_JUMP
if (kexec_image->preserve_context) {
		lock_system_sleep();
		pm_prepare_console();
		error = freeze_processes();
		if (error) {
			error = -EBUSY;
			goto Restore_console;
		}
		suspend_console();
		error = dpm_suspend_start(PMSG_FREEZE);
		if (error)
			goto Resume_console;
		/* At this point, dpm_suspend_start() has been called,
		 * but *not* dpm_suspend_end(). We *must* call
		 * dpm_suspend_end() now.  Otherwise, drivers for
		 * some devices (e.g. interrupt controllers) become
		 * desynchronized with the actual state of the
		 * hardware at resume time, and evil weirdness ensues.
		 */
		error = dpm_suspend_end(PMSG_FREEZE);
		if (error)
			goto Resume_devices;
		error = disable_nonboot_cpus();
		if (error)
			goto Enable_cpus;
		local_irq_disable();
		error = syscore_suspend();
		if (error)
			goto Enable_irqs;
	} else
#endif
	{
		kexec_in_progress = true;
		kernel_restart_prepare(NULL);
		printk(KERN_EMERG "Starting new kernel\n");
		machine_shutdown();
	}
