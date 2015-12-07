if( errno == ERANGE
#if LONG_MAX > INT_MAX
			|| num < INT_MIN || num > INT_MAX
#endif
			)
		{
			if( num <= INT_MIN )
			{
				num = INT_MIN;
				ShowError("script:conv_num: underflow detected, capping to %ld\n", num);
			}
			else//if( num >= INT_MAX )
			{
				num = INT_MAX;
				ShowError("script:conv_num: overflow detected, capping to %ld\n", num);
			}
			script_reportdata(data);
			script_reportsrc(st);
		}
