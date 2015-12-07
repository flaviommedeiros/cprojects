#ifdef SCTP_EXT
if (likely((cmsg->cmsg_level==IPPROTO_SCTP) &&
						((cmsg->cmsg_type==SCTP_SNDRCV)
						 || (cmsg->cmsg_type==SCTP_EXTRCV)
						) && (cmsg->cmsg_len>=CMSG_LEN(sizeof(*sinfo)))) )
#else  /* !SCTP_EXT -- same as above but w/o SCTP_EXTRCV */
			if (likely((cmsg->cmsg_level==IPPROTO_SCTP) &&
						((cmsg->cmsg_type==SCTP_SNDRCV)
						) && (cmsg->cmsg_len>=CMSG_LEN(sizeof(*sinfo)))) )
#endif /*SCTP_EXT */
			{
				sinfo=(struct sctp_sndrcvinfo*)CMSG_DATA(cmsg);
				DBG("sctp recv: message from %s:%d stream %d  ppid %x"
						" flags %x%s tsn %u" " cumtsn %u assoc_id %d\n",
						ip_addr2a(&ri.src_ip), ri.src_port,
						sinfo->sinfo_stream, sinfo->sinfo_ppid,
						sinfo->sinfo_flags,
						(sinfo->sinfo_flags&SCTP_UNORDERED)?
							" (SCTP_UNORDERED)":"",
						sinfo->sinfo_tsn, sinfo->sinfo_cumtsn, 
						sinfo->sinfo_assoc_id);
				break;
			}
