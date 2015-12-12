if (vfp_state_in_hw(cpu, thread))
		vfp_save_state(&thread->vfpstate, fpexc);
#ifndef CONFIG_SMP
	else if (vfp_current_hw_state[cpu] != NULL)
		vfp_save_state(vfp_current_hw_state[cpu], fpexc);
#endif
