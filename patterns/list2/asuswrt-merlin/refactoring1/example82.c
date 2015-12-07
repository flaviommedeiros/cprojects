if (PAM_error == PAM_NEW_AUTHTOK_REQD)    /* password expired */
            ret = AFPERR_PWDEXPR;
#ifdef PAM_AUTHTOKEN_REQD
        else if (PAM_error == PAM_AUTHTOKEN_REQD)
            ret = AFPERR_PWDCHNG;
#endif
