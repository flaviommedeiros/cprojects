#ifdef LEGACY_PROTOCOL
if(!chan->compat)
#endif
		MSG_WriteLong(&send, NETCHAN_GENCHECKSUM(chan->challenge, chan->outgoingSequence));
