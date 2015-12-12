#if MPC_SV8
if (mpc_demux_seek_second(priv->decoder, offset) == MPC_STATUS_OK)
#else
	if (mpc_decoder_seek_seconds(&priv->decoder, offset))
#endif
		return 0;
