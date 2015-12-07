#ifdef ENABLE_CLIENT_CR
if (auth_challenge && (flags & GET_USER_PASS_DYNAMIC_CHALLENGE))
	    {
	      struct auth_challenge_info *ac = get_auth_challenge (auth_challenge, &gc);
	      if (ac)
		{
		  char *response = (char *) gc_malloc (USER_PASS_LEN, false, &gc);
		  struct buffer packed_resp;

		  buf_set_write (&packed_resp, (uint8_t*)up->password, USER_PASS_LEN);
		  msg (M_INFO|M_NOPREFIX, "CHALLENGE: %s", ac->challenge_text);
		  if (!get_console_input ("Response:", BOOL_CAST(ac->flags&CR_ECHO), response, USER_PASS_LEN))
		    msg (M_FATAL, "ERROR: could not read challenge response from stdin");
		  strncpynt (up->username, ac->user, USER_PASS_LEN);
		  buf_printf (&packed_resp, "CRV1::%s::%s", ac->state_id, response);
		}
	      else
		{
		  msg (M_FATAL, "ERROR: received malformed challenge request from server");
		}
	    }
	  else
#endif
	    {
	      struct buffer user_prompt = alloc_buf_gc (128, &gc);
	      struct buffer pass_prompt = alloc_buf_gc (128, &gc);

	      buf_printf (&user_prompt, "Enter %s Username:", prefix);
	      buf_printf (&pass_prompt, "Enter %s Password:", prefix);

	      if (!(flags & GET_USER_PASS_PASSWORD_ONLY))
		{
		  if (!get_console_input (BSTR (&user_prompt), true, up->username, USER_PASS_LEN))
		    msg (M_FATAL, "ERROR: could not read %s username from stdin", prefix);
		  if (strlen (up->username) == 0)
		    msg (M_FATAL, "ERROR: %s username is empty", prefix);
		}

	      if (!get_console_input (BSTR (&pass_prompt), false, up->password, USER_PASS_LEN))
		msg (M_FATAL, "ERROR: could not not read %s password from stdin", prefix);

#ifdef ENABLE_CLIENT_CR
	      if (auth_challenge && (flags & GET_USER_PASS_STATIC_CHALLENGE))
		{
		  char *response = (char *) gc_malloc (USER_PASS_LEN, false, &gc);
		  struct buffer packed_resp;
		  char *pw64=NULL, *resp64=NULL;

		  msg (M_INFO|M_NOPREFIX, "CHALLENGE: %s", auth_challenge);
		  if (!get_console_input ("Response:", BOOL_CAST(flags & GET_USER_PASS_STATIC_CHALLENGE_ECHO), response, USER_PASS_LEN))
		    msg (M_FATAL, "ERROR: could not read static challenge response from stdin");
		  if (openvpn_base64_encode(up->password, strlen(up->password), &pw64) == -1
		      || openvpn_base64_encode(response, strlen(response), &resp64) == -1)
		    msg (M_FATAL, "ERROR: could not base64-encode password/static_response");
		  buf_set_write (&packed_resp, (uint8_t*)up->password, USER_PASS_LEN);
		  buf_printf (&packed_resp, "SCRV1:%s:%s", pw64, resp64);
		  string_clear(pw64);
		  free(pw64);
		  string_clear(resp64);
		  free(resp64);
		}
#endif
	    }
