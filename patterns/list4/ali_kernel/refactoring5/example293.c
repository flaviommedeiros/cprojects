#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6)
		uhdr->check =
			csum_fold(ip_vs_check_diff16(oldip->ip6, newip->ip6,
					 ip_vs_check_diff2(oldport, newport,
						~csum_unfold(uhdr->check))));
	else
#endif
		uhdr->check =
			csum_fold(ip_vs_check_diff4(oldip->ip, newip->ip,
					 ip_vs_check_diff2(oldport, newport,
						~csum_unfold(uhdr->check))));
