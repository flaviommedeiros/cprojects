#ifdef CONFIG_X86_PAE
if (!test_cpu_cap(c, X86_FEATURE_NX))
#endif
			clear_cpu_cap(c, X86_FEATURE_SEP);
