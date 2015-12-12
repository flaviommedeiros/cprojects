#ifdef CONFIG_SBNI_MULTILINE
if( (nl->state & FL_SLAVE)  ||  nl->link )
#endif
			nl->state |= FL_LINE_DOWN;
