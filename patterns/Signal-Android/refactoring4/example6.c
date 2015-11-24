#if defined(OPENSSL_SYS_WINDOWS) || defined(OPENSSL_SYS_MSDOS)
if (_kbhit())
#else
		else if ((_kbhit()) || (WAIT_OBJECT_0 == WaitForSingleObject(GetStdHandle(STD_INPUT_HANDLE), 0)))
#endif
#elif defined (OPENSSL_SYS_NETWARE)
		else if (_kbhit())
#elif defined(OPENSSL_SYS_BEOS_R5)
		else if (stdin_set)
#else
		else if (FD_ISSET(fileno(stdin),&readfds))
#endif
			{
			if (crlf)
				{
				int j, lf_num;

				i=raw_read_stdin(cbuf,BUFSIZZ/2);
				lf_num = 0;
				/* both loops are skipped when i <= 0 */
				for (j = 0; j < i; j++)
					if (cbuf[j] == '\n')
						lf_num++;
				for (j = i-1; j >= 0; j--)
					{
					cbuf[j+lf_num] = cbuf[j];
					if (cbuf[j] == '\n')
						{
						lf_num--;
						i++;
						cbuf[j+lf_num] = '\r';
						}
					}
				assert(lf_num == 0);
				}
			else
				i=raw_read_stdin(cbuf,BUFSIZZ);

			if ((!c_ign_eof) && ((i <= 0) || (cbuf[0] == 'Q')))
				{
				BIO_printf(bio_err,"DONE\n");
				ret=0;
				goto shut;
				}

			if ((!c_ign_eof) && (cbuf[0] == 'R'))
				{
				BIO_printf(bio_err,"RENEGOTIATING\n");
				SSL_renegotiate(con);
				cbuf_len=0;
				}
#ifndef OPENSSL_NO_HEARTBEATS
			else if ((!c_ign_eof) && (cbuf[0] == 'B'))
 				{
				BIO_printf(bio_err,"HEARTBEATING\n");
				SSL_heartbeat(con);
				cbuf_len=0;
				}
#endif
			else
				{
				cbuf_len=i;
				cbuf_off=0;
#ifdef CHARSET_EBCDIC
				ebcdic2ascii(cbuf, cbuf, i);
#endif
				}

			write_ssl=1;
			read_tty=0;
			}
