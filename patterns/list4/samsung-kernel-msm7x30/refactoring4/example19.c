#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 31))
if (ifp->net->open)
#else
			if (ifp->net->netdev_ops == &dhd_ops_pri)
#endif
			{
				unregister_netdev(ifp->net);
				free_netdev(ifp->net);
				ifp->net = NULL;
				MFREE(dhd->pub.osh, ifp, sizeof(*ifp));
				dhd->iflist[0] = NULL;
			}
