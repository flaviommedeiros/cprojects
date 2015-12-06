void
pppSetAuth(enum pppAuthType authType, const char *user, const char *passwd)
{
  switch(authType) {
    case PPPAUTHTYPE_NONE:
    default:
#ifdef LWIP_PPP_STRICT_PAP_REJECT
      ppp_settings.refuse_pap = 1;
#else  /* LWIP_PPP_STRICT_PAP_REJECT */
      /* some providers request pap and accept an empty login/pw */
      ppp_settings.refuse_pap = 0;
#endif /* LWIP_PPP_STRICT_PAP_REJECT */
      ppp_settings.refuse_chap = 1;
      break;

    case PPPAUTHTYPE_ANY:
      /* Warning: Using PPPAUTHTYPE_ANY might have security consequences.
       * RFC 1994 says:
       *
       * In practice, within or associated with each PPP server, there is a
       * database which associates "user" names with authentication
       * information ("secrets").  It is not anticipated that a particular
       * named user would be authenticated by multiple methods.  This would
       * make the user vulnerable to attacks which negotiate the least secure
       * method from among a set (such as PAP rather than CHAP).  If the same
       * secret was used, PAP would reveal the secret to be used later with
       * CHAP.
       *
       * Instead, for each user name there should be an indication of exactly
       * one method used to authenticate that user name.  If a user needs to
       * make use of different authentication methods under different
       * circumstances, then distinct user names SHOULD be employed, each of
       * which identifies exactly one authentication method.
       *
       */
      ppp_settings.refuse_pap = 0;
      ppp_settings.refuse_chap = 0;
      break;

    case PPPAUTHTYPE_PAP:
      ppp_settings.refuse_pap = 0;
      ppp_settings.refuse_chap = 1;
      break;

    case PPPAUTHTYPE_CHAP:
      ppp_settings.refuse_pap = 1;
      ppp_settings.refuse_chap = 0;
      break;
  }

  if(user) {
    strncpy(ppp_settings.user, user, sizeof(ppp_settings.user)-1);
    ppp_settings.user[sizeof(ppp_settings.user)-1] = '\0';
  } else {
    ppp_settings.user[0] = '\0';
  }

  if(passwd) {
    strncpy(ppp_settings.passwd, passwd, sizeof(ppp_settings.passwd)-1);
    ppp_settings.passwd[sizeof(ppp_settings.passwd)-1] = '\0';
  } else {
    ppp_settings.passwd[0] = '\0';
  }
}
