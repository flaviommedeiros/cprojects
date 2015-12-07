# ifdef ENABLE_CLIENT_CR
if (auth_challenge) /* dynamic challenge/response */
       get_user_pass_cr (&auth_user_pass,
                         auth_file,
                         UP_TYPE_AUTH,
                         GET_USER_PASS_MANAGEMENT|GET_USER_PASS_SENSITIVE|GET_USER_PASS_DYNAMIC_CHALLENGE,
                         auth_challenge);
      else if (sci) /* static challenge response */
       {
         int flags = GET_USER_PASS_MANAGEMENT|GET_USER_PASS_SENSITIVE|GET_USER_PASS_STATIC_CHALLENGE;
         if (sci->flags & SC_ECHO)
           flags |= GET_USER_PASS_STATIC_CHALLENGE_ECHO;
         get_user_pass_cr (&auth_user_pass,
                           auth_file,
                           UP_TYPE_AUTH,
                           flags,
                           sci->challenge_text);
       }
      else
# endif
       get_user_pass (&auth_user_pass, auth_file, UP_TYPE_AUTH, GET_USER_PASS_MANAGEMENT|GET_USER_PASS_SENSITIVE);
