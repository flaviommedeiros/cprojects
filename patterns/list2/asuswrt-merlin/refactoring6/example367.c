if (
#if !defined(__s390__)
			    probed_ifaces[i].netmask.s_addr != allones_ip.s_addr &&
#endif
			    probed_ifaces[i].ip.s_addr != loopback_ip.s_addr) {
				add_interface(probed_ifaces[i].ip, 
					      probed_ifaces[i].netmask);
			}
