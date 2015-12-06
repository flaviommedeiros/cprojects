static const translation_info_t resstats_translation_table[] = /* {{{ */
{
  /* Generic resolver information */
  { "Queryv4",         "dns_query",    "IPv4"        },
  { "Queryv6",         "dns_query",    "IPv6"        },
  { "Responsev4",      "dns_response", "IPv4"        },
  { "Responsev6",      "dns_response", "IPv6"        },
  /* Received response codes */
  { "NXDOMAIN",        "dns_rcode",    "rx-NXDOMAIN" },
  { "SERVFAIL",        "dns_rcode",    "rx-SERVFAIL" },
  { "FORMERR",         "dns_rcode",    "rx-FORMERR"  },
  { "OtherError",      "dns_rcode",    "rx-OTHER"    },
  { "EDNS0Fail",       "dns_rcode",    "rx-EDNS0Fail"},
  /* Received responses */
  { "Mismatch",        "dns_response", "mismatch"    },
  { "Truncated",       "dns_response", "truncated"   },
  { "Lame",            "dns_response", "lame"        },
  { "Retry",           "dns_query",    "retry"       },
#if 0
  { "GlueFetchv4",     "type", "type_instance" },
  { "GlueFetchv6",     "type", "type_instance" },
  { "GlueFetchv4Fail", "type", "type_instance" },
  { "GlueFetchv6Fail", "type", "type_instance" },
#endif
  /* DNSSEC information */
  { "ValAttempt",      "dns_resolver", "DNSSEC-attempt" },
  { "ValOk",           "dns_resolver", "DNSSEC-okay"    },
  { "ValNegOk",        "dns_resolver", "DNSSEC-negokay" },
  { "ValFail",         "dns_resolver", "DNSSEC-fail"    }
};
