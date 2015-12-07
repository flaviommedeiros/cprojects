#ifdef ENABLE_X509ALTUSERNAME
if (strncmp("ext:",x509_username_field,4) == 0)
    {
      if (!extract_x509_extension (peer_cert, x509_username_field+4, common_name, cn_len))
	return FAILURE;
    } else
#endif
  if (FAILURE == extract_x509_field_ssl (X509_get_subject_name (peer_cert),
      x509_username_field, common_name, cn_len))
      return FAILURE;
