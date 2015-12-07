#ifdef MDP4_NONBLOCKING
if (mfd->panel_power_on)
#else
		if (!mfd->dma->busy && mfd->panel_power_on)
#endif
			mdp4_mddi_overlay_kickoff(mfd, pipe);
