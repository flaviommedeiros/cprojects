switch (optname) {
	case MRT_INIT:
		if (optlen != sizeof(int))
			return -EINVAL;

		rtnl_lock();
		if (rtnl_dereference(mrt->mroute_sk)) {
			rtnl_unlock();
			return -EADDRINUSE;
		}

		ret = ip_ra_control(sk, 1, mrtsock_destruct);
		if (ret == 0) {
			rcu_assign_pointer(mrt->mroute_sk, sk);
			IPV4_DEVCONF_ALL(net, MC_FORWARDING)++;
			inet_netconf_notify_devconf(net, NETCONFA_MC_FORWARDING,
						    NETCONFA_IFINDEX_ALL,
						    net->ipv4.devconf_all);
		}
		rtnl_unlock();
		return ret;
	case MRT_DONE:
		if (sk != rcu_access_pointer(mrt->mroute_sk))
			return -EACCES;
		return ip_ra_control(sk, 0, NULL);
	case MRT_ADD_VIF:
	case MRT_DEL_VIF:
		if (optlen != sizeof(vif))
			return -EINVAL;
		if (copy_from_user(&vif, optval, sizeof(vif)))
			return -EFAULT;
		if (vif.vifc_vifi >= MAXVIFS)
			return -ENFILE;
		rtnl_lock();
		if (optname == MRT_ADD_VIF) {
			ret = vif_add(net, mrt, &vif,
				      sk == rtnl_dereference(mrt->mroute_sk));
		} else {
			ret = vif_delete(mrt, vif.vifc_vifi, 0, NULL);
		}
		rtnl_unlock();
		return ret;

		/*
		 *	Manipulate the forwarding caches. These live
		 *	in a sort of kernel/user symbiosis.
		 */
	case MRT_ADD_MFC:
	case MRT_DEL_MFC:
		parent = -1;
	case MRT_ADD_MFC_PROXY:
	case MRT_DEL_MFC_PROXY:
		if (optlen != sizeof(mfc))
			return -EINVAL;
		if (copy_from_user(&mfc, optval, sizeof(mfc)))
			return -EFAULT;
		if (parent == 0)
			parent = mfc.mfcc_parent;
		rtnl_lock();
		if (optname == MRT_DEL_MFC || optname == MRT_DEL_MFC_PROXY)
			ret = ipmr_mfc_delete(mrt, &mfc, parent);
		else
			ret = ipmr_mfc_add(net, mrt, &mfc,
					   sk == rtnl_dereference(mrt->mroute_sk),
					   parent);
		rtnl_unlock();
		return ret;
		/*
		 *	Control PIM assert.
		 */
	case MRT_ASSERT:
	{
		int v;
		if (optlen != sizeof(v))
			return -EINVAL;
		if (get_user(v, (int __user *)optval))
			return -EFAULT;
		mrt->mroute_do_assert = v;
		return 0;
	}
#ifdef CONFIG_IP_PIMSM
	case MRT_PIM:
	{
		int v;

		if (optlen != sizeof(v))
			return -EINVAL;
		if (get_user(v, (int __user *)optval))
			return -EFAULT;
		v = !!v;

		rtnl_lock();
		ret = 0;
		if (v != mrt->mroute_do_pim) {
			mrt->mroute_do_pim = v;
			mrt->mroute_do_assert = v;
		}
		rtnl_unlock();
		return ret;
	}
#endif
#ifdef CONFIG_IP_MROUTE_MULTIPLE_TABLES
	case MRT_TABLE:
	{
		u32 v;

		if (optlen != sizeof(u32))
			return -EINVAL;
		if (get_user(v, (u32 __user *)optval))
			return -EFAULT;

		/* "pimreg%u" should not exceed 16 bytes (IFNAMSIZ) */
		if (v != RT_TABLE_DEFAULT && v >= 1000000000)
			return -EINVAL;

		rtnl_lock();
		ret = 0;
		if (sk == rtnl_dereference(mrt->mroute_sk)) {
			ret = -EBUSY;
		} else {
			if (!ipmr_new_table(net, v))
				ret = -ENOMEM;
			else
				raw_sk(sk)->ipmr_table = v;
		}
		rtnl_unlock();
		return ret;
	}
#endif
	/*
	 *	Spurious command, or MRT_VERSION which you cannot
	 *	set.
	 */
	default:
		return -ENOPROTOOPT;
	}
