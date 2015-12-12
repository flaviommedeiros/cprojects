switch (a->type) {
	case LSM_AUDIT_DATA_NONE:
		return;
	case LSM_AUDIT_DATA_IPC:
		audit_log_format(ab, " key=%d ", a->u.ipc_id);
		break;
	case LSM_AUDIT_DATA_CAP:
		audit_log_format(ab, " capability=%d ", a->u.cap);
		break;
	case LSM_AUDIT_DATA_PATH: {
		struct inode *inode;

		audit_log_d_path(ab, " path=", &a->u.path);

		inode = d_backing_inode(a->u.path.dentry);
		if (inode) {
			audit_log_format(ab, " dev=");
			audit_log_untrustedstring(ab, inode->i_sb->s_id);
			audit_log_format(ab, " ino=%lu", inode->i_ino);
		}
		break;
	}
	case LSM_AUDIT_DATA_IOCTL_OP: {
		struct inode *inode;

		audit_log_d_path(ab, " path=", &a->u.op->path);

		inode = a->u.op->path.dentry->d_inode;
		if (inode) {
			audit_log_format(ab, " dev=");
			audit_log_untrustedstring(ab, inode->i_sb->s_id);
			audit_log_format(ab, " ino=%lu", inode->i_ino);
		}

		audit_log_format(ab, " ioctlcmd=%hx", a->u.op->cmd);
		break;
	}
	case LSM_AUDIT_DATA_DENTRY: {
		struct inode *inode;

		audit_log_format(ab, " name=");
		audit_log_untrustedstring(ab, a->u.dentry->d_name.name);

		inode = d_backing_inode(a->u.dentry);
		if (inode) {
			audit_log_format(ab, " dev=");
			audit_log_untrustedstring(ab, inode->i_sb->s_id);
			audit_log_format(ab, " ino=%lu", inode->i_ino);
		}
		break;
	}
	case LSM_AUDIT_DATA_INODE: {
		struct dentry *dentry;
		struct inode *inode;

		inode = a->u.inode;
		dentry = d_find_alias(inode);
		if (dentry) {
			audit_log_format(ab, " name=");
			audit_log_untrustedstring(ab,
					 dentry->d_name.name);
			dput(dentry);
		}
		audit_log_format(ab, " dev=");
		audit_log_untrustedstring(ab, inode->i_sb->s_id);
		audit_log_format(ab, " ino=%lu", inode->i_ino);
		break;
	}
	case LSM_AUDIT_DATA_TASK: {
		struct task_struct *tsk = a->u.tsk;
		if (tsk) {
			pid_t pid = task_pid_nr(tsk);
			if (pid) {
				char comm[sizeof(tsk->comm)];
				audit_log_format(ab, " opid=%d ocomm=", pid);
				audit_log_untrustedstring(ab,
				    memcpy(comm, tsk->comm, sizeof(comm)));
			}
		}
		break;
	}
	case LSM_AUDIT_DATA_NET:
		if (a->u.net->sk) {
			struct sock *sk = a->u.net->sk;
			struct unix_sock *u;
			int len = 0;
			char *p = NULL;

			switch (sk->sk_family) {
			case AF_INET: {
				struct inet_sock *inet = inet_sk(sk);

				print_ipv4_addr(ab, inet->inet_rcv_saddr,
						inet->inet_sport,
						"laddr", "lport");
				print_ipv4_addr(ab, inet->inet_daddr,
						inet->inet_dport,
						"faddr", "fport");
				break;
			}
#if IS_ENABLED(CONFIG_IPV6)
			case AF_INET6: {
				struct inet_sock *inet = inet_sk(sk);

				print_ipv6_addr(ab, &sk->sk_v6_rcv_saddr,
						inet->inet_sport,
						"laddr", "lport");
				print_ipv6_addr(ab, &sk->sk_v6_daddr,
						inet->inet_dport,
						"faddr", "fport");
				break;
			}
#endif
			case AF_UNIX:
				u = unix_sk(sk);
				if (u->path.dentry) {
					audit_log_d_path(ab, " path=", &u->path);
					break;
				}
				if (!u->addr)
					break;
				len = u->addr->len-sizeof(short);
				p = &u->addr->name->sun_path[0];
				audit_log_format(ab, " path=");
				if (*p)
					audit_log_untrustedstring(ab, p);
				else
					audit_log_n_hex(ab, p, len);
				break;
			}
		}

		switch (a->u.net->family) {
		case AF_INET:
			print_ipv4_addr(ab, a->u.net->v4info.saddr,
					a->u.net->sport,
					"saddr", "src");
			print_ipv4_addr(ab, a->u.net->v4info.daddr,
					a->u.net->dport,
					"daddr", "dest");
			break;
		case AF_INET6:
			print_ipv6_addr(ab, &a->u.net->v6info.saddr,
					a->u.net->sport,
					"saddr", "src");
			print_ipv6_addr(ab, &a->u.net->v6info.daddr,
					a->u.net->dport,
					"daddr", "dest");
			break;
		}
		if (a->u.net->netif > 0) {
			struct net_device *dev;

			/* NOTE: we always use init's namespace */
			dev = dev_get_by_index(&init_net, a->u.net->netif);
			if (dev) {
				audit_log_format(ab, " netif=%s", dev->name);
				dev_put(dev);
			}
		}
		break;
#ifdef CONFIG_KEYS
	case LSM_AUDIT_DATA_KEY:
		audit_log_format(ab, " key_serial=%u", a->u.key_struct.key);
		if (a->u.key_struct.key_desc) {
			audit_log_format(ab, " key_desc=");
			audit_log_untrustedstring(ab, a->u.key_struct.key_desc);
		}
		break;
#endif
	case LSM_AUDIT_DATA_KMOD:
		audit_log_format(ab, " kmod=");
		audit_log_untrustedstring(ab, a->u.kmod_name);
		break;
	}
