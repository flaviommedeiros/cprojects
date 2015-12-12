switch (*++format)
			{
				case '\0':
					--format;
					break;
				case 'A':
					pt = _add((t->tm_wday < 0 ||
							   t->tm_wday >= DAYSPERWEEK) ?
							  "?" : Locale->weekday[t->tm_wday],
							  pt, ptlim);
					continue;
				case 'a':
					pt = _add((t->tm_wday < 0 ||
							   t->tm_wday >= DAYSPERWEEK) ?
							  "?" : Locale->wday[t->tm_wday],
							  pt, ptlim);
					continue;
				case 'B':
					pt = _add((t->tm_mon < 0 ||
							   t->tm_mon >= MONSPERYEAR) ?
							  "?" : Locale->month[t->tm_mon],
							  pt, ptlim);
					continue;
				case 'b':
				case 'h':
					pt = _add((t->tm_mon < 0 ||
							   t->tm_mon >= MONSPERYEAR) ?
							  "?" : Locale->mon[t->tm_mon],
							  pt, ptlim);
					continue;
				case 'C':

					/*
					 * %C used to do a... _fmt("%a %b %e %X %Y", t);
					 * ...whereas now POSIX 1003.2 calls for something
					 * completely different. (ado, 1993-05-24)
					 */
					pt = _yconv(t->tm_year, TM_YEAR_BASE, 1, 0,
								pt, ptlim);
					continue;
				case 'c':
					{
						int			warn2 = IN_SOME;

						pt = _fmt(Locale->c_fmt, t, pt, ptlim, &warn2);
						if (warn2 == IN_ALL)
							warn2 = IN_THIS;
						if (warn2 > *warnp)
							*warnp = warn2;
					}
					continue;
				case 'D':
					pt = _fmt("%m/%d/%y", t, pt, ptlim, warnp);
					continue;
				case 'd':
					pt = _conv(t->tm_mday, "%02d", pt, ptlim);
					continue;
				case 'E':
				case 'O':

					/*
					 * C99 locale modifiers. The sequences	%Ec %EC %Ex %EX
					 * %Ey %EY	%Od %oe %OH %OI %Om %OM  %OS %Ou %OU %OV %Ow
					 * %OW %Oy are supposed to provide alternate
					 * representations.
					 */
					goto label;
				case 'e':
					pt = _conv(t->tm_mday, "%2d", pt, ptlim);
					continue;
				case 'F':
					pt = _fmt("%Y-%m-%d", t, pt, ptlim, warnp);
					continue;
				case 'H':
					pt = _conv(t->tm_hour, "%02d", pt, ptlim);
					continue;
				case 'I':
					pt = _conv((t->tm_hour % 12) ?
							   (t->tm_hour % 12) : 12,
							   "%02d", pt, ptlim);
					continue;
				case 'j':
					pt = _conv(t->tm_yday + 1, "%03d", pt, ptlim);
					continue;
				case 'k':

					/*
					 * This used to be...  _conv(t->tm_hour % 12 ? t->tm_hour
					 * % 12 : 12, 2, ' '); ...and has been changed to the
					 * below to match SunOS 4.1.1 and Arnold Robbins' strftime
					 * version 3.0. That is, "%k" and "%l" have been swapped.
					 * (ado, 1993-05-24)
					 */
					pt = _conv(t->tm_hour, "%2d", pt, ptlim);
					continue;
#ifdef KITCHEN_SINK
				case 'K':

					/*
					 * * After all this time, still unclaimed!
					 */
					pt = _add("kitchen sink", pt, ptlim);
					continue;
#endif   /* defined KITCHEN_SINK */
				case 'l':

					/*
					 * This used to be...  _conv(t->tm_hour, 2, ' '); ...and
					 * has been changed to the below to match SunOS 4.1.1 and
					 * Arnold Robbin's strftime version 3.0. That is, "%k" and
					 * "%l" have been swapped. (ado, 1993-05-24)
					 */
					pt = _conv((t->tm_hour % 12) ?
							   (t->tm_hour % 12) : 12,
							   "%2d", pt, ptlim);
					continue;
				case 'M':
					pt = _conv(t->tm_min, "%02d", pt, ptlim);
					continue;
				case 'm':
					pt = _conv(t->tm_mon + 1, "%02d", pt, ptlim);
					continue;
				case 'n':
					pt = _add("\n", pt, ptlim);
					continue;
				case 'p':
					pt = _add((t->tm_hour >= (HOURSPERDAY / 2)) ?
							  Locale->pm :
							  Locale->am,
							  pt, ptlim);
					continue;
				case 'R':
					pt = _fmt("%H:%M", t, pt, ptlim, warnp);
					continue;
				case 'r':
					pt = _fmt("%I:%M:%S %p", t, pt, ptlim, warnp);
					continue;
				case 'S':
					pt = _conv(t->tm_sec, "%02d", pt, ptlim);
					continue;
				case 'T':
					pt = _fmt("%H:%M:%S", t, pt, ptlim, warnp);
					continue;
				case 't':
					pt = _add("\t", pt, ptlim);
					continue;
				case 'U':
					pt = _conv((t->tm_yday + DAYSPERWEEK -
								t->tm_wday) / DAYSPERWEEK,
							   "%02d", pt, ptlim);
					continue;
				case 'u':

					/*
					 * From Arnold Robbins' strftime version 3.0: "ISO 8601:
					 * Weekday as a decimal number [1 (Monday) - 7]" (ado,
					 * 1993-05-24)
					 */
					pt = _conv((t->tm_wday == 0) ?
							   DAYSPERWEEK : t->tm_wday,
							   "%d", pt, ptlim);
					continue;
				case 'V':		/* ISO 8601 week number */
				case 'G':		/* ISO 8601 year (four digits) */
				case 'g':		/* ISO 8601 year (two digits) */
/*
 * From Arnold Robbins' strftime version 3.0: "the week number of the
 * year (the first Monday as the first day of week 1) as a decimal number
 * (01-53)."
 * (ado, 1993-05-24)
 *
 * From "http://www.ft.uni-erlangen.de/~mskuhn/iso-time.html" by Markus Kuhn:
 * "Week 01 of a year is per definition the first week which has the
 * Thursday in this year, which is equivalent to the week which contains
 * the fourth day of January. In other words, the first week of a new year
 * is the week which has the majority of its days in the new year. Week 01
 * might also contain days from the previous year and the week before week
 * 01 of a year is the last week (52 or 53) of the previous year even if
 * it contains days from the new year. A week starts with Monday (day 1)
 * and ends with Sunday (day 7). For example, the first week of the year
 * 1997 lasts from 1996-12-30 to 1997-01-05..."
 * (ado, 1996-01-02)
 */
					{
						int			year;
						int			base;
						int			yday;
						int			wday;
						int			w;

						year = t->tm_year;
						base = TM_YEAR_BASE;
						yday = t->tm_yday;
						wday = t->tm_wday;
						for (;;)
						{
							int			len;
							int			bot;
							int			top;

							len = isleap_sum(year, base) ?
								DAYSPERLYEAR :
								DAYSPERNYEAR;

							/*
							 * What yday (-3 ... 3) does the ISO year begin
							 * on?
							 */
							bot = ((yday + 11 - wday) %
								   DAYSPERWEEK) - 3;

							/*
							 * What yday does the NEXT ISO year begin on?
							 */
							top = bot -
								(len % DAYSPERWEEK);
							if (top < -3)
								top += DAYSPERWEEK;
							top += len;
							if (yday >= top)
							{
								++base;
								w = 1;
								break;
							}
							if (yday >= bot)
							{
								w = 1 + ((yday - bot) /
										 DAYSPERWEEK);
								break;
							}
							--base;
							yday += isleap_sum(year, base) ?
								DAYSPERLYEAR :
								DAYSPERNYEAR;
						}
						if (*format == 'V')
							pt = _conv(w, "%02d",
									   pt, ptlim);
						else if (*format == 'g')
						{
							*warnp = IN_ALL;
							pt = _yconv(year, base, 0, 1,
										pt, ptlim);
						}
						else
							pt = _yconv(year, base, 1, 1,
										pt, ptlim);
					}
					continue;
				case 'v':

					/*
					 * From Arnold Robbins' strftime version 3.0: "date as
					 * dd-bbb-YYYY" (ado, 1993-05-24)
					 */
					pt = _fmt("%e-%b-%Y", t, pt, ptlim, warnp);
					continue;
				case 'W':
					pt = _conv((t->tm_yday + DAYSPERWEEK -
								(t->tm_wday ?
								 (t->tm_wday - 1) :
								 (DAYSPERWEEK - 1))) / DAYSPERWEEK,
							   "%02d", pt, ptlim);
					continue;
				case 'w':
					pt = _conv(t->tm_wday, "%d", pt, ptlim);
					continue;
				case 'X':
					pt = _fmt(Locale->X_fmt, t, pt, ptlim, warnp);
					continue;
				case 'x':
					{
						int			warn2 = IN_SOME;

						pt = _fmt(Locale->x_fmt, t, pt, ptlim, &warn2);
						if (warn2 == IN_ALL)
							warn2 = IN_THIS;
						if (warn2 > *warnp)
							*warnp = warn2;
					}
					continue;
				case 'y':
					*warnp = IN_ALL;
					pt = _yconv(t->tm_year, TM_YEAR_BASE, 0, 1,
								pt, ptlim);
					continue;
				case 'Y':
					pt = _yconv(t->tm_year, TM_YEAR_BASE, 1, 1,
								pt, ptlim);
					continue;
				case 'Z':
					if (t->tm_zone != NULL)
						pt = _add(t->tm_zone, pt, ptlim);

					/*
					 * C99 says that %Z must be replaced by the empty string
					 * if the time zone is not determinable.
					 */
					continue;
				case 'z':
					{
						int			diff;
						char const *sign;

						if (t->tm_isdst < 0)
							continue;
						diff = t->tm_gmtoff;
						if (diff < 0)
						{
							sign = "-";
							diff = -diff;
						}
						else
							sign = "+";
						pt = _add(sign, pt, ptlim);
						diff /= 60;
						pt = _conv((diff / 60) * 100 + diff % 60,
								   "%04d", pt, ptlim);
					}
					continue;
				case '+':
					pt = _fmt(Locale->date_fmt, t, pt, ptlim,
							  warnp);
					continue;
				case '%':

					/*
					 * X311J/88-090 (4.12.3.5): if conversion char is
					 * undefined, behavior is undefined.  Print out the
					 * character itself as printf(3) also does.
					 */
				default:
					break;
			}
