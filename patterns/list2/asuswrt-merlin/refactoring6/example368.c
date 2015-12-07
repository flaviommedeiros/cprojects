if (!cli_send_trans(cli, SMBtrans2, 
				    NULL,                   /* Name */
				    -1, 0,                  /* fid, flags */
				    &setup, 1, 0,           /* setup, length, max */
				    param, param_len, 10,   /* param, length, max */
				    NULL, 0, 
#if 0
				    /* w2k value. */
				    MIN(16384,cli->max_xmit) /* data, length, max. */
#else
				    cli->max_xmit	    /* data, length, max. */
#endif
				    )) {
			break;
		}
