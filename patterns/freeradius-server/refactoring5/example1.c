#ifdef HAVE_PCRE
if (!(*preg)->precompiled) {
		new_sc->preg = talloc_steal(new_sc, *preg);
		*preg = NULL;
	} else
#endif
	{
		new_sc->preg = *preg;
	}
