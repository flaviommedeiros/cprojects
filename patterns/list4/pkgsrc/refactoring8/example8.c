char	*int_fmt[] = {
			"%-1.5d",
			"%1.5d",
			"%123.9d",
			"%5.5d",
			"%10.5d",
			"% 10.5d",
			"%+22.33d",
			"%01.3d",
			"%4d",
#if defined(HAVE_LONG_LONG_INT)
			"%12lld",
#endif
			NULL
		 };
