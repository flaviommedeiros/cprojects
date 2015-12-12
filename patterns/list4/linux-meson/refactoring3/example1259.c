switch (optname) {
	case NETLINK_PKTINFO:
		if (val)
			nlk->flags |= NETLINK_RECV_PKTINFO;
		else
			nlk->flags &= ~NETLINK_RECV_PKTINFO;
		err = 0;
		break;
	case NETLINK_ADD_MEMBERSHIP:
	case NETLINK_DROP_MEMBERSHIP: {
		if (!netlink_capable(sock, NL_CFG_F_NONROOT_RECV))
			return -EPERM;
		err = netlink_realloc_groups(sk);
		if (err)
			return err;
		if (!val || val - 1 >= nlk->ngroups)
			return -EINVAL;
		netlink_table_grab();
		netlink_update_socket_mc(nlk, val,
					 optname == NETLINK_ADD_MEMBERSHIP);
		netlink_table_ungrab();

		if (nlk->netlink_bind)
			nlk->netlink_bind(val);

		err = 0;
		break;
	}
	case NETLINK_BROADCAST_ERROR:
		if (val)
			nlk->flags |= NETLINK_BROADCAST_SEND_ERROR;
		else
			nlk->flags &= ~NETLINK_BROADCAST_SEND_ERROR;
		err = 0;
		break;
	case NETLINK_NO_ENOBUFS:
		if (val) {
			nlk->flags |= NETLINK_RECV_NO_ENOBUFS;
			clear_bit(NETLINK_CONGESTED, &nlk->state);
			wake_up_interruptible(&nlk->wait);
		} else {
			nlk->flags &= ~NETLINK_RECV_NO_ENOBUFS;
		}
		err = 0;
		break;
#ifdef CONFIG_NETLINK_MMAP
	case NETLINK_RX_RING:
	case NETLINK_TX_RING: {
		struct nl_mmap_req req;

		/* Rings might consume more memory than queue limits, require
		 * CAP_NET_ADMIN.
		 */
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
		if (optlen < sizeof(req))
			return -EINVAL;
		if (copy_from_user(&req, optval, sizeof(req)))
			return -EFAULT;
		err = netlink_set_ring(sk, &req, false,
				       optname == NETLINK_TX_RING);
		break;
	}
#endif /* CONFIG_NETLINK_MMAP */
	default:
		err = -ENOPROTOOPT;
	}
