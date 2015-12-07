if (!of_machine_is_compatible("renesas,emev2") &&
		    !of_machine_is_compatible("renesas,r7s72100") &&
#ifndef CONFIG_PM_GENERIC_DOMAINS_OF
		    !of_machine_is_compatible("renesas,r8a73a4") &&
		    !of_machine_is_compatible("renesas,r8a7740") &&
		    !of_machine_is_compatible("renesas,sh73a0") &&
#endif
		    !of_machine_is_compatible("renesas,r8a7778") &&
		    !of_machine_is_compatible("renesas,r8a7779") &&
		    !of_machine_is_compatible("renesas,r8a7790") &&
		    !of_machine_is_compatible("renesas,r8a7791") &&
		    !of_machine_is_compatible("renesas,r8a7792") &&
		    !of_machine_is_compatible("renesas,r8a7793") &&
		    !of_machine_is_compatible("renesas,r8a7794"))
			return 0;
