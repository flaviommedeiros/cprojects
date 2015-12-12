if (artyp == ISTAPE
#ifdef SUPPORT_RMT
		    || artyp == ISRMT
#endif /* SUPPORT_RMT */
		    ) {
			tty_prnt("%s ready for archive tape volume: %d\n",
				arcname, arvol);
			tty_prnt("Load the NEXT TAPE on the tape drive");
		} else
#endif /* SUPPORT_TAPE */
		{
			tty_prnt("%s ready for archive volume: %d\n",
				arcname, arvol);
			tty_prnt("Load the NEXT STORAGE MEDIA (if required)");
		}
