#ifndef _NO_LONGLONG
if (flags & QUADINT)
				*GET_ARG(N, ap, quad_ptr_t) = ret;
			else 
#endif
			if (flags & LONGINT)
				*GET_ARG(N, ap, long_ptr_t) = ret;
			else if (flags & SHORTINT)
				*GET_ARG(N, ap, short_ptr_t) = ret;
			else
				*GET_ARG(N, ap, int_ptr_t) = ret;
