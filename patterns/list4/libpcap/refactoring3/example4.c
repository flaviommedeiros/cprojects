switch (proto) {

		case ETHERTYPE_IP:
			proto = AF_INET;
			break;

#ifdef INET6
		case ETHERTYPE_IPV6:
			proto = AF_INET6;
			break;
#endif

		default:
			/*
			 * Not a type on which we support filtering.
			 * XXX - support those that have AF_ values
			 * #defined on this platform, at least?
			 */
			return gen_false();
		}
