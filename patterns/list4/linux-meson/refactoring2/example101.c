#ifdef CONFIG_VSX
if (!cpu_has_feature(CPU_FTR_VSX))
#endif
		{
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			return RESUME_GUEST;
		}
