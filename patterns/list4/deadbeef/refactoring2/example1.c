#ifdef HAVE_PER_THREAD_LOCALE
if (result == 0)
#endif
	    {
#ifdef IN_LIBGLOCALE
	      result = strcmp (s1->encoding, s2->encoding);
	      if (result == 0)
#endif
		/* We compare the category last (though this is the cheapest
		   operation) since it is hopefully always the same (namely
		   LC_MESSAGES).  */
		result = s1->category - s2->category;
	    }
