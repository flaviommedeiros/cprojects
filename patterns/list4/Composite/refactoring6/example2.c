if (cichar != CHAP_DIGEST_MD5
#ifdef CHAPMS
              && cichar != CHAP_MICROSOFT
#endif
          ) {
            LCPDEBUG((LOG_WARNING, "lcp_reqci: Nak AUTHTYPE CHAP digest=%d\n", cichar));
            orc = CONFNAK;
            PUTCHAR(CI_AUTHTYPE, nakp);
            PUTCHAR(CILEN_CHAP, nakp);
            PUTSHORT(PPP_CHAP, nakp);
            PUTCHAR(ao->chap_mdtype, nakp);
            break;
          }
