#ifdef BCM_VLAN
if ((bp->vlgrp != NULL) && is_vlan_cqe &&
			    (!is_not_hwaccel_vlan_cqe))
				vlan_gro_receive(&fp->napi, bp->vlgrp,
						 le16_to_cpu(cqe->fast_path_cqe.
							     vlan_tag), skb);
			else
#endif
				napi_gro_receive(&fp->napi, skb);
