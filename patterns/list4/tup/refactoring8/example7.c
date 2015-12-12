static SQLITE_WSD FuncDef aDateTimeFuncs[] = {
#ifndef SQLITE_OMIT_DATETIME_FUNCS
    DFUNCTION(julianday,        -1, 0, 0, juliandayFunc ),
    DFUNCTION(date,             -1, 0, 0, dateFunc      ),
    DFUNCTION(time,             -1, 0, 0, timeFunc      ),
    DFUNCTION(datetime,         -1, 0, 0, datetimeFunc  ),
    DFUNCTION(strftime,         -1, 0, 0, strftimeFunc  ),
    DFUNCTION(current_time,      0, 0, 0, ctimeFunc     ),
    DFUNCTION(current_timestamp, 0, 0, 0, ctimestampFunc),
    DFUNCTION(current_date,      0, 0, 0, cdateFunc     ),
#else
    STR_FUNCTION(current_time,      0, "%H:%M:%S",          0, currentTimeFunc),
    STR_FUNCTION(current_date,      0, "%Y-%m-%d",          0, currentTimeFunc),
    STR_FUNCTION(current_timestamp, 0, "%Y-%m-%d %H:%M:%S", 0, currentTimeFunc),
#endif
  };
