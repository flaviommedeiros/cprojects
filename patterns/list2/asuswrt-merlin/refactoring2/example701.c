#ifdef CONFIG_FB_MSM_MDP31
if ((req->src.format != MDP_Y_CBCR_H2V2) &&
			(req->src.format != MDP_Y_CRCB_H2V2))
#endif
		return -EINVAL;
