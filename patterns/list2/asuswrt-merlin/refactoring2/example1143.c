#ifdef MULTICAST_AVOID
if(lp->promiscuous || lp->allmulticast ||
	     (dev->mc_count != lp->mc_count))
#endif
	    {
	      lp->promiscuous = 0;
	      lp->allmulticast = 0;
	      lp->mc_count = dev->mc_count;

	      wv_82593_reconfig(dev);
	    }
