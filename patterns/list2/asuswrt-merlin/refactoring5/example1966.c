#ifdef BCM_VLAN
if (bp->vlgrp)
				hw_vlan = 1;
			else
#endif
			{
				struct vlan_ethhdr *ve = (struct vlan_ethhdr *)
					__skb_push(skb, 4);

				memmove(ve, skb->data + 4, ETH_ALEN * 2);
				ve->h_vlan_proto = htons(ETH_P_8021Q);
				ve->h_vlan_TCI = htons(vtag);
				len += 4;
			}
