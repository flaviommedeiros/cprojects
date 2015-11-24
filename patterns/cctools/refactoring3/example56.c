switch(errno) {
			#ifdef EACCES
			case EACCES:
			#endif

			#ifdef EROFS
			case EROFS:
			#endif

			#ifdef ENOENT
			case ENOENT:
			#endif

			#ifdef ENOTDIR
			case ENOTDIR:
			#endif

			#ifdef ELOOP
			case ELOOP:
			#endif
				result = xxstrdup("false");
				break;
			default:
				result = 0;
				break;
		}
