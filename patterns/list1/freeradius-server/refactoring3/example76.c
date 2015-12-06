switch (type) {
	case PW_TYPE_STRING :
		return talloc_typed_strdup(ctx, "_");

	case PW_TYPE_INTEGER64:
	case PW_TYPE_SIGNED:
	case PW_TYPE_BYTE:
	case PW_TYPE_SHORT:
	case PW_TYPE_INTEGER:
	case PW_TYPE_DATE :
		return talloc_typed_strdup(ctx, "0");

	case PW_TYPE_IPV4_ADDR :
		return talloc_typed_strdup(ctx, "?.?.?.?");

	case PW_TYPE_IPV4_PREFIX:
		return talloc_typed_strdup(ctx, "?.?.?.?/?");

	case PW_TYPE_IPV6_ADDR:
		return talloc_typed_strdup(ctx, "[:?:]");

	case PW_TYPE_IPV6_PREFIX:
		return talloc_typed_strdup(ctx, "[:?:]/?");

	case PW_TYPE_OCTETS:
		return talloc_typed_strdup(ctx, "??");

	case PW_TYPE_ETHERNET:
		return talloc_typed_strdup(ctx, "??:??:??:??:??:??:??:??");

#ifdef WITH_ASCEND_BINARY
	case PW_TYPE_ABINARY:
		return talloc_typed_strdup(ctx, "??");
#endif

	default :
		break;
	}
