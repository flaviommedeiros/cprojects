switch (proto) {
#ifdef CONFIG_NF_CT_PROTO_SCTP_MODULE
	case IPPROTO_SCTP:
		return false;
#endif
#ifdef CONFIG_NF_CT_PROTO_DCCP_MODULE
	case IPPROTO_DCCP:
		return false;
#endif
#ifdef CONFIG_NF_CT_PROTO_GRE_MODULE
	case IPPROTO_GRE:
		return false;
#endif
#ifdef CONFIG_NF_CT_PROTO_UDPLITE_MODULE
	case IPPROTO_UDPLITE:
		return false;
#endif
	default:
		return true;
	}
