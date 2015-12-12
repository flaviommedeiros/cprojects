#  if HAVE_USELOCALE
if (locale == NULL)
#  endif
    {
      locale = _nl_locale_name_posix (category, categoryname);
      if (locale == NULL)
	{
	  locale = _nl_locale_name_default ();
	  locale_defaulted = 1;
	}
    }
