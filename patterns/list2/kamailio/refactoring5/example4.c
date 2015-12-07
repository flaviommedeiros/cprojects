#ifdef HONOR_MADDR
if (u->maddr_val.s && u->maddr_val.len)
					dst_host=&u->maddr_val;
				else
#endif
					dst_host=&u->host;
