if( runflag == CHARSERVER_ST_RUNNING &&
			cd != NULL &&
			node != NULL &&
			node->account_id == account_id &&
			node->char_id == char_id &&
			node->login_id1 == login_id1
			//&& node->ip == ip
#if PACKETVER < 20141016
			&& node->sex == sex
#endif
			)
		{// auth ok
			uint16 mmo_charstatus_len = sizeof(struct mmo_charstatus) + 25;
			if (cd->sex == 99)
				cd->sex = sex;

			WFIFOHEAD(fd,mmo_charstatus_len);
			WFIFOW(fd,0) = 0x2afd;
			WFIFOW(fd,2) = mmo_charstatus_len;
			WFIFOL(fd,4) = account_id;
			WFIFOL(fd,8) = node->login_id1;
			WFIFOL(fd,12) = node->login_id2;
			WFIFOL(fd,16) = (uint32)node->expiration_time; // FIXME: will wrap to negative after "19-Jan-2038, 03:14:07 AM GMT"
			WFIFOL(fd,20) = node->group_id;
			WFIFOB(fd,24) = node->changing_mapservers;
			memcpy(WFIFOP(fd,25), cd, sizeof(struct mmo_charstatus));
			WFIFOSET(fd, WFIFOW(fd,2));

			// only use the auth once and mark user online
			idb_remove(auth_db, account_id);
			char_set_char_online(id, char_id, account_id);
		} else {// auth failed
			WFIFOHEAD(fd,19);
			WFIFOW(fd,0) = 0x2b27;
			WFIFOL(fd,2) = account_id;
			WFIFOL(fd,6) = char_id;
			WFIFOL(fd,10) = login_id1;
			WFIFOB(fd,14) = sex;
			WFIFOL(fd,15) = htonl(ip);
			WFIFOSET(fd,19);
		}
