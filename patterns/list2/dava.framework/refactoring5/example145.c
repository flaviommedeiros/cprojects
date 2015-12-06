#ifdef IN6_IS_ADDR_V4MAPPED
if (IN6_IS_ADDR_V4MAPPED(&data->peer.sa_in6.sin6_addr))
					ret += 576;
				else
#endif
					ret += 1280;
