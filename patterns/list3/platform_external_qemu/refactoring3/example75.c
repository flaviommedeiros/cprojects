switch(so->so_emu) {

#ifdef EMULATE_TALK
	 case EMU_TALK:
	 case EMU_NTALK:
		/*
		 * Talk emulation. We always change the ctl_addr to get
		 * some answers from the daemon. When an ANNOUNCE comes,
		 * we send LEAVE_INVITE to the local daemons. Also when a
		 * DELETE comes, we send copies to the local daemons.
		 */
		if (getsockname(so->s, (struct sockaddr *)&addr, &addrlen) < 0)
			return;

#define	IS_OLD	(so->so_emu == EMU_TALK)

#define COPY_MSG(dest, src) { dest->type = src->type; \
			      dest->id_num = src->id_num; \
			      dest->pid = src->pid; \
			      dest->addr = src->addr; \
			      dest->ctl_addr = src->ctl_addr; \
			      memcpy(&dest->l_name, &src->l_name, NAME_SIZE_OLD); \
			      memcpy(&dest->r_name, &src->r_name, NAME_SIZE_OLD); \
	         	      memcpy(&dest->r_tty, &src->r_tty, TTY_SIZE); }

#define OTOSIN(ptr, field) ((struct sockaddr_in *)&ptr->field)
/* old_sockaddr to sockaddr_in */


		if (IS_OLD) {  		/* old talk */
			omsg = mtod(m, CTL_MSG_OLD*);
			nmsg = (CTL_MSG *) buff;
			type = omsg->type;
			OTOSIN(omsg, ctl_addr)->sin_port = addr.sin_port;
			OTOSIN(omsg, ctl_addr)->sin_addr = our_addr;
                        pstrcpy(omsg->l_name, NAME_SIZE_OLD, getlogin());
		} else {		/* new talk */
			omsg = (CTL_MSG_OLD *) buff;
			nmsg = mtod(m, CTL_MSG *);
			type = nmsg->type;
			OTOSIN(nmsg, ctl_addr)->sin_port = addr.sin_port;
			OTOSIN(nmsg, ctl_addr)->sin_addr = our_addr;
                        pstrcpy(nmsg->l_name, NAME_SIZE_OLD, getlogin());
		}

		if (type == LOOK_UP)
			return;		/* for LOOK_UP this is enough */

		if (IS_OLD) {		/* make a copy of the message */
			COPY_MSG(nmsg, omsg);
			nmsg->vers = 1;
			nmsg->answer = 0;
		} else
			COPY_MSG(omsg, nmsg);

		/*
		 * If if is an ANNOUNCE message, we go through the
		 * request table to see if a tcp port has already
		 * been redirected for this socket. If not, we solisten()
		 * a new socket and add this entry to the table.
		 * The port number of the tcp socket and our IP
		 * are put to the addr field of the message structures.
		 * Then a LEAVE_INVITE is sent to both local daemon
		 * ports, 517 and 518. This is why we have two copies
		 * of the message, one in old talk and one in new talk
		 * format.
		 */

		if (type == ANNOUNCE) {
			int s;
			u_short temp_port;

			for(req = req_tbl; req; req = req->next)
				if (so == req->udp_so)
					break;  	/* found it */

			if (!req) {	/* no entry for so, create new */
				req = (struct talk_request *)
					malloc(sizeof(struct talk_request));
				req->udp_so = so;
				req->tcp_so = solisten(0,
					OTOSIN(omsg, addr)->sin_addr.s_addr,
					OTOSIN(omsg, addr)->sin_port,
					SS_FACCEPTONCE);
				req->next = req_tbl;
				req_tbl = req;
			}

			/* replace port number in addr field */
			addrlen = sizeof(addr);
			getsockname(req->tcp_so->s,
					(struct sockaddr *) &addr,
					&addrlen);
			OTOSIN(omsg, addr)->sin_port = addr.sin_port;
			OTOSIN(omsg, addr)->sin_addr = our_addr;
			OTOSIN(nmsg, addr)->sin_port = addr.sin_port;
			OTOSIN(nmsg, addr)->sin_addr = our_addr;

			/* send LEAVE_INVITEs */
			temp_port = OTOSIN(omsg, ctl_addr)->sin_port;
			OTOSIN(omsg, ctl_addr)->sin_port = 0;
			OTOSIN(nmsg, ctl_addr)->sin_port = 0;
			omsg->type = nmsg->type = LEAVE_INVITE;

			s = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
			addr.sin_addr = our_addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(517);
			sendto(s, (char *)omsg, sizeof(*omsg), 0,
				(struct sockaddr *)&addr, sizeof(addr));
			addr.sin_port = htons(518);
			sendto(s, (char *)nmsg, sizeof(*nmsg), 0,
				(struct sockaddr *) &addr, sizeof(addr));
			closesocket(s) ;

			omsg->type = nmsg->type = ANNOUNCE;
			OTOSIN(omsg, ctl_addr)->sin_port = temp_port;
			OTOSIN(nmsg, ctl_addr)->sin_port = temp_port;
		}

		/*
		 * If it is a DELETE message, we send a copy to the
		 * local daemons. Then we delete the entry corresponding
		 * to our socket from the request table.
		 */

		if (type == DELETE) {
			struct talk_request *temp_req, *req_next;
			int s;
			u_short temp_port;

			temp_port = OTOSIN(omsg, ctl_addr)->sin_port;
			OTOSIN(omsg, ctl_addr)->sin_port = 0;
			OTOSIN(nmsg, ctl_addr)->sin_port = 0;

			s = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
			addr.sin_addr = our_addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(517);
			sendto(s, (char *)omsg, sizeof(*omsg), 0,
				(struct sockaddr *)&addr, sizeof(addr));
			addr.sin_port = htons(518);
			sendto(s, (char *)nmsg, sizeof(*nmsg), 0,
				(struct sockaddr *)&addr, sizeof(addr));
			closesocket(s);

			OTOSIN(omsg, ctl_addr)->sin_port = temp_port;
			OTOSIN(nmsg, ctl_addr)->sin_port = temp_port;

			/* delete table entry */
			if (so == req_tbl->udp_so) {
				temp_req = req_tbl;
				req_tbl = req_tbl->next;
				free(temp_req);
			} else {
				temp_req = req_tbl;
				for(req = req_tbl->next; req; req = req_next) {
					req_next = req->next;
					if (so == req->udp_so) {
						temp_req->next = req_next;
						free(req);
						break;
					} else {
						temp_req = req;
					}
				}
			}
		}

		return;
#endif

	case EMU_CUSEEME:

		/*
		 * Cu-SeeMe emulation.
		 * Hopefully the packet is more that 16 bytes long. We don't
		 * do any other tests, just replace the address and port
		 * fields.
		 */
		if (m->m_len >= sizeof (*cu_head)) {
			if (getsockname(so->s, (struct sockaddr *)&addr, &addrlen) < 0)
				return;
			cu_head = mtod(m, struct cu_header *);
			cu_head->s_port = addr.sin_port;
			cu_head->so_addr = our_addr.s_addr;
		}

		return;
	}
