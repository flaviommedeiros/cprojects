switch (*++format) {
            case '\0':
                --format;
                break;
            case 'A':
                pt = _add((t->tm_wday < 0 ||
                    t->tm_wday >= DAYSPERWEEK) ?
                    "?" : locale->weekday[t->tm_wday],
                    pt, ptlim, modifier);
                continue;
            case 'a':
                pt = _add((t->tm_wday < 0 ||
                    t->tm_wday >= DAYSPERWEEK) ?
                    "?" : locale->wday[t->tm_wday],
                    pt, ptlim, modifier);
                continue;
            case 'B':
                if (modifier == '-') {
                    pt = _add((t->tm_mon < 0 ||
                                t->tm_mon >= MONSPERYEAR) ?
                                "?" : locale->standalone_month[t->tm_mon],
                                pt, ptlim, modifier);
                } else {
                    pt = _add((t->tm_mon < 0 ||
                                t->tm_mon >= MONSPERYEAR) ?
                                "?" : locale->month[t->tm_mon],
                                pt, ptlim, modifier);
                }
                continue;
            case 'b':
            case 'h':
                pt = _add((t->tm_mon < 0 ||
                    t->tm_mon >= MONSPERYEAR) ?
                    "?" : locale->mon[t->tm_mon],
                    pt, ptlim, modifier);
                continue;
            case 'C':
                /*
                ** %C used to do a...
                **  _fmt("%a %b %e %X %Y", t);
                ** ...whereas now POSIX 1003.2 calls for
                ** something completely different.
                ** (ado, 1993-05-24)
                */
                pt = _yconv(t->tm_year, TM_YEAR_BASE, 1, 0,
                    pt, ptlim, modifier);
                continue;
            case 'c':
                {
                int warn2 = IN_SOME;

                pt = _fmt(locale->c_fmt, t, pt, ptlim, warnp, locale);
                if (warn2 == IN_ALL)
                    warn2 = IN_THIS;
                if (warn2 > *warnp)
                    *warnp = warn2;
                }
                continue;
            case 'D':
                                pt = _fmt("%m/%d/%y", t, pt, ptlim, warnp, locale);
                continue;
            case 'd':
                                pt = _conv(t->tm_mday,
                                           getformat(modifier, "%02d",
                                                     "%2d", "%d", "%02d"),
                                           pt, ptlim);
                continue;
            case 'E':
            case 'O':
                /*
                ** C99 locale modifiers.
                ** The sequences
                **  %Ec %EC %Ex %EX %Ey %EY
                **  %Od %oe %OH %OI %Om %OM
                **  %OS %Ou %OU %OV %Ow %OW %Oy
                ** are supposed to provide alternate
                ** representations.
                */
                goto label;
            case '_':
            case '-':
            case '0':
            case '^':
            case '#':
                modifier = *format;
                goto label;
            case 'e':
                pt = _conv(t->tm_mday,
                                           getformat(modifier, "%2d",
                                                     "%2d", "%d", "%02d"),
                                           pt, ptlim);
                continue;
            case 'F':
                pt = _fmt("%Y-%m-%d", t, pt, ptlim, warnp, locale);
                continue;
            case 'H':
                pt = _conv(t->tm_hour,
                                           getformat(modifier, "%02d",
                                                     "%2d", "%d", "%02d"),
                                           pt, ptlim);
                continue;
            case 'I':
                pt = _conv((t->tm_hour % 12) ?
                    (t->tm_hour % 12) : 12,
                    getformat(modifier, "%02d",
                                                  "%2d", "%d", "%02d"),
                                        pt, ptlim);
                continue;
            case 'j':
                pt = _conv(t->tm_yday + 1,
                           getformat(modifier, "%03d", "%3d", "%d", "%03d"),
                           pt, ptlim);
                continue;
            case 'k':
                /*
                ** This used to be...
                **  _conv(t->tm_hour % 12 ?
                **      t->tm_hour % 12 : 12, 2, ' ');
                ** ...and has been changed to the below to
                ** match SunOS 4.1.1 and Arnold Robbins'
                ** strftime version 3.0. That is, "%k" and
                ** "%l" have been swapped.
                ** (ado, 1993-05-24)
                */
                pt = _conv(t->tm_hour,
                                           getformat(modifier, "%2d",
                                                     "%2d", "%d", "%02d"),
                                           pt, ptlim);
                continue;
#ifdef KITCHEN_SINK
            case 'K':
                /*
                ** After all this time, still unclaimed!
                */
                pt = _add("kitchen sink", pt, ptlim, modifier);
                continue;
#endif /* defined KITCHEN_SINK */
            case 'l':
                /*
                ** This used to be...
                **  _conv(t->tm_hour, 2, ' ');
                ** ...and has been changed to the below to
                ** match SunOS 4.1.1 and Arnold Robbin's
                ** strftime version 3.0. That is, "%k" and
                ** "%l" have been swapped.
                ** (ado, 1993-05-24)
                */
                pt = _conv((t->tm_hour % 12) ?
                    (t->tm_hour % 12) : 12,
                    getformat(modifier, "%2d",
                                                  "%2d", "%d", "%02d"),
                                        pt, ptlim);
                continue;
            case 'M':
                pt = _conv(t->tm_min,
                                           getformat(modifier, "%02d",
                                                     "%2d", "%d", "%02d"),
                                           pt, ptlim);
                continue;
            case 'm':
                pt = _conv(t->tm_mon + 1,
                                           getformat(modifier, "%02d",
                                                     "%2d", "%d", "%02d"),
                                           pt, ptlim);
                continue;
            case 'n':
                pt = _add("\n", pt, ptlim, modifier);
                continue;
            case 'p':
                pt = _add((t->tm_hour >= (HOURSPERDAY / 2)) ?
                    locale->pm :
                    locale->am,
                    pt, ptlim, modifier);
                continue;
            case 'P':
                pt = _add((t->tm_hour >= (HOURSPERDAY / 2)) ?
                    locale->pm :
                    locale->am,
                    pt, ptlim, FORCE_LOWER_CASE);
                continue;
            case 'R':
                pt = _fmt("%H:%M", t, pt, ptlim, warnp, locale);
                continue;
            case 'r':
                pt = _fmt("%I:%M:%S %p", t, pt, ptlim, warnp, locale);
                continue;
            case 'S':
                pt = _conv(t->tm_sec,
                                           getformat(modifier, "%02d",
                                                     "%2d", "%d", "%02d"),
                                           pt, ptlim);
                continue;
            case 's':
                {
                    struct tm   tm;
                    char        buf[INT_STRLEN_MAXIMUM(
                                time64_t) + 1];
                    time64_t    mkt;

                    tm = *t;
                    mkt = mktime64(&tm);
                    if (TYPE_SIGNED(time64_t))
                        (void) sprintf(buf, "%lld",
                            (long long) mkt);
                    else    (void) sprintf(buf, "%llu",
                            (unsigned long long) mkt);
                    pt = _add(buf, pt, ptlim, modifier);
                }
                continue;
            case 'T':
                pt = _fmt("%H:%M:%S", t, pt, ptlim, warnp, locale);
                continue;
            case 't':
                pt = _add("\t", pt, ptlim, modifier);
                continue;
            case 'U':
                pt = _conv((t->tm_yday + DAYSPERWEEK -
                    t->tm_wday) / DAYSPERWEEK,
                    getformat(modifier, "%02d",
                                                  "%2d", "%d", "%02d"),
                                        pt, ptlim);
                continue;
            case 'u':
                /*
                ** From Arnold Robbins' strftime version 3.0:
                ** "ISO 8601: Weekday as a decimal number
                ** [1 (Monday) - 7]"
                ** (ado, 1993-05-24)
                */
                pt = _conv((t->tm_wday == 0) ?
                    DAYSPERWEEK : t->tm_wday, "%d", pt, ptlim);
                continue;
            case 'V':   /* ISO 8601 week number */
            case 'G':   /* ISO 8601 year (four digits) */
            case 'g':   /* ISO 8601 year (two digits) */
/*
** From Arnold Robbins' strftime version 3.0: "the week number of the
** year (the first Monday as the first day of week 1) as a decimal number
** (01-53)."
** (ado, 1993-05-24)
**
** From "http://www.ft.uni-erlangen.de/~mskuhn/iso-time.html" by Markus Kuhn:
** "Week 01 of a year is per definition the first week which has the
** Thursday in this year, which is equivalent to the week which contains
** the fourth day of January. In other words, the first week of a new year
** is the week which has the majority of its days in the new year. Week 01
** might also contain days from the previous year and the week before week
** 01 of a year is the last week (52 or 53) of the previous year even if
** it contains days from the new year. A week starts with Monday (day 1)
** and ends with Sunday (day 7). For example, the first week of the year
** 1997 lasts from 1996-12-30 to 1997-01-05..."
** (ado, 1996-01-02)
*/
                {
                    int year;
                    int base;
                    int yday;
                    int wday;
                    int w;

                    year = t->tm_year;
                    base = TM_YEAR_BASE;
                    yday = t->tm_yday;
                    wday = t->tm_wday;
                    for ( ; ; ) {
                        int len;
                        int bot;
                        int top;

                        len = isleap_sum(year, base) ?
                            DAYSPERLYEAR :
                            DAYSPERNYEAR;
                        /*
                        ** What yday (-3 ... 3) does
                        ** the ISO year begin on?
                        */
                        bot = ((yday + 11 - wday) %
                            DAYSPERWEEK) - 3;
                        /*
                        ** What yday does the NEXT
                        ** ISO year begin on?
                        */
                        top = bot -
                            (len % DAYSPERWEEK);
                        if (top < -3)
                            top += DAYSPERWEEK;
                        top += len;
                        if (yday >= top) {
                            ++base;
                            w = 1;
                            break;
                        }
                        if (yday >= bot) {
                            w = 1 + ((yday - bot) /
                                DAYSPERWEEK);
                            break;
                        }
                        --base;
                        yday += isleap_sum(year, base) ?
                            DAYSPERLYEAR :
                            DAYSPERNYEAR;
                    }
#ifdef XPG4_1994_04_09
                    if ((w == 52 &&
                        t->tm_mon == TM_JANUARY) ||
                        (w == 1 &&
                        t->tm_mon == TM_DECEMBER))
                            w = 53;
#endif /* defined XPG4_1994_04_09 */
                    if (*format == 'V')
                        pt = _conv(w,
                                                           getformat(modifier,
                                                                     "%02d",
                                                                     "%2d",
                                                                     "%d",
                                                                     "%02d"),
                               pt, ptlim);
                    else if (*format == 'g') {
                        *warnp = IN_ALL;
                        pt = _yconv(year, base, 0, 1,
                            pt, ptlim, modifier);
                    } else  pt = _yconv(year, base, 1, 1,
                            pt, ptlim, modifier);
                }
                continue;
            case 'v':
                /*
                ** From Arnold Robbins' strftime version 3.0:
                ** "date as dd-bbb-YYYY"
                ** (ado, 1993-05-24)
                */
                pt = _fmt("%e-%b-%Y", t, pt, ptlim, warnp, locale);
                continue;
            case 'W':
                pt = _conv((t->tm_yday + DAYSPERWEEK -
                    (t->tm_wday ?
                    (t->tm_wday - 1) :
                    (DAYSPERWEEK - 1))) / DAYSPERWEEK,
                    getformat(modifier, "%02d",
                                                  "%2d", "%d", "%02d"),
                                        pt, ptlim);
                continue;
            case 'w':
                pt = _conv(t->tm_wday, "%d", pt, ptlim);
                continue;
            case 'X':
                pt = _fmt(locale->X_fmt, t, pt, ptlim, warnp, locale);
                continue;
            case 'x':
                {
                int warn2 = IN_SOME;

                pt = _fmt(locale->x_fmt, t, pt, ptlim, &warn2, locale);
                if (warn2 == IN_ALL)
                    warn2 = IN_THIS;
                if (warn2 > *warnp)
                    *warnp = warn2;
                }
                continue;
            case 'y':
                *warnp = IN_ALL;
                pt = _yconv(t->tm_year, TM_YEAR_BASE, 0, 1,
                    pt, ptlim, modifier);
                continue;
            case 'Y':
                pt = _yconv(t->tm_year, TM_YEAR_BASE, 1, 1,
                    pt, ptlim, modifier);
                continue;
            case 'Z':
#ifdef TM_ZONE
                if (t->TM_ZONE != NULL)
                    pt = _add(t->TM_ZONE, pt, ptlim,
                                                  modifier);
                else
#endif /* defined TM_ZONE */
                if (t->tm_isdst >= 0)
                    pt = _add(tzname[t->tm_isdst != 0],
                        pt, ptlim, modifier);
                /*
                ** C99 says that %Z must be replaced by the
                ** empty string if the time zone is not
                ** determinable.
                */
                continue;
            case 'z':
                {
                int     diff;
                char const *    sign;

                if (t->tm_isdst < 0)
                    continue;
#ifdef TM_GMTOFF
                diff = t->TM_GMTOFF;
#else /* !defined TM_GMTOFF */
                /*
                ** C99 says that the UTC offset must
                ** be computed by looking only at
                ** tm_isdst. This requirement is
                ** incorrect, since it means the code
                ** must rely on magic (in this case
                ** altzone and timezone), and the
                ** magic might not have the correct
                ** offset. Doing things correctly is
                ** tricky and requires disobeying C99;
                ** see GNU C strftime for details.
                ** For now, punt and conform to the
                ** standard, even though it's incorrect.
                **
                ** C99 says that %z must be replaced by the
                ** empty string if the time zone is not
                ** determinable, so output nothing if the
                ** appropriate variables are not available.
                */
                if (t->tm_isdst == 0)
#ifdef USG_COMPAT
                    diff = -timezone;
#else /* !defined USG_COMPAT */
                    continue;
#endif /* !defined USG_COMPAT */
                else
#ifdef ALTZONE
                    diff = -altzone;
#else /* !defined ALTZONE */
                    continue;
#endif /* !defined ALTZONE */
#endif /* !defined TM_GMTOFF */
                if (diff < 0) {
                    sign = "-";
                    diff = -diff;
                } else  sign = "+";
                pt = _add(sign, pt, ptlim, modifier);
                diff /= SECSPERMIN;
                diff = (diff / MINSPERHOUR) * 100 +
                    (diff % MINSPERHOUR);
                pt = _conv(diff,
                                           getformat(modifier, "%04d",
                                                     "%4d", "%d", "%04d"),
                                           pt, ptlim);
                }
                continue;
            case '+':
                pt = _fmt(locale->date_fmt, t, pt, ptlim,
                    warnp, locale);
                continue;
            case '%':
            /*
            ** X311J/88-090 (4.12.3.5): if conversion char is
            ** undefined, behavior is undefined. Print out the
            ** character itself as printf(3) also does.
            */
            default:
                break;
            }
