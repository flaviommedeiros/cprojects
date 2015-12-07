#ifdef MULTICAST_AVOID
if (lp->promiscuous || (dev->mc_count != lp->mc_count))
#endif
		{
			lp->promiscuous = 0;
			lp->mc_count = dev->mc_count;

			wv_82586_reconfig(dev);
		}
