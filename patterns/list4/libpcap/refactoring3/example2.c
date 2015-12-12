switch (errno) {

			case EINTR:
				goto again;

#ifdef _AIX
			case EFAULT:
				/*
				 * Sigh.  More AIX wonderfulness.
				 *
				 * For some unknown reason the uiomove()
				 * operation in the bpf kernel extension
				 * used to copy the buffer into user
				 * space sometimes returns EFAULT. I have
				 * no idea why this is the case given that
				 * a kernel debugger shows the user buffer
				 * is correct. This problem appears to
				 * be mostly mitigated by the memset of
				 * the buffer before it is first used.
				 * Very strange.... Shaun Clowes
				 *
				 * In any case this means that we shouldn't
				 * treat EFAULT as a fatal error; as we
				 * don't have an API for returning
				 * a "some packets were dropped since
				 * the last packet you saw" indication,
				 * we just ignore EFAULT and keep reading.
				 */
				goto again;
#endif

			case EWOULDBLOCK:
				return (0);

			case ENXIO:
				/*
				 * The device on which we're capturing
				 * went away.
				 *
				 * XXX - we should really return
				 * PCAP_ERROR_IFACE_NOT_UP, but
				 * pcap_dispatch() etc. aren't
				 * defined to retur that.
				 */
				pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
				    "The interface went down");
				return (PCAP_ERROR);

#if defined(sun) && !defined(BSD) && !defined(__svr4__) && !defined(__SVR4)
			/*
			 * Due to a SunOS bug, after 2^31 bytes, the kernel
			 * file offset overflows and read fails with EINVAL.
			 * The lseek() to 0 will fix things.
			 */
			case EINVAL:
				if (lseek(p->fd, 0L, SEEK_CUR) +
				    p->bufsize < 0) {
					(void)lseek(p->fd, 0L, SEEK_SET);
					goto again;
				}
				/* fall through */
#endif
			}
