static const struct cpu_dev __cpuinitconst amd_cpu_dev = {
	.c_vendor	= "AMD",
	.c_ident	= { "AuthenticAMD" },
#ifdef CONFIG_X86_32
	.c_models = {
		{ .vendor = X86_VENDOR_AMD, .family = 4, .model_names =
		  {
			  [3] = "486 DX/2",
			  [7] = "486 DX/2-WB",
			  [8] = "486 DX/4",
			  [9] = "486 DX/4-WB",
			  [14] = "Am5x86-WT",
			  [15] = "Am5x86-WB"
		  }
		},
	},
	.c_size_cache	= amd_size_cache,
#endif
	.c_early_init   = early_init_amd,
	.c_detect_tlb	= cpu_detect_tlb_amd,
	.c_bsp_init	= bsp_init_amd,
	.c_init		= init_amd,
	.c_x86_vendor	= X86_VENDOR_AMD,
};
