#ifndef OPENSSL_NO_SCTP
if (BIO_dgram_is_sctp(SSL_get_wbio(s)) &&
			    state == SSL_ST_RENEGOTIATE)
				s->state=DTLS1_SCTP_ST_SR_READ_SOCK;
			else
#endif			
				s->state=SSL3_ST_SR_FINISHED_A;
