switch (optname) {
	case MRT_INIT:
		if (sk->sk_type != SOCK_RAW ||
		    inet_sk(sk)->num != IPPROTO_IGMP)
			return -EOPNOTSUPP;
		if (optlen != sizeof(int))
			return -ENOPROTOOPT;

		rtnl_lock();
		if (net->ipv4.mroute_sk) {
			rtnl_unlock();
			return -EADDRINUSE;
		}

		ret = ip_ra_control(sk, 1, mrtsock_destruct);
		if (ret == 0) {
			write_lock_bh(&mrt_lock);
			net->ipv4.mroute_sk = sk;
			write_unlock_bh(&mrt_lock);

			IPV4_DEVCONF_ALL(net, MC_FORWARDING)++;
		}
		rtnl_unlock();
		return ret;
	case MRT_DONE:
		if (sk != net->ipv4.mroute_sk)
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
			ret = vif_add(net, &vif, sk == net->ipv4.mroute_sk);
		} else {
			ret = vif_delete(net, vif.vifc_vifi, 0);
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
			ret = ipmr_mfc_delete(net, &mfc);
		else
			ret = ipmr_mfc_add(net, &mfc, sk == net->ipv4.mroute_sk);
		rtnl_unlock();
		return ret;
		/*
		 *	Control PIM assert.
		 */
	case MRT_ASSERT:
	{
		int v;
		if (get_user(v,(int __user *)optval))
			return -EFAULT;
		net->ipv4.mroute_do_assert = (v) ? 1 : 0;
		return 0;
	}
#ifdef CONFIG_IP_PIMSM
	case MRT_PIM:
	{
		int v;

		if (get_user(v,(int __user *)optval))
			return -EFAULT;
		v = (v) ? 1 : 0;

		rtnl_lock();
		ret = 0;
		if (v != net->ipv4.mroute_do_pim) {
			net->ipv4.mroute_do_pim = v;
			net->ipv4.mroute_do_assert = v;
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
