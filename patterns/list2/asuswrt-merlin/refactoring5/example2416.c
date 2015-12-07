#ifdef CONFIG_NCPFS_PACKET_SIGNING
if (ncp_negotiate_size_and_options(server, default_bufsize,
		NCP_DEFAULT_OPTIONS, &(server->buffer_size), &options) == 0)
	{
		if (options != NCP_DEFAULT_OPTIONS)
		{
			if (ncp_negotiate_size_and_options(server, 
				default_bufsize,
				options & 2, 
				&(server->buffer_size), &options) != 0)
				
			{
				goto out_disconnect;
			}
		}
		if (options & 2)
			server->sign_wanted = 1;
	}
	else 
#endif	/* CONFIG_NCPFS_PACKET_SIGNING */
	if (ncp_negotiate_buffersize(server, default_bufsize,
  				     &(server->buffer_size)) != 0)
		goto out_disconnect;
