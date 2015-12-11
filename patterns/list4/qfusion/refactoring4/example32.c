#if POLARSSL_VERSION_NUMBER<0x01020000
if(x509parse_cert_info(buffer, sizeof(buffer), (char *)"* ",
                           conn->ssl[sockindex].ssl.peer_cert) != -1)
#else
    if(x509parse_cert_info(buffer, sizeof(buffer), (char *)"* ",
                           ssl_get_peer_cert(&(connssl->ssl))) != -1)
#endif
      infof(data, "Dumping cert info:\n%s\n", buffer);
