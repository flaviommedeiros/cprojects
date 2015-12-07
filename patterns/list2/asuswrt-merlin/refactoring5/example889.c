#ifdef SKY2_VLAN_TAG_USED
if (sky2->vlgrp && (status & GMR_FS_VLAN)) {
				vlan_hwaccel_receive_skb(skb,
							 sky2->vlgrp,
							 be16_to_cpu(sky2->rx_tag));
			} else
#endif
				netif_receive_skb(skb);
