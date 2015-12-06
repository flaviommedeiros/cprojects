switch(errno) {
			#ifdef ENOENT
			case ENOENT:
			#endif

			#ifdef ENOTDIR
			case ENOTDIR:
			#endif

			#ifdef ELOOP
			case ELOOP:
			#endif

			#ifdef EACCES
			case EACCES:
			#endif
				result = xxstrdup("false");
				break;

			default:
				result = 0;
				break;
		}
