#if ENABLE_LOCALE_SUPPORT
if (strcoll(p->text, q->text) < 0)
#else
		if (strcmp(p->text, q->text) < 0)
#endif
						{
			*lpp = p;
			lpp = &p->next;
			p = *lpp;
			if (p == NULL) {
				*lpp = q;
				break;
			}
		} else {
			*lpp = q;
			lpp = &q->next;
			q = *lpp;
			if (q == NULL) {
				*lpp = p;
				break;
			}
		}
