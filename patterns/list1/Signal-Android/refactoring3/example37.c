switch (s->state)
		{
case SSL_ST_BEFORE: str="before SSL initialization"; break;
case SSL_ST_ACCEPT: str="before accept initialization"; break;
case SSL_ST_CONNECT: str="before connect initialization"; break;
case SSL_ST_OK: str="SSL negotiation finished successfully"; break;
case SSL_ST_RENEGOTIATE:	str="SSL renegotiate ciphers"; break;
case SSL_ST_BEFORE|SSL_ST_CONNECT: str="before/connect initialization"; break;
case SSL_ST_OK|SSL_ST_CONNECT: str="ok/connect SSL initialization"; break;
case SSL_ST_BEFORE|SSL_ST_ACCEPT: str="before/accept initialization"; break;
case SSL_ST_OK|SSL_ST_ACCEPT: str="ok/accept SSL initialization"; break;
#ifndef OPENSSL_NO_SSL2
case SSL2_ST_CLIENT_START_ENCRYPTION: str="SSLv2 client start encryption"; break;
case SSL2_ST_SERVER_START_ENCRYPTION: str="SSLv2 server start encryption"; break;
case SSL2_ST_SEND_CLIENT_HELLO_A: str="SSLv2 write client hello A"; break;
case SSL2_ST_SEND_CLIENT_HELLO_B: str="SSLv2 write client hello B"; break;
case SSL2_ST_GET_SERVER_HELLO_A: str="SSLv2 read server hello A"; break;
case SSL2_ST_GET_SERVER_HELLO_B: str="SSLv2 read server hello B"; break;
case SSL2_ST_SEND_CLIENT_MASTER_KEY_A: str="SSLv2 write client master key A"; break;
case SSL2_ST_SEND_CLIENT_MASTER_KEY_B: str="SSLv2 write client master key B"; break;
case SSL2_ST_SEND_CLIENT_FINISHED_A: str="SSLv2 write client finished A"; break;
case SSL2_ST_SEND_CLIENT_FINISHED_B: str="SSLv2 write client finished B"; break;
case SSL2_ST_SEND_CLIENT_CERTIFICATE_A: str="SSLv2 write client certificate A"; break;
case SSL2_ST_SEND_CLIENT_CERTIFICATE_B: str="SSLv2 write client certificate B"; break;
case SSL2_ST_SEND_CLIENT_CERTIFICATE_C: str="SSLv2 write client certificate C"; break;
case SSL2_ST_SEND_CLIENT_CERTIFICATE_D: str="SSLv2 write client certificate D"; break;
case SSL2_ST_GET_SERVER_VERIFY_A: str="SSLv2 read server verify A"; break;
case SSL2_ST_GET_SERVER_VERIFY_B: str="SSLv2 read server verify B"; break;
case SSL2_ST_GET_SERVER_FINISHED_A: str="SSLv2 read server finished A"; break;
case SSL2_ST_GET_SERVER_FINISHED_B: str="SSLv2 read server finished B"; break;
case SSL2_ST_GET_CLIENT_HELLO_A: str="SSLv2 read client hello A"; break;
case SSL2_ST_GET_CLIENT_HELLO_B: str="SSLv2 read client hello B"; break;
case SSL2_ST_GET_CLIENT_HELLO_C: str="SSLv2 read client hello C"; break;
case SSL2_ST_SEND_SERVER_HELLO_A: str="SSLv2 write server hello A"; break;
case SSL2_ST_SEND_SERVER_HELLO_B: str="SSLv2 write server hello B"; break;
case SSL2_ST_GET_CLIENT_MASTER_KEY_A: str="SSLv2 read client master key A"; break;
case SSL2_ST_GET_CLIENT_MASTER_KEY_B: str="SSLv2 read client master key B"; break;
case SSL2_ST_SEND_SERVER_VERIFY_A: str="SSLv2 write server verify A"; break;
case SSL2_ST_SEND_SERVER_VERIFY_B: str="SSLv2 write server verify B"; break;
case SSL2_ST_SEND_SERVER_VERIFY_C: str="SSLv2 write server verify C"; break;
case SSL2_ST_GET_CLIENT_FINISHED_A: str="SSLv2 read client finished A"; break;
case SSL2_ST_GET_CLIENT_FINISHED_B: str="SSLv2 read client finished B"; break;
case SSL2_ST_SEND_SERVER_FINISHED_A: str="SSLv2 write server finished A"; break;
case SSL2_ST_SEND_SERVER_FINISHED_B: str="SSLv2 write server finished B"; break;
case SSL2_ST_SEND_REQUEST_CERTIFICATE_A: str="SSLv2 write request certificate A"; break;
case SSL2_ST_SEND_REQUEST_CERTIFICATE_B: str="SSLv2 write request certificate B"; break;
case SSL2_ST_SEND_REQUEST_CERTIFICATE_C: str="SSLv2 write request certificate C"; break;
case SSL2_ST_SEND_REQUEST_CERTIFICATE_D: str="SSLv2 write request certificate D"; break;
case SSL2_ST_X509_GET_SERVER_CERTIFICATE: str="SSLv2 X509 read server certificate"; break;
case SSL2_ST_X509_GET_CLIENT_CERTIFICATE: str="SSLv2 X509 read client certificate"; break;
#endif

#ifndef OPENSSL_NO_SSL3
/* SSLv3 additions */
case SSL3_ST_CW_CLNT_HELLO_A:	str="SSLv3 write client hello A"; break;
case SSL3_ST_CW_CLNT_HELLO_B:	str="SSLv3 write client hello B"; break;
case SSL3_ST_CR_SRVR_HELLO_A:	str="SSLv3 read server hello A"; break;
case SSL3_ST_CR_SRVR_HELLO_B:	str="SSLv3 read server hello B"; break;
case SSL3_ST_CR_CERT_A:		str="SSLv3 read server certificate A"; break;
case SSL3_ST_CR_CERT_B:		str="SSLv3 read server certificate B"; break;
case SSL3_ST_CR_KEY_EXCH_A:	str="SSLv3 read server key exchange A"; break;
case SSL3_ST_CR_KEY_EXCH_B:	str="SSLv3 read server key exchange B"; break;
case SSL3_ST_CR_CERT_REQ_A:	str="SSLv3 read server certificate request A"; break;
case SSL3_ST_CR_CERT_REQ_B:	str="SSLv3 read server certificate request B"; break;
case SSL3_ST_CR_SESSION_TICKET_A: str="SSLv3 read server session ticket A";break;
case SSL3_ST_CR_SESSION_TICKET_B: str="SSLv3 read server session ticket B";break;
case SSL3_ST_CR_SRVR_DONE_A:	str="SSLv3 read server done A"; break;
case SSL3_ST_CR_SRVR_DONE_B:	str="SSLv3 read server done B"; break;
case SSL3_ST_CW_CERT_A:		str="SSLv3 write client certificate A"; break;
case SSL3_ST_CW_CERT_B:		str="SSLv3 write client certificate B"; break;
case SSL3_ST_CW_CERT_C:		str="SSLv3 write client certificate C"; break;
case SSL3_ST_CW_CERT_D:		str="SSLv3 write client certificate D"; break;
case SSL3_ST_CW_KEY_EXCH_A:	str="SSLv3 write client key exchange A"; break;
case SSL3_ST_CW_KEY_EXCH_B:	str="SSLv3 write client key exchange B"; break;
case SSL3_ST_CW_CERT_VRFY_A:	str="SSLv3 write certificate verify A"; break;
case SSL3_ST_CW_CERT_VRFY_B:	str="SSLv3 write certificate verify B"; break;

case SSL3_ST_CW_CHANGE_A:
case SSL3_ST_SW_CHANGE_A:	str="SSLv3 write change cipher spec A"; break;
case SSL3_ST_CW_CHANGE_B:	
case SSL3_ST_SW_CHANGE_B:	str="SSLv3 write change cipher spec B"; break;
case SSL3_ST_CW_FINISHED_A:	
case SSL3_ST_SW_FINISHED_A:	str="SSLv3 write finished A"; break;
case SSL3_ST_CW_FINISHED_B:	
case SSL3_ST_SW_FINISHED_B:	str="SSLv3 write finished B"; break;
case SSL3_ST_CR_CHANGE_A:	
case SSL3_ST_SR_CHANGE_A:	str="SSLv3 read change cipher spec A"; break;
case SSL3_ST_CR_CHANGE_B:	
case SSL3_ST_SR_CHANGE_B:	str="SSLv3 read change cipher spec B"; break;
case SSL3_ST_CR_FINISHED_A:	
case SSL3_ST_SR_FINISHED_A:	str="SSLv3 read finished A"; break;
case SSL3_ST_CR_FINISHED_B:	
case SSL3_ST_SR_FINISHED_B:	str="SSLv3 read finished B"; break;

case SSL3_ST_CW_FLUSH:
case SSL3_ST_SW_FLUSH:		str="SSLv3 flush data"; break;

case SSL3_ST_SR_CLNT_HELLO_A:	str="SSLv3 read client hello A"; break;
case SSL3_ST_SR_CLNT_HELLO_B:	str="SSLv3 read client hello B"; break;
case SSL3_ST_SR_CLNT_HELLO_C:	str="SSLv3 read client hello C"; break;
case SSL3_ST_SW_HELLO_REQ_A:	str="SSLv3 write hello request A"; break;
case SSL3_ST_SW_HELLO_REQ_B:	str="SSLv3 write hello request B"; break;
case SSL3_ST_SW_HELLO_REQ_C:	str="SSLv3 write hello request C"; break;
case SSL3_ST_SW_SRVR_HELLO_A:	str="SSLv3 write server hello A"; break;
case SSL3_ST_SW_SRVR_HELLO_B:	str="SSLv3 write server hello B"; break;
case SSL3_ST_SW_CERT_A:		str="SSLv3 write certificate A"; break;
case SSL3_ST_SW_CERT_B:		str="SSLv3 write certificate B"; break;
case SSL3_ST_SW_KEY_EXCH_A:	str="SSLv3 write key exchange A"; break;
case SSL3_ST_SW_KEY_EXCH_B:	str="SSLv3 write key exchange B"; break;
case SSL3_ST_SW_CERT_REQ_A:	str="SSLv3 write certificate request A"; break;
case SSL3_ST_SW_CERT_REQ_B:	str="SSLv3 write certificate request B"; break;
case SSL3_ST_SW_SESSION_TICKET_A: str="SSLv3 write session ticket A"; break;
case SSL3_ST_SW_SESSION_TICKET_B: str="SSLv3 write session ticket B"; break;
case SSL3_ST_SW_SRVR_DONE_A:	str="SSLv3 write server done A"; break;
case SSL3_ST_SW_SRVR_DONE_B:	str="SSLv3 write server done B"; break;
case SSL3_ST_SR_CERT_A:		str="SSLv3 read client certificate A"; break;
case SSL3_ST_SR_CERT_B:		str="SSLv3 read client certificate B"; break;
case SSL3_ST_SR_KEY_EXCH_A:	str="SSLv3 read client key exchange A"; break;
case SSL3_ST_SR_KEY_EXCH_B:	str="SSLv3 read client key exchange B"; break;
case SSL3_ST_SR_CERT_VRFY_A:	str="SSLv3 read certificate verify A"; break;
case SSL3_ST_SR_CERT_VRFY_B:	str="SSLv3 read certificate verify B"; break;
#endif

#if !defined(OPENSSL_NO_SSL2) && !defined(OPENSSL_NO_SSL3)
/* SSLv2/v3 compatibility states */
/* client */
case SSL23_ST_CW_CLNT_HELLO_A:	str="SSLv2/v3 write client hello A"; break;
case SSL23_ST_CW_CLNT_HELLO_B:	str="SSLv2/v3 write client hello B"; break;
case SSL23_ST_CR_SRVR_HELLO_A:	str="SSLv2/v3 read server hello A"; break;
case SSL23_ST_CR_SRVR_HELLO_B:	str="SSLv2/v3 read server hello B"; break;
/* server */
case SSL23_ST_SR_CLNT_HELLO_A:	str="SSLv2/v3 read client hello A"; break;
case SSL23_ST_SR_CLNT_HELLO_B:	str="SSLv2/v3 read client hello B"; break;
#endif

/* DTLS */
case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_A: str="DTLS1 read hello verify request A"; break;
case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_B: str="DTLS1 read hello verify request B"; break;
case DTLS1_ST_SW_HELLO_VERIFY_REQUEST_A: str="DTLS1 write hello verify request A"; break;
case DTLS1_ST_SW_HELLO_VERIFY_REQUEST_B: str="DTLS1 write hello verify request B"; break;

default:	str="unknown state"; break;
		}
