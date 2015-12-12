switch (dlp->dl_primitive) {

	case DL_INFO_ACK:
	case DL_BIND_ACK:
	case DL_OK_ACK:
#ifdef DL_HP_PPA_ACK
	case DL_HP_PPA_ACK:
#endif
		/* These are OK */
		break;

	case DL_ERROR_ACK:
		switch (dlp->error_ack.dl_errno) {

		case DL_SYSERR:
			if (uerror != NULL)
				*uerror = dlp->error_ack.dl_unix_errno;
			pcap_snprintf(ebuf, PCAP_ERRBUF_SIZE,
			    "recv_ack: %s: UNIX error - %s",
			    what, pcap_strerror(dlp->error_ack.dl_unix_errno));
			if (dlp->error_ack.dl_unix_errno == EPERM ||
			    dlp->error_ack.dl_unix_errno == EACCES)
				return (PCAP_ERROR_PERM_DENIED);
			break;

		default:
			pcap_snprintf(ebuf, PCAP_ERRBUF_SIZE, "recv_ack: %s: %s",
			    what, dlstrerror(dlp->error_ack.dl_errno));
			if (dlp->error_ack.dl_errno == DL_BADPPA)
				return (PCAP_ERROR_NO_SUCH_DEVICE);
			else if (dlp->error_ack.dl_errno == DL_ACCESS)
				return (PCAP_ERROR_PERM_DENIED);
			break;
		}
		return (PCAP_ERROR);

	default:
		pcap_snprintf(ebuf, PCAP_ERRBUF_SIZE,
		    "recv_ack: %s: Unexpected primitive ack %s",
		    what, dlprim(dlp->dl_primitive));
		return (PCAP_ERROR);
	}
