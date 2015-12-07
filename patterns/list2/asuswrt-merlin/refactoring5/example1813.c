#ifdef ENABLE_CLI_AGENTFWD
if (key->source == SIGNKEY_SOURCE_AGENT) {
		/* Format the agent signature ourselves, as buf_put_sign would. */
		buffer *sigblob;
		sigblob = buf_new(MAX_PUBKEY_SIZE);
		agent_buf_sign(sigblob, key, data_buf);
		buf_putbufstring(buf, sigblob);
		buf_free(sigblob);
	} else 
#endif /* ENABLE_CLI_AGENTFWD */
	{
		buf_put_sign(buf, key, type, data_buf);
	}
