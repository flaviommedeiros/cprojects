struct entry appdefaults_entries[] = {
    { "afslog", krb5_config_string, check_boolean, 0 },
    { "afs-use-524", krb5_config_string, check_524, 0 },
#if 0
    { "anonymous", krb5_config_string, check_boolean, 0 },
#endif
    { "encrypt", krb5_config_string, check_boolean, 0 },
    { "forward", krb5_config_string, check_boolean, 0 },
    { "forwardable", krb5_config_string, check_boolean, 0 },
    { "krb4_get_tickets", krb5_config_string, check_boolean, 0 },
    { "proxiable", krb5_config_string, check_boolean, 0 },
    { "renew_lifetime", krb5_config_string, check_time, 0 },
    { "no-addresses", krb5_config_string, check_boolean, 0 },
    { "pkinit_anchors", krb5_config_string, NULL, 0 },
    { "pkinit_pool", krb5_config_string, NULL, 0 },
    { "pkinit_require_eku", krb5_config_string, NULL, 0 },
    { "pkinit_require_hostname_match", krb5_config_string, NULL, 0 },
    { "pkinit_require_krbtgt_otherName", krb5_config_string, NULL, 0 },
    { "pkinit_revoke", krb5_config_string, NULL, 0 },
    { "pkinit_trustedCertifiers", krb5_config_string, check_boolean, 0 },
    { "pkinit_win2k", krb5_config_string, NULL, 0 },
    { "pkinit_win2k_require_binding", krb5_config_string, NULL, 0 },
    { "ticket_lifetime", krb5_config_string, check_time, 0 },
    { "", krb5_config_list, appdefaults_entries, 0 },
    { NULL, 0, NULL, 0 }
};
