#ifndef OPENSSL_NO_SCTP
if ((!s->in_handshake && SSL_in_init(s)) ||
	    (BIO_dgram_is_sctp(SSL_get_rbio(s)) &&
	     (s->state == DTLS1_SCTP_ST_SR_READ_SOCK || s->state == DTLS1_SCTP_ST_CR_READ_SOCK) &&
	     s->s3->in_read_app_data != 2))
#else
	if (!s->in_handshake && SSL_in_init(s))
#endif
		{
		/* type == SSL3_RT_APPLICATION_DATA */
		i=s->handshake_func(s);
		if (i < 0) return(i);
		if (i == 0)
			{
			SSLerr(SSL_F_DTLS1_READ_BYTES,SSL_R_SSL_HANDSHAKE_FAILURE);
			return(-1);
			}
		}
