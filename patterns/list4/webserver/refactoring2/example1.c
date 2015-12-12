#ifdef SUPPORT_UCP
if (dc != _pcre_ucp_othercase(fc))
#endif
            RRETURN(MATCH_NOMATCH);
