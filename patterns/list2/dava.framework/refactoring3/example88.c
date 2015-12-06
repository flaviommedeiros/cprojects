switch (s->state)
		{
case SSL_ST_BEFORE:				str="PINIT "; break;
case SSL_ST_ACCEPT:				str="AINIT "; break;
case SSL_ST_CONNECT:				str="CINIT "; break;
case SSL_ST_OK:			 		str="SSLOK "; break;
#ifndef OPENSSL_NO_SSL2
case SSL2_ST_CLIENT_START_ENCRYPTION:		str="2CSENC"; break;
case SSL2_ST_SERVER_START_ENCRYPTION:		str="2SSENC"; break;
case SSL2_ST_SEND_CLIENT_HELLO_A:		str="2SCH_A"; break;
case SSL2_ST_SEND_CLIENT_HELLO_B:		str="2SCH_B"; break;
case SSL2_ST_GET_SERVER_HELLO_A:		str="2GSH_A"; break;
case SSL2_ST_GET_SERVER_HELLO_B:		str="2GSH_B"; break;
case SSL2_ST_SEND_CLIENT_MASTER_KEY_A:		str="2SCMKA"; break;
case SSL2_ST_SEND_CLIENT_MASTER_KEY_B:		str="2SCMKB"; break;
case SSL2_ST_SEND_CLIENT_FINISHED_A:		str="2SCF_A"; break;
case SSL2_ST_SEND_CLIENT_FINISHED_B:		str="2SCF_B"; break;
case SSL2_ST_SEND_CLIENT_CERTIFICATE_A:		str="2SCC_A"; break;
case SSL2_ST_SEND_CLIENT_CERTIFICATE_B:		str="2SCC_B"; break;
case SSL2_ST_SEND_CLIENT_CERTIFICATE_C:		str="2SCC_C"; break;
case SSL2_ST_SEND_CLIENT_CERTIFICATE_D:		str="2SCC_D"; break;
case SSL2_ST_GET_SERVER_VERIFY_A:		str="2GSV_A"; break;
case SSL2_ST_GET_SERVER_VERIFY_B:		str="2GSV_B"; break;
case SSL2_ST_GET_SERVER_FINISHED_A:		str="2GSF_A"; break;
case SSL2_ST_GET_SERVER_FINISHED_B:		str="2GSF_B"; break;
case SSL2_ST_GET_CLIENT_HELLO_A:		str="2GCH_A"; break;
case SSL2_ST_GET_CLIENT_HELLO_B:		str="2GCH_B"; break;
case SSL2_ST_GET_CLIENT_HELLO_C:		str="2GCH_C"; break;
case SSL2_ST_SEND_SERVER_HELLO_A:		str="2SSH_A"; break;
case SSL2_ST_SEND_SERVER_HELLO_B:		str="2SSH_B"; break;
case SSL2_ST_GET_CLIENT_MASTER_KEY_A:		str="2GCMKA"; break;
case SSL2_ST_GET_CLIENT_MASTER_KEY_B:		str="2GCMKA"; break;
case SSL2_ST_SEND_SERVER_VERIFY_A:		str="2SSV_A"; break;
case SSL2_ST_SEND_SERVER_VERIFY_B:		str="2SSV_B"; break;
case SSL2_ST_SEND_SERVER_VERIFY_C:		str="2SSV_C"; break;
case SSL2_ST_GET_CLIENT_FINISHED_A:		str="2GCF_A"; break;
case SSL2_ST_GET_CLIENT_FINISHED_B:		str="2GCF_B"; break;
case SSL2_ST_SEND_SERVER_FINISHED_A:		str="2SSF_A"; break;
case SSL2_ST_SEND_SERVER_FINISHED_B:		str="2SSF_B"; break;
case SSL2_ST_SEND_REQUEST_CERTIFICATE_A:	str="2SRC_A"; break;
case SSL2_ST_SEND_REQUEST_CERTIFICATE_B:	str="2SRC_B"; break;
case SSL2_ST_SEND_REQUEST_CERTIFICATE_C:	str="2SRC_C"; break;
case SSL2_ST_SEND_REQUEST_CERTIFICATE_D:	str="2SRC_D"; break;
case SSL2_ST_X509_GET_SERVER_CERTIFICATE:	str="2X9GSC"; break;
case SSL2_ST_X509_GET_CLIENT_CERTIFICATE:	str="2X9GCC"; break;
#endif

#ifndef OPENSSL_NO_SSL3
/* SSLv3 additions */
case SSL3_ST_SW_FLUSH:
case SSL3_ST_CW_FLUSH:				str="3FLUSH"; break;
case SSL3_ST_CW_CLNT_HELLO_A:			str="3WCH_A"; break;
case SSL3_ST_CW_CLNT_HELLO_B:			str="3WCH_B"; break;
case SSL3_ST_CR_SRVR_HELLO_A:			str="3RSH_A"; break;
case SSL3_ST_CR_SRVR_HELLO_B:			str="3RSH_B"; break;
case SSL3_ST_CR_CERT_A:				str="3RSC_A"; break;
case SSL3_ST_CR_CERT_B:				str="3RSC_B"; break;
case SSL3_ST_CR_KEY_EXCH_A:			str="3RSKEA"; break;
case SSL3_ST_CR_KEY_EXCH_B:			str="3RSKEB"; break;
case SSL3_ST_CR_CERT_REQ_A:			str="3RCR_A"; break;
case SSL3_ST_CR_CERT_REQ_B:			str="3RCR_B"; break;
case SSL3_ST_CR_SRVR_DONE_A:			str="3RSD_A"; break;
case SSL3_ST_CR_SRVR_DONE_B:			str="3RSD_B"; break;
case SSL3_ST_CW_CERT_A:				str="3WCC_A"; break;
case SSL3_ST_CW_CERT_B:				str="3WCC_B"; break;
case SSL3_ST_CW_CERT_C:				str="3WCC_C"; break;
case SSL3_ST_CW_CERT_D:				str="3WCC_D"; break;
case SSL3_ST_CW_KEY_EXCH_A:			str="3WCKEA"; break;
case SSL3_ST_CW_KEY_EXCH_B:			str="3WCKEB"; break;
case SSL3_ST_CW_CERT_VRFY_A:			str="3WCV_A"; break;
case SSL3_ST_CW_CERT_VRFY_B:			str="3WCV_B"; break;

case SSL3_ST_SW_CHANGE_A:
case SSL3_ST_CW_CHANGE_A:			str="3WCCSA"; break;
case SSL3_ST_SW_CHANGE_B:
case SSL3_ST_CW_CHANGE_B:			str="3WCCSB"; break;
case SSL3_ST_SW_FINISHED_A:
case SSL3_ST_CW_FINISHED_A:			str="3WFINA"; break;
case SSL3_ST_SW_FINISHED_B:
case SSL3_ST_CW_FINISHED_B:			str="3WFINB"; break;
case SSL3_ST_SR_CHANGE_A:
case SSL3_ST_CR_CHANGE_A:			str="3RCCSA"; break;
case SSL3_ST_SR_CHANGE_B:
case SSL3_ST_CR_CHANGE_B:			str="3RCCSB"; break;
case SSL3_ST_SR_FINISHED_A:
case SSL3_ST_CR_FINISHED_A:			str="3RFINA"; break;
case SSL3_ST_SR_FINISHED_B:
case SSL3_ST_CR_FINISHED_B:			str="3RFINB"; break;

case SSL3_ST_SW_HELLO_REQ_A:			str="3WHR_A"; break;
case SSL3_ST_SW_HELLO_REQ_B:			str="3WHR_B"; break;
case SSL3_ST_SW_HELLO_REQ_C:			str="3WHR_C"; break;
case SSL3_ST_SR_CLNT_HELLO_A:			str="3RCH_A"; break;
case SSL3_ST_SR_CLNT_HELLO_B:			str="3RCH_B"; break;
case SSL3_ST_SR_CLNT_HELLO_C:			str="3RCH_C"; break;
case SSL3_ST_SW_SRVR_HELLO_A:			str="3WSH_A"; break;
case SSL3_ST_SW_SRVR_HELLO_B:			str="3WSH_B"; break;
case SSL3_ST_SW_CERT_A:				str="3WSC_A"; break;
case SSL3_ST_SW_CERT_B:				str="3WSC_B"; break;
case SSL3_ST_SW_KEY_EXCH_A:			str="3WSKEA"; break;
case SSL3_ST_SW_KEY_EXCH_B:			str="3WSKEB"; break;
case SSL3_ST_SW_CERT_REQ_A:			str="3WCR_A"; break;
case SSL3_ST_SW_CERT_REQ_B:			str="3WCR_B"; break;
case SSL3_ST_SW_SRVR_DONE_A:			str="3WSD_A"; break;
case SSL3_ST_SW_SRVR_DONE_B:			str="3WSD_B"; break;
case SSL3_ST_SR_CERT_A:				str="3RCC_A"; break;
case SSL3_ST_SR_CERT_B:				str="3RCC_B"; break;
case SSL3_ST_SR_KEY_EXCH_A:			str="3RCKEA"; break;
case SSL3_ST_SR_KEY_EXCH_B:			str="3RCKEB"; break;
case SSL3_ST_SR_CERT_VRFY_A:			str="3RCV_A"; break;
case SSL3_ST_SR_CERT_VRFY_B:			str="3RCV_B"; break;
#endif

/* SSLv2/v3 compatibility states */
/* client */
case SSL23_ST_CW_CLNT_HELLO_A:			str="23WCHA"; break;
case SSL23_ST_CW_CLNT_HELLO_B:			str="23WCHB"; break;
case SSL23_ST_CR_SRVR_HELLO_A:			str="23RSHA"; break;
case SSL23_ST_CR_SRVR_HELLO_B:			str="23RSHA"; break;
/* server */
case SSL23_ST_SR_CLNT_HELLO_A:			str="23RCHA"; break;
case SSL23_ST_SR_CLNT_HELLO_B:			str="23RCHB"; break;

/* DTLS */
case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_A: str="DRCHVA"; break;
case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_B: str="DRCHVB"; break;
case DTLS1_ST_SW_HELLO_VERIFY_REQUEST_A: str="DWCHVA"; break;
case DTLS1_ST_SW_HELLO_VERIFY_REQUEST_B: str="DWCHVB"; break;

default:					str="UNKWN "; break;
		}
