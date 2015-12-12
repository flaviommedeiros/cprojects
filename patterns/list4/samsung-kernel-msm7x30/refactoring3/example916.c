switch (optname) {
	case MRT6_INIT:
		if (sk->sk_type != SOCK_RAW ||
		    inet_sk(sk)->inet_num != IPPROTO_ICMPV6)
			return -EOPNOTSUPP;
		if (optlen < sizeof(int))
			return -EINVAL;

		return ip6mr_sk_init(mrt, sk);

	case MRT6_DONE:
		return ip6mr_sk_done(sk);

	case MRT6_ADD_MIF:
		if (optlen < sizeof(vif))
			return -EINVAL;
		if (copy_from_user(&vif, optval, sizeof(vif)))
			return -EFAULT;
		if (vif.mif6c_mifi >= MAXMIFS)
			return -ENFILE;
		rtnl_lock();
		ret = mif6_add(net, mrt, &vif, sk == mrt->mroute6_sk);
		rtnl_unlock();
		return ret;

	case MRT6_DEL_MIF:
		if (optlen < sizeof(mifi_t))
			return -EINVAL;
		if (copy_from_user(&mifi, optval, sizeof(mifi_t)))
			return -EFAULT;
		rtnl_lock();
		ret = mif6_delete(mrt, mifi, NULL);
		rtnl_unlock();
		return ret;

	/*
	 *	Manipulate the forwarding caches. These live
	 *	in a sort of kernel/user symbiosis.
	 */
	case MRT6_ADD_MFC:
	case MRT6_DEL_MFC:
		if (optlen < sizeof(mfc))
			return -EINVAL;
		if (copy_from_user(&mfc, optval, sizeof(mfc)))
			return -EFAULT;
		rtnl_lock();
		if (optname == MRT6_DEL_MFC)
			ret = ip6mr_mfc_delete(mrt, &mfc);
		else
			ret = ip6mr_mfc_add(net, mrt, &mfc, sk == mrt->mroute6_sk);
		rtnl_unlock();
		return ret;

	/*
	 *	Control PIM assert (to activate pim will activate assert)
	 */
	case MRT6_ASSERT:
	{
		int v;
		if (get_user(v, (int __user *)optval))
			return -EFAULT;
		mrt->mroute_do_assert = !!v;
		return 0;
	}

#ifdef CONFIG_IPV6_PIMSM_V2
	case MRT6_PIM:
	{
		int v;
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
#ifdef CONFIG_IPV6_MROUTE_MULTIPLE_TABLES
	case MRT6_TABLE:
	{
		u32 v;

		if (optlen != sizeof(u32))
			return -EINVAL;
		if (get_user(v, (u32 __user *)optval))
			return -EFAULT;
		if (sk == mrt->mroute6_sk)
			return -EBUSY;

		rtnl_lock();
		ret = 0;
		if (!ip6mr_new_table(net, v))
			ret = -ENOMEM;
		raw6_sk(sk)->ip6mr_table = v;
		rtnl_unlock();
		return ret;
	}
#endif
	/*
	 *	Spurious command, or MRT6_VERSION which you cannot
	 *	set.
	 */
	default:
		return -ENOPROTOOPT;
	}
