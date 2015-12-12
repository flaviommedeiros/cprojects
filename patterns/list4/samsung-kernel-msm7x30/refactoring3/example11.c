switch (remcom_in_buffer[1]) {
	case 's':
	case 'f':
		if (memcmp(remcom_in_buffer + 2, "ThreadInfo", 10))
			break;

		i = 0;
		remcom_out_buffer[0] = 'm';
		ptr = remcom_out_buffer + 1;
		if (remcom_in_buffer[1] == 'f') {
			/* Each cpu is a shadow thread */
			for_each_online_cpu(cpu) {
				ks->thr_query = 0;
				int_to_threadref(thref, -cpu - 2);
				ptr = pack_threadid(ptr, thref);
				*(ptr++) = ',';
				i++;
			}
		}

		do_each_thread(g, p) {
			if (i >= ks->thr_query && !finished) {
				int_to_threadref(thref, p->pid);
				ptr = pack_threadid(ptr, thref);
				*(ptr++) = ',';
				ks->thr_query++;
				if (ks->thr_query % KGDB_MAX_THREAD_QUERY == 0)
					finished = 1;
			}
			i++;
		} while_each_thread(g, p);

		*(--ptr) = '\0';
		break;

	case 'C':
		/* Current thread id */
		strcpy(remcom_out_buffer, "QC");
		ks->threadid = shadow_pid(current->pid);
		int_to_threadref(thref, ks->threadid);
		pack_threadid(remcom_out_buffer + 2, thref);
		break;
	case 'T':
		if (memcmp(remcom_in_buffer + 1, "ThreadExtraInfo,", 16))
			break;

		ks->threadid = 0;
		ptr = remcom_in_buffer + 17;
		kgdb_hex2long(&ptr, &ks->threadid);
		if (!getthread(ks->linux_regs, ks->threadid)) {
			error_packet(remcom_out_buffer, -EINVAL);
			break;
		}
		if ((int)ks->threadid > 0) {
			kgdb_mem2hex(getthread(ks->linux_regs,
					ks->threadid)->comm,
					remcom_out_buffer, 16);
		} else {
			static char tmpstr[23 + BUF_THREAD_ID_SIZE];

			sprintf(tmpstr, "shadowCPU%d",
					(int)(-ks->threadid - 2));
			kgdb_mem2hex(tmpstr, remcom_out_buffer, strlen(tmpstr));
		}
		break;
#ifdef CONFIG_KGDB_KDB
	case 'R':
		if (strncmp(remcom_in_buffer, "qRcmd,", 6) == 0) {
			int len = strlen(remcom_in_buffer + 6);

			if ((len % 2) != 0) {
				strcpy(remcom_out_buffer, "E01");
				break;
			}
			kgdb_hex2mem(remcom_in_buffer + 6,
				     remcom_out_buffer, len);
			len = len / 2;
			remcom_out_buffer[len++] = 0;

			kdb_parse(remcom_out_buffer);
			strcpy(remcom_out_buffer, "OK");
		}
		break;
#endif
	}
