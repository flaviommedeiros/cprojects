#if defined(NETSNMP_CAN_USE_NLIST) && defined(LOADAVE_SYMBOL)
if (auto_nlist(LOADAVE_SYMBOL, (char *) pave, sizeof(double) * s_ave)
        == 0)
#endif
        return (-1);
