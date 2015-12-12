switch (cmd) {
	case SIOCGETTUNNEL:
#ifdef CONFIG_IPV6_SIT_6RD
	case SIOCGET6RD:
#endif
		t = NULL;
		if (dev == sitn->fb_tunnel_dev) {
			if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p))) {
				err = -EFAULT;
				break;
			}
			t = ipip6_tunnel_locate(net, &p, 0);
		}
		if (t == NULL)
			t = netdev_priv(dev);

		err = -EFAULT;
		if (cmd == SIOCGETTUNNEL) {
			memcpy(&p, &t->parms, sizeof(p));
			if (copy_to_user(ifr->ifr_ifru.ifru_data, &p,
					 sizeof(p)))
				goto done;
#ifdef CONFIG_IPV6_SIT_6RD
		} else {
			ip6rd.prefix = t->ip6rd.prefix;
			ip6rd.relay_prefix = t->ip6rd.relay_prefix;
			ip6rd.prefixlen = t->ip6rd.prefixlen;
			ip6rd.relay_prefixlen = t->ip6rd.relay_prefixlen;
			if (copy_to_user(ifr->ifr_ifru.ifru_data, &ip6rd,
					 sizeof(ip6rd)))
				goto done;
#endif
		}
		err = 0;
		break;

	case SIOCADDTUNNEL:
	case SIOCCHGTUNNEL:
		err = -EPERM;
		if (!capable(CAP_NET_ADMIN))
			goto done;

		err = -EFAULT;
		if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p)))
			goto done;

		err = -EINVAL;
		if (p.iph.version != 4 || p.iph.protocol != IPPROTO_IPV6 ||
		    p.iph.ihl != 5 || (p.iph.frag_off&htons(~IP_DF)))
			goto done;
		if (p.iph.ttl)
			p.iph.frag_off |= htons(IP_DF);

		t = ipip6_tunnel_locate(net, &p, cmd == SIOCADDTUNNEL);

		if (dev != sitn->fb_tunnel_dev && cmd == SIOCCHGTUNNEL) {
			if (t != NULL) {
				if (t->dev != dev) {
					err = -EEXIST;
					break;
				}
			} else {
				if (((dev->flags&IFF_POINTOPOINT) && !p.iph.daddr) ||
				    (!(dev->flags&IFF_POINTOPOINT) && p.iph.daddr)) {
					err = -EINVAL;
					break;
				}
				t = netdev_priv(dev);
				ipip6_tunnel_unlink(sitn, t);
				synchronize_net();
				t->parms.iph.saddr = p.iph.saddr;
				t->parms.iph.daddr = p.iph.daddr;
				memcpy(dev->dev_addr, &p.iph.saddr, 4);
				memcpy(dev->broadcast, &p.iph.daddr, 4);
				ipip6_tunnel_link(sitn, t);
				netdev_state_change(dev);
			}
		}

		if (t) {
			err = 0;
			if (cmd == SIOCCHGTUNNEL) {
				t->parms.iph.ttl = p.iph.ttl;
				t->parms.iph.tos = p.iph.tos;
				if (t->parms.link != p.link) {
					t->parms.link = p.link;
					ipip6_tunnel_bind_dev(dev);
					netdev_state_change(dev);
				}
			}
			if (copy_to_user(ifr->ifr_ifru.ifru_data, &t->parms, sizeof(p)))
				err = -EFAULT;
		} else
			err = (cmd == SIOCADDTUNNEL ? -ENOBUFS : -ENOENT);
		break;

	case SIOCDELTUNNEL:
		err = -EPERM;
		if (!capable(CAP_NET_ADMIN))
			goto done;

		if (dev == sitn->fb_tunnel_dev) {
			err = -EFAULT;
			if (copy_from_user(&p, ifr->ifr_ifru.ifru_data, sizeof(p)))
				goto done;
			err = -ENOENT;
			if ((t = ipip6_tunnel_locate(net, &p, 0)) == NULL)
				goto done;
			err = -EPERM;
			if (t == netdev_priv(sitn->fb_tunnel_dev))
				goto done;
			dev = t->dev;
		}
		unregister_netdevice(dev);
		err = 0;
		break;

	case SIOCGETPRL:
		err = -EINVAL;
		if (dev == sitn->fb_tunnel_dev)
			goto done;
		err = -ENOENT;
		if (!(t = netdev_priv(dev)))
			goto done;
		err = ipip6_tunnel_get_prl(t, ifr->ifr_ifru.ifru_data);
		break;

	case SIOCADDPRL:
	case SIOCDELPRL:
	case SIOCCHGPRL:
		err = -EPERM;
		if (!capable(CAP_NET_ADMIN))
			goto done;
		err = -EINVAL;
		if (dev == sitn->fb_tunnel_dev)
			goto done;
		err = -EFAULT;
		if (copy_from_user(&prl, ifr->ifr_ifru.ifru_data, sizeof(prl)))
			goto done;
		err = -ENOENT;
		if (!(t = netdev_priv(dev)))
			goto done;

		switch (cmd) {
		case SIOCDELPRL:
			err = ipip6_tunnel_del_prl(t, &prl);
			break;
		case SIOCADDPRL:
		case SIOCCHGPRL:
			err = ipip6_tunnel_add_prl(t, &prl, cmd == SIOCCHGPRL);
			break;
		}
		netdev_state_change(dev);
		break;

#ifdef CONFIG_IPV6_SIT_6RD
	case SIOCADD6RD:
	case SIOCCHG6RD:
	case SIOCDEL6RD:
		err = -EPERM;
		if (!capable(CAP_NET_ADMIN))
			goto done;

		err = -EFAULT;
		if (copy_from_user(&ip6rd, ifr->ifr_ifru.ifru_data,
				   sizeof(ip6rd)))
			goto done;

		t = netdev_priv(dev);

		if (cmd != SIOCDEL6RD) {
			struct in6_addr prefix;
			__be32 relay_prefix;

			err = -EINVAL;
			if (ip6rd.relay_prefixlen > 32 ||
			    ip6rd.prefixlen + (32 - ip6rd.relay_prefixlen) > 64)
				goto done;

			ipv6_addr_prefix(&prefix, &ip6rd.prefix,
					 ip6rd.prefixlen);
			if (!ipv6_addr_equal(&prefix, &ip6rd.prefix))
				goto done;
			if (ip6rd.relay_prefixlen)
				relay_prefix = ip6rd.relay_prefix &
					       htonl(0xffffffffUL <<
						     (32 - ip6rd.relay_prefixlen));
			else
				relay_prefix = 0;
			if (relay_prefix != ip6rd.relay_prefix)
				goto done;

			t->ip6rd.prefix = prefix;
			t->ip6rd.relay_prefix = relay_prefix;
			t->ip6rd.prefixlen = ip6rd.prefixlen;
			t->ip6rd.relay_prefixlen = ip6rd.relay_prefixlen;
		} else
			ipip6_tunnel_clone_6rd(dev, sitn);

		err = 0;
		break;
#endif

	default:
		err = -EINVAL;
	}
