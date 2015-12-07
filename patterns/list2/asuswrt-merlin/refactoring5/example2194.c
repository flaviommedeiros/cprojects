#ifdef CONFIG_X86_32
if (!enabled_via_apicbase)
		clear_local_APIC();
	else
#endif
		disable_local_APIC();
