static const iw_handler wl_private_handler[] =
{                                                       /* SIOCIWFIRSTPRIV + */
                wvlan_set_netname,                      /* 0: SIOCSIWNETNAME */
                wvlan_get_netname,                      /* 1: SIOCGIWNETNAME */
                wvlan_set_station_nickname,             /* 2: SIOCSIWSTANAME */
                wvlan_get_station_nickname,             /* 3: SIOCGIWSTANAME */
#if 1 //;? (HCF_TYPE) & HCF_TYPE_STA
                wvlan_set_porttype,                     /* 4: SIOCSIWPORTTYPE */
                wvlan_get_porttype,                     /* 5: SIOCGIWPORTTYPE */
#endif
};
