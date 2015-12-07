#ifdef CONFIG_KEXEC_JUMP
if (kexec_image->preserve_context) {
		mutex_lock(&pm_mutex);
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
		 * but *not* dpm_suspend_noirq(). We *must* call
		 * dpm_suspend_noirq() now.  Otherwise, drivers for
		 * some devices (e.g. interrupt controllers) become
		 * desynchronized with the actual state of the
		 * hardware at resume time, and evil weirdness ensues.
		 */
		error = dpm_suspend_noirq(PMSG_FREEZE);
		if (error)
			goto Resume_devices;
		error = disable_nonboot_cpus();
		if (error)
			goto Enable_cpus;
		local_irq_disable();
		/* Suspend system devices */
		error = sysdev_suspend(PMSG_FREEZE);
		if (error)
			goto Enable_irqs;
	} else
#endif
	{
		kernel_restart_prepare(NULL);
		printk(KERN_EMERG "Starting new kernel\n");
		machine_shutdown();
	}
