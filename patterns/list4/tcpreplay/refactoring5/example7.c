#ifdef _WIN32
if (at->pzOptFmt == zGnuOptFmt)
            snprintf(z, sizeof(z), "--%s%s", od->pz_Name, atyp);
        else if (at->pzOptFmt == zGnuOptFmt + 2)
            snprintf(z, sizeof(z), "%s%s", od->pz_Name, atyp);
        else
#endif
        snprintf(z, sizeof(z), at->pzOptFmt, atyp, od->pz_Name,
                 (od->optMinCt != 0) ? at->pzReq : at->pzOpt);
