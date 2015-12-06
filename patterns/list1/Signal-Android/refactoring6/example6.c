if (!s->s3->alpn_selected
#ifndef OPENSSL_NO_NEXTPROTONEG
		&& !s->s3->next_proto_neg_seen
#endif
	)
		{
		return 0;
		}
