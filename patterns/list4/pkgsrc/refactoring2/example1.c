#if !defined(NO_EDITCOMPLETE)
if (strchr(margv[0], ':') != NULL ||
			    !editing ||
			    el_parse(el, margc, (void *)margv) != 0)
#endif /* !NO_EDITCOMPLETE */
				fputs("?Invalid command.\n", ttyout);
