static const int supported_nids[] = {
        NID_netscape_cert_type, /* 71 */
        NID_key_usage,          /* 83 */
        NID_subject_alt_name,   /* 85 */
        NID_basic_constraints,  /* 87 */
        NID_certificate_policies, /* 89 */
        NID_ext_key_usage,      /* 126 */
#ifndef OPENSSL_NO_RFC3779
        NID_sbgp_ipAddrBlock,   /* 290 */
        NID_sbgp_autonomousSysNum, /* 291 */
#endif
        NID_policy_constraints, /* 401 */
        NID_proxyCertInfo,      /* 663 */
        NID_name_constraints,   /* 666 */
        NID_policy_mappings,    /* 747 */
        NID_inhibit_any_policy  /* 748 */
    };
