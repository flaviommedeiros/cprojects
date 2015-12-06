static SQLITE_WSD FuncDef aDateTimeFuncs[] = {
#ifndef SQLITE_OMIT_DATETIME_FUNCS
    FUNCTION(julianday,        -1, 0, 0, juliandayFunc ),
    FUNCTION(date,             -1, 0, 0, dateFunc      ),
    FUNCTION(time,             -1, 0, 0, timeFunc      ),
    FUNCTION(datetime,         -1, 0, 0, datetimeFunc  ),
    FUNCTION(strftime,         -1, 0, 0, strftimeFunc  ),
    FUNCTION(current_time,      0, 0, 0, ctimeFunc     ),
    FUNCTION(current_timestamp, 0, 0, 0, ctimestampFunc),
    FUNCTION(current_date,      0, 0, 0, cdateFunc     ),
#else
    STR_FUNCTION(current_time,      0, "%H:%M:%S",          0, currentTimeFunc),
    STR_FUNCTION(current_date,      0, "%Y-%m-%d",          0, currentTimeFunc),
    STR_FUNCTION(current_timestamp, 0, "%Y-%m-%d %H:%M:%S", 0, currentTimeFunc),
#endif
  };
