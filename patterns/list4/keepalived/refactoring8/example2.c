const hash_t hashes[hash_guard] = {
	[hash_md5] = {
		(hash_init_f) MD5_Init,
		(hash_update_f) MD5_Update,
		(hash_final_f) MD5_Final,
		MD5_DIGEST_LENGTH,
		"MD5",
		"MD5SUM",
	},
#ifdef FEAT_SHA1
	[hash_sha1] = {
		(hash_init_f) SHA1_Init,
		(hash_update_f) SHA1_Update,
		(hash_final_f) SHA1_Final,
		SHA_DIGEST_LENGTH,
		"SHA1",
		"SHA1SUM",
	}
#endif
};
