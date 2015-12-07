#ifdef BCM_VLAN
if (hw_vlan)
			vlan_gro_receive(&bnapi->napi, bp->vlgrp, vtag, skb);
		else
#endif
			napi_gro_receive(&bnapi->napi, skb);
