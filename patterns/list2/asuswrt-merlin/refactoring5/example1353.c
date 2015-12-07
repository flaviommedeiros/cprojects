#ifndef NETSNMP_DISABLE_MIB_LOADING
if (in_dices)
            snprintf(buf, sizeof(buf), "Index out of range: %s (%s)",
                    fcp, in_dices->ilabel);
        else if (tp)
            snprintf(buf, sizeof(buf), "Sub-id not found: %s -> %s", tp->label, fcp);
        else
#endif /* NETSNMP_DISABLE_MIB_LOADING */
            snprintf(buf, sizeof(buf), "%s", fcp);
