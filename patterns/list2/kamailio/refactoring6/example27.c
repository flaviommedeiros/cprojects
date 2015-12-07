if (sctp_con_id_hash==0 || sctp_con_assoc_hash==0 ||
#ifdef SCTP_ADDR_HASH
			sctp_con_addr_hash==0 ||
#endif /* SCTP_ADDR_HASH */
			sctp_id==0 || sctp_conn_tracked==0){
		ERR("sctp init: memory allocation error\n");
		ret=E_OUT_OF_MEM;
		goto error;
	}
