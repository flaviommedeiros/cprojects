xi_time_t xi_mktime(register struct xi_tm *timep)
{
    register long day, year;
    register int tm_year;
    int yday, month;
    register signed long seconds;
    int overflow;

    timep->tm_min += timep->tm_sec / 60;
    timep->tm_sec %= 60;
    if (timep->tm_sec < 0) {
         timep->tm_sec += 60;
         timep->tm_min--;
    }
    timep->tm_hour += timep->tm_min / 60;
    timep->tm_min = timep->tm_min % 60;
    if (timep->tm_min < 0) {
         timep->tm_min += 60;
         timep->tm_hour--;
    }
    day = timep->tm_hour / 24;
    timep->tm_hour= timep->tm_hour % 24;
    if (timep->tm_hour < 0) {
         timep->tm_hour += 24;
         day--;
    }
    timep->tm_year += timep->tm_mon / 12;
    timep->tm_mon %= 12;
    if (timep->tm_mon < 0) {
         timep->tm_mon += 12;
         timep->tm_year--;
    }
    day += (timep->tm_mday - 1);
    while (day < 0) {
         if(--timep->tm_mon < 0) {
                 timep->tm_year--;
                 timep->tm_mon = 11;
         }
         day += _ytab[LEAPYEAR(YEAR0 + timep->tm_year)][timep->tm_mon];
    }
    while (day >= _ytab[LEAPYEAR(YEAR0 + timep->tm_year)][timep->tm_mon]) {
         day -= _ytab[LEAPYEAR(YEAR0 + timep->tm_year)][timep->tm_mon];
         if (++(timep->tm_mon) == 12) {
                 timep->tm_mon = 0;
                 timep->tm_year++;
         }
    }
    timep->tm_mday = day + 1;
    year = EPOCH_YR;
    if (timep->tm_year < year - YEAR0) return (xi_time_t)-1;
    seconds = 0;
    day = 0;
    overflow = 0;

    /*
     * Assume that when day becomes negative, there will certainly be overflow on seconds.
     * The check for overflow needs not to be done for leapyears divisible by 400.
     * The code only works when year (1970) is not a leapyear.
     */
    #if EPOCH_YR != 1970
    #error EPOCH_YR != 1970
    #endif

    tm_year = timep->tm_year + YEAR0;

    if (LONG_MAX / 365 < tm_year - year) overflow++;
    day = (tm_year - year) * 365;
    if (LONG_MAX - day < (tm_year - year) / 4 + 1) overflow++;
    day += (tm_year - year) / 4
         + ((tm_year % 4) && tm_year % 4 < year % 4);
    day -= (tm_year - year) / 100
         + ((tm_year % 100) && tm_year % 100 < year % 100);
    day += (tm_year - year) / 400
         + ((tm_year % 400) && tm_year % 400 < year % 400);

    yday = month = 0;
    while (month < timep->tm_mon) {
         yday += _ytab[LEAPYEAR(tm_year)][month];
         month++;
    }
    yday += (timep->tm_mday - 1);
    if (day + yday < 0) overflow++;
    day += yday;

    timep->tm_yday = yday;
    timep->tm_wday = (day + 4) % 7;

    seconds = ( ( timep->tm_hour * 60L ) + timep->tm_min ) * 60L + timep->tm_sec;

    if ( ( TIME_MAX - seconds ) / SECS_DAY < ( unsigned long ) day ) overflow++;
    seconds += day * SECS_DAY;

    if ( overflow ) return ( xi_time_t ) - 1;

    if ( ( xi_time_t ) seconds != seconds) return ( xi_time_t ) - 1;
    return ( xi_time_t ) seconds;
}
