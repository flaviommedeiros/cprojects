switch (num) {
#ifdef SOCK_STREAM
  case SOCK_STREAM: return "stream";
#endif
#ifdef SOCK_DGRAM
  case SOCK_DGRAM: return "dgram";
#endif
#ifdef SOCK_SEQPACKET
  case SOCK_SEQPACKET: return "seqpacket";
#endif
#ifdef SOCK_RAW
  case SOCK_RAW: return "raw";
#endif
#ifdef SOCK_RDM
  case SOCK_RDM: return "rdm";
#endif
  }
