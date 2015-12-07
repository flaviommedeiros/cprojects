#ifdef ENABLE_MANAGEMENT
if (management)
	{
	  const char *reason = NULL;
	  struct buffer buf = *buffer;
	  if (buf_string_compare_advance (&buf, "AUTH_FAILED,") && BLEN (&buf))
	    reason = BSTR (&buf);
	  management_auth_failure (management, UP_TYPE_AUTH, reason);
	} else
#endif
	{
#ifdef ENABLE_CLIENT_CR
	  struct buffer buf = *buffer;
	  if (buf_string_match_head_str (&buf, "AUTH_FAILED,CRV1:") && BLEN (&buf))
	    {
	      buf_advance (&buf, 12); /* Length of "AUTH_FAILED," substring */
	      ssl_put_auth_challenge (BSTR (&buf));
	    }
#endif
	}
