#ifndef OPENSSL_NO_SCTP
if (BIO_dgram_is_sctp(SSL_get_wbio(s)) &&
			    state == SSL_ST_RENEGOTIATE)
				s->state=DTLS1_SCTP_ST_CR_READ_SOCK;
			else
#endif			
			s->state=s->s3->tmp.next_state;
