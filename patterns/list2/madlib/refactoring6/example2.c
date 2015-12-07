if (!(fcinfo->context &&
          (IsA(fcinfo->context, AggState)
    #ifdef NOTGP
           || IsA(fcinfo->context, WindowAggState)
    #endif
          )))
        elog(
            ERROR,
            "UDF call to a function that only works for aggs (destructive pass by reference)");
