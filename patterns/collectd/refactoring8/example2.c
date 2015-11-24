static const translation_info_t nsstats_translation_table[] = /* {{{ */
{
  /* Requests */
  { "Requestv4",       "dns_request",  "IPv4"        },
  { "Requestv6",       "dns_request",  "IPv6"        },
  { "ReqEdns0",        "dns_request",  "EDNS0"       },
  { "ReqBadEDNSVer",   "dns_request",  "BadEDNSVer"  },
  { "ReqTSIG",         "dns_request",  "TSIG"        },
  { "ReqSIG0",         "dns_request",  "SIG0"        },
  { "ReqBadSIG",       "dns_request",  "BadSIG"      },
  { "ReqTCP",          "dns_request",  "TCP"         },
  /* Rejects */
  { "AuthQryRej",      "dns_reject",   "authorative" },
  { "RecQryRej",       "dns_reject",   "recursive"   },
  { "XfrRej",          "dns_reject",   "transfer"    },
  { "UpdateRej",       "dns_reject",   "update"      },
  /* Responses */
  { "Response",        "dns_response", "normal"      },
  { "TruncatedResp",   "dns_response", "truncated"   },
  { "RespEDNS0",       "dns_response", "EDNS0"       },
  { "RespTSIG",        "dns_response", "TSIG"        },
  { "RespSIG0",        "dns_response", "SIG0"        },
  /* Queries */
  { "QryAuthAns",      "dns_query",    "authorative" },
  { "QryNoauthAns",    "dns_query",    "nonauth"     },
  { "QryReferral",     "dns_query",    "referral"    },
  { "QryRecursion",    "dns_query",    "recursion"   },
  { "QryDuplicate",    "dns_query",    "dupliate"    },
  { "QryDropped",      "dns_query",    "dropped"     },
  { "QryFailure",      "dns_query",    "failure"     },
  /* Response codes */
  { "QrySuccess",      "dns_rcode",    "tx-NOERROR"  },
  { "QryNxrrset",      "dns_rcode",    "tx-NXRRSET"  },
  { "QrySERVFAIL",     "dns_rcode",    "tx-SERVFAIL" },
  { "QryFORMERR",      "dns_rcode",    "tx-FORMERR"  },
  { "QryNXDOMAIN",     "dns_rcode",    "tx-NXDOMAIN" }
#if 0
  { "XfrReqDone",      "type", "type_instance"       },
  { "UpdateReqFwd",    "type", "type_instance"       },
  { "UpdateRespFwd",   "type", "type_instance"       },
  { "UpdateFwdFail",   "type", "type_instance"       },
  { "UpdateDone",      "type", "type_instance"       },
  { "UpdateFail",      "type", "type_instance"       },
  { "UpdateBadPrereq", "type", "type_instance"       },
#endif
};
