switch (data_addr.su_family) {
		case AF_INET:
			a = (char *)&data_addr.si_su.su_sin.sin_addr;
			p = (char *)&data_addr.su_port;
			result = command("PORT %d,%d,%d,%d,%d,%d",
				 UC(a[0]), UC(a[1]), UC(a[2]), UC(a[3]),
				 UC(p[0]), UC(p[1]));
			break;
#ifdef INET6
		case AF_INET6: {
			uint8_t ua[sizeof(data_addr.si_su.su_sin6.sin6_addr)];
			uint8_t up[sizeof(data_addr.su_port)];

			memcpy(ua, &data_addr.si_su.su_sin6.sin6_addr,
			    sizeof(ua));
			memcpy(up, &data_addr.su_port, sizeof(up));
			
			result = command(
	"LPRT %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				 6, 16,
				  ua[0],  ua[1],  ua[2],  ua[3],
				  ua[4],  ua[5],  ua[6],  ua[7],
				  ua[8],  ua[9], ua[10], ua[11],
				 ua[12], ua[13], ua[14], ua[15],
				 2,
				 up[0], up[1]);
			break;
		}
#endif
		default:
			result = COMPLETE + 1; /* xxx */
		}
