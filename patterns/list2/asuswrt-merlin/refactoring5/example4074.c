#ifndef RTCONFIG_BCM7
if (nvram_match("asus_tweak", "1")) {	/* dbg ref ? */
				f_write_string("/proc/irq/179/smp_affinity", "1", 0, 0);	// eth0
				f_write_string("/proc/irq/163/smp_affinity", "2", 0, 0);	// eth1 or eth1/eth2
				f_write_string("/proc/irq/169/smp_affinity", "2", 0, 0);	// eth2 or eth3
			} else
#endif	// RTCONFIG_BCM7
				tweak_smp_affinity(0);
