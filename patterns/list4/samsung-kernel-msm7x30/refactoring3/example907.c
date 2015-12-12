switch (optname) {
	case MRT_INIT:
		if (sk->sk_type != SOCK_RAW ||
		    inet_sk(sk)->inet_num != IPPROTO_IGMP)
			return -EOPNOTSUPP;
		if (optlen != sizeof(int))
			return -ENOPROTOOPT;

		rtnl_lock();
		if (rtnl_dereference(mrt->mroute_sk)) {
			rtnl_unlock();
			return -EADDRINUSE;
		}

		ret = ip_ra_control(sk, 1, mrtsock_destruct);
		if (ret == 0) {
			rcu_assign_pointer(mrt->mroute_sk, sk);
			IPV4_DEVCONF_ALL(net, MC_FORWARDING)++;
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
		if (optlen != sizeof(mfc))
			return -EINVAL;
		if (copy_from_user(&mfc, optval, sizeof(mfc)))
			return -EFAULT;
		rtnl_lock();
		if (optname == MRT_DEL_MFC)
			ret = ipmr_mfc_delete(mrt, &mfc);
		else
			ret = ipmr_mfc_add(net, mrt, &mfc,
					   sk == rtnl_dereference(mrt->mroute_sk));
		rtnl_unlock();
		return ret;
		/*
		 *	Control PIM assert.
		 */
	case MRT_ASSERT:
	{
		int v;
		if (get_user(v, (int __user *)optval))
			return -EFAULT;
		mrt->mroute_do_assert = (v) ? 1 : 0;
		return 0;
	}
#ifdef CONFIG_IP_PIMSM
	case MRT_PIM:
	{
		int v;

		if (get_user(v, (int __user *)optval))
			return -EFAULT;
		v = (v) ? 1 : 0;

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

		rtnl_lock();
		ret = 0;
		if (sk == rtnl_dereference(mrt->mroute_sk)) {
			ret = -EBUSY;
		} else {
			if (!ipmr_new_table(net, v))
				ret = -ENOMEM;
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
