# ifdef OPENSSL_FIPS
if (FIPS_mode()) {
                *pcurves = fips_curves_default;
                pcurveslen = sizeof(fips_curves_default);
            } else
# endif
            {
                if (!s->server || (s->cert && s->cert->ecdh_tmp_auto)) {
                    *pcurves = eccurves_auto;
                    pcurveslen = sizeof(eccurves_auto);
                } else {
                    *pcurves = eccurves_all;
                    pcurveslen = sizeof(eccurves_all);
                }
            }
