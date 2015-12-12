return "Ethernet Packet transports"
#if defined (HAVE_PCAP_NETWORK)
     ":PCAP"
#endif
#if defined (HAVE_TAP_NETWORK)
     ":TAP"
#endif
#if defined (HAVE_VDE_NETWORK)
     ":VDE"
#endif
#if defined (HAVE_SLIRP_NETWORK)
     ":NAT"
#endif
     ":UDP";
