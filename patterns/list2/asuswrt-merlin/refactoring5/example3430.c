#ifdef BCM_VLAN
if ((bp->vlgrp != NULL) && (bp->flags & HW_VLAN_RX_FLAG) &&
		    (le16_to_cpu(cqe->fast_path_cqe.pars_flags.flags) &
		     PARSING_FLAGS_VLAN))
			vlan_gro_receive(&fp->napi, bp->vlgrp,
				le16_to_cpu(cqe->fast_path_cqe.vlan_tag), skb);
		else
#endif
			napi_gro_receive(&fp->napi, skb);
