switch (inst->log_dst) {
	case LINELOG_DST_FILE:
	{
		char path[2048];

		if (radius_xlat(path, sizeof(path), request, inst->file.name, inst->file.escape_func, NULL) < 0) {
			return RLM_MODULE_FAIL;
		}

		/* check path and eventually create subdirs */
		p = strrchr(path, '/');
		if (p) {
			*p = '\0';
			if (rad_mkdir(path, 0700, -1, -1) < 0) {
				RERROR("Failed to create directory %s: %s", path, fr_syserror(errno));
				rcode = RLM_MODULE_FAIL;
				goto finish;
			}
			*p = '/';
		}

		fd = exfile_open(inst->file.ef, path, inst->file.permissions, true);
		if (fd < 0) {
			RERROR("Failed to open %s: %s", path, fr_syserror(errno));
			rcode = RLM_MODULE_FAIL;
			goto finish;
		}

		if (inst->file.group_str && (chown(path, -1, inst->file.group) == -1)) {
			RWARN("Unable to change system group of \"%s\": %s", path, fr_strerror());
		}

		if (writev(fd, vector_p, vector_len) < 0) {
			RERROR("Failed writing to \"%s\": %s", path, fr_syserror(errno));
			exfile_close(inst->file.ef, fd);

			/* Assert on the extra fatal errors */
			rad_assert((errno != EINVAL) && (errno != EFAULT));

			return RLM_MODULE_FAIL;
		}

		exfile_close(inst->file.ef, fd);
	}
		break;

	case LINELOG_DST_UNIX:
		if (inst->unix_sock.timeout.tv_sec || inst->unix_sock.timeout.tv_usec) {
			timeout = &inst->unix_sock.timeout;
		}
		goto do_write;

	case LINELOG_DST_UDP:
		if (inst->udp.timeout.tv_sec || inst->udp.timeout.tv_usec) timeout = &inst->udp.timeout;
		goto do_write;

	case LINELOG_DST_TCP:
	{
		int i, num;
		if (inst->tcp.timeout.tv_sec || inst->tcp.timeout.tv_usec) timeout = &inst->tcp.timeout;

	do_write:
		num = fr_connection_pool_state(inst->pool)->num;
		conn = fr_connection_get(inst->pool);
		if (!conn) {
			rcode = RLM_MODULE_FAIL;
			goto finish;
		}

		for (i = num; i >= 0; i--) {
			ssize_t wrote;
			char discard[64];

			wrote = fr_writev(conn->sockfd, vector_p, vector_len, timeout);
			if (wrote < 0) switch (errno) {
			/* Errors that indicate we should reconnect */
			case EDESTADDRREQ:
			case EPIPE:
			case EBADF:
			case ECONNRESET:
			case ENETDOWN:
			case ENETUNREACH:
			case EADDRNOTAVAIL: /* Which is OSX for outbound interface is down? */
				RWARN("Failed writing to socket: %s.  Will reconnect and try again...",
				      fr_syserror(errno));
				conn = fr_connection_reconnect(inst->pool, conn);
				if (!conn) {
					rcode = RLM_MODULE_FAIL;
					goto done;
				}
				continue;

			/* Assert on the extra fatal errors */
			case EINVAL:
			case EFAULT:
				rad_assert(0);
				/* FALL-THROUGH */

			/* Normal errors that just cause the module to fail */
			default:
				RERROR("Failed writing to socket: %s", fr_syserror(errno));
				rcode = RLM_MODULE_FAIL;
				goto done;
			}
			RDEBUG2("Wrote %zi bytes", wrote);

			/* Drain the receive buffer */
			while (read(conn->sockfd, discard, sizeof(discard)) > 0);
			break;
		}
	done:
		fr_connection_release(inst->pool, conn);
	}
		break;

#ifdef HAVE_SYSLOG_H
	case LINELOG_DST_SYSLOG:
	{
		size_t i;

		for (i = 0; i < vector_len; i++) {
			syslog(inst->syslog.priority, "%.*s", (int)vector_p[i].iov_len, (char *)vector_p[i].iov_base);
		}
	}
		break;
#endif
	case LINELOG_DST_INVALID:
		rad_assert(0);
		rcode = RLM_MODULE_FAIL;
		break;
	}
