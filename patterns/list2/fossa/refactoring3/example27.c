switch (rr->rtype) {
    case NS_DNS_A_RECORD:
      if (data_len < sizeof(struct in_addr)) {
        return -1;
      }
      if (rr->rdata.p + data_len > msg->pkt.p + msg->pkt.len) {
        return -1;
      }
      memcpy(data, rr->rdata.p, data_len);
      return 0;
#ifdef NS_ENABLE_IPV6
    case NS_DNS_AAAA_RECORD:
      if (data_len < sizeof(struct in6_addr)) {
        return -1; /* LCOV_EXCL_LINE */
      }
      memcpy(data, rr->rdata.p, data_len);
      return 0;
#endif
    case NS_DNS_CNAME_RECORD:
      ns_dns_uncompress_name(msg, &rr->rdata, (char *) data, data_len);
      return 0;
  }
