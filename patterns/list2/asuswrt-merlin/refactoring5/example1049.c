#ifdef CONFIG_IA32_EMULATION
if (test_thread_flag(TIF_IA32))
			err = ia32_child_tls(p, childregs); 
		else 			
#endif	 
			err = do_arch_prctl(p, ARCH_SET_FS, childregs->r8);
