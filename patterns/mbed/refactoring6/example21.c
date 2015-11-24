if (cichar != CHAP_DIGEST_MD5
#if MSCHAP_SUPPORT
              && cichar != CHAP_MICROSOFT
#endif
          ) {
            LCPDEBUG(LOG_WARNING, ("lcp_reqci: Nak AUTHTYPE CHAP digest=%d\n", (int)cichar));
            orc = CONFNAK;
            PUTCHAR(CI_AUTHTYPE, nakp);
            PUTCHAR(CILEN_CHAP, nakp);
            PUTSHORT(PPP_CHAP, nakp);
            PUTCHAR(ao->chap_mdtype, nakp);
            break;
          }
