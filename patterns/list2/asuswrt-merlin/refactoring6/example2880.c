if(0
#ifdef ALLOW_SIMULT_CONNECT
     || ((irttp_is_primary(server->tsap) == 1) &&	/* primary */
	 (test_and_clear_bit(0, &new->ttp_connect)))
#endif /* ALLOW_SIMULT_CONNECT */
     )
    {
      DERROR(IRDA_CB_ERROR, "Socket already connecting, but going to reuse it !\n");

      /* Cleanup the old TSAP if necessary - IrIAP will be cleaned up later */
      if(new->tsap != NULL)
	{
	  /* Close the old connection the new socket was attempting,
	   * so that we can hook it up to the new connection.
	   * It's now safe to do it... */
	  irttp_close_tsap(new->tsap);
	  new->tsap = NULL;
	}
    }
  else
    {
      /* Three options :
       * 1) socket was not connecting or connected : ttp_connect should be 0.
       * 2) we don't want to connect the socket because we are secondary or
       * ALLOW_SIMULT_CONNECT is undefined. ttp_connect should be 1.
       * 3) we are half way in irnet_disconnect_indication(), and it's a
       * nice race condition... Fortunately, we can detect that by checking
       * if tsap is still alive. On the other hand, we can't be in
       * irda_irnet_destroy() otherwise we would not have found this
       * socket in the hashbin.
       * Jean II */
      if((test_bit(0, &new->ttp_connect)) || (new->tsap != NULL))
	{
	  /* Don't mess this socket, somebody else in in charge... */
	  DERROR(IRDA_CB_ERROR, "Race condition detected, socket in use, abort connect...\n");
	  irnet_disconnect_server(server, skb);
	  return;
	}
    }
