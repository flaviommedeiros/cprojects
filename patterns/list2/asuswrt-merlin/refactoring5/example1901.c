#ifdef WPS_UPNP_DEVICE
if (hndl->type == WPS_RECEIVE_PKT_UPNP) {
			/*
			 * We have to know the return code after upnp_dispatch invoke
			 * WFADevice functions, the libupnp_retcode variable will store it.
			 */
			if (upnp_fd_isset(hndl->private, &fdvar)) {
				upnp_dispatch(hndl->private, &fdvar);
				ret_hndl = hndl;
				break;
			}
		}
		else
#endif /* WPS_UPNP_DEVICE */
		if (FD_ISSET(hndl->handle, &fdvar)) {
			/*
			 * Specially hacking eap handle to
			 * retrieve eap wl ifname.
			 */
			num = 0;
			if (hndl->type == WPS_RECEIVE_PKT_EAP) {
				iov[num].iov_base = hndl->ifname;
				iov[num].iov_len = sizeof(hndl->ifname);
				num++;
			}
			iov[num].iov_base = (void *)dataBuffer;
			iov[num].iov_len = *dataLen;

			/* Setup message */
			memset(&dst, 0, sizeof(dst));
			memset(&msg, 0, sizeof(msg));
			msg.msg_name = (void *)&dst;
			msg.msg_namelen = sizeof(dst);
			msg.msg_iov = iov;
			msg.msg_iovlen = num+1;

			/* Read this message */
			bytes = recvmsg(hndl->handle, &msg, 0);
			bytes -= num * sizeof(hndl->ifname);
			if (bytes <= 0) {
				TUTRACE((TUTRACE_ERR,
					"recv failed, recvBytes = %d\n", bytes));
				break;
			}

			*dataLen = bytes;
			ret_hndl = hndl;
			break;
		}
