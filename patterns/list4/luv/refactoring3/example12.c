switch (num) {
#ifdef AI_ADDRCONFIG
  case AI_ADDRCONFIG: return "addrconfig";
#endif
#ifdef AI_V4MAPPED
  case AI_V4MAPPED: return "v4mapped";
#endif
#ifdef AI_ALL
  case AI_ALL: return "all";
#endif
#ifdef AI_NUMERICHOST
  case AI_NUMERICHOST: return "numerichost";
#endif
#ifdef AI_PASSIVE
  case AI_PASSIVE: return "passive";
#endif
#ifdef AI_NUMERICSERV
  case AI_NUMERICSERV: return "numericserv";
#endif
  }
