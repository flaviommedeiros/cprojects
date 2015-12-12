static struct sctp_hmac sctp_hmac_list[SCTP_AUTH_NUM_HMACS] = {
	{
		/* id 0 is reserved.  as all 0 */
		.hmac_id = SCTP_AUTH_HMAC_ID_RESERVED_0,
	},
	{
		.hmac_id = SCTP_AUTH_HMAC_ID_SHA1,
		.hmac_name = "hmac(sha1)",
		.hmac_len = SCTP_SHA1_SIG_SIZE,
	},
	{
		/* id 2 is reserved as well */
		.hmac_id = SCTP_AUTH_HMAC_ID_RESERVED_2,
	},
#if defined (CONFIG_CRYPTO_SHA256) || defined (CONFIG_CRYPTO_SHA256_MODULE)
	{
		.hmac_id = SCTP_AUTH_HMAC_ID_SHA256,
		.hmac_name = "hmac(sha256)",
		.hmac_len = SCTP_SHA256_SIG_SIZE,
	}
#endif
};
