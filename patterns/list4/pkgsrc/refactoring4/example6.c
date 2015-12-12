#ifdef NET2_REGEX
if (regexec(pt->rcmp, inpt) == 0)
#else
			if (regexec(&(pt->rcmp), inpt, MAXSUBEXP, pm, 0) != 0)
#endif
				break;
