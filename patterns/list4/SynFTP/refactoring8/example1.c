int packet_hmac_verify(ssh_session session, ssh_buffer buffer,
    unsigned char *mac, enum ssh_hmac_e type) {
  unsigned char hmacbuf[DIGEST_MAX_LEN] = {0};
  HMACCTX ctx;
  unsigned int len;
  uint32_t seq;

  ctx = hmac_init(session->current_crypto->decryptMAC, hmac_digest_len(type), type);
  if (ctx == NULL) {
    return -1;
  }

  seq = htonl(session->recv_seq);

  hmac_update(ctx, (unsigned char *) &seq, sizeof(uint32_t));
  hmac_update(ctx, buffer_get_rest(buffer), buffer_get_rest_len(buffer));
  hmac_final(ctx, hmacbuf, &len);

#ifdef DEBUG_CRYPTO
  ssh_print_hexa("received mac",mac,len);
  ssh_print_hexa("Computed mac",hmacbuf,len);
  ssh_print_hexa("seq",(unsigned char *)&seq,sizeof(uint32_t));
#endif
  if (memcmp(mac, hmacbuf, len) == 0) {
    return 0;
  }

  return -1;
}
