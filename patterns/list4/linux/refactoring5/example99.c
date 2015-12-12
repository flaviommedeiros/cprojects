#ifdef CONFIG_CRASH_DUMP
if (((struct kimage *) data)->type == KEXEC_TYPE_CRASH) {

		lgr_info_log();
		s390_reset_system(setup_regs, __do_machine_kdump, data);
	} else
#endif
		s390_reset_system(NULL, __do_machine_kexec, data);
