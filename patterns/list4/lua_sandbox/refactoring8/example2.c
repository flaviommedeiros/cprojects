const char* outputs[] = {
    "{\"time\":0,\"rows\":3,\"columns\":3,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Add_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Set_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Get_column\",\"unit\":\"count\",\"aggregation\":\"sum\"}]}\n1\t1\t1\n2\t1\t2\n3\t1\t3\n"
#ifdef LUA_JIT
    , "{\"time\":0,\"rows\":3,\"columns\":3,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Add_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Set_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Get_column\",\"unit\":\"count\",\"aggregation\":\"sum\"}]}\n0\t1\t1\t1\n1\t2\t1\t2\n2\t3\t1\t3\n"
#else
    , "{\"time\":0,\"rows\":3,\"columns\":3,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Add_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Set_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Get_column\",\"unit\":\"count\",\"aggregation\":\"sum\"}]}\n1\t2\t1\t2\n2\t3\t1\t3\n0\t1\t1\t1\n"
#endif
    , "{\"time\":0,\"rows\":3,\"columns\":3,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Add_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Set_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Get_column\",\"unit\":\"count\",\"aggregation\":\"sum\"}]}\n1\t1\t1\n2\t1\t2\n3\t1\t3\n"
    , ""
    , "{\"time\":0,\"rows\":3,\"columns\":3,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Add_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Set_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Get_column\",\"unit\":\"count\",\"aggregation\":\"sum\"}]}\n2\tnan\tnan\tnan\n"
    , "{\"time\":0,\"rows\":2,\"columns\":2,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Sum_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Min\",\"unit\":\"count\",\"aggregation\":\"min\"}]}\n0\t2\t5\n"
    , "{\"time\":0,\"rows\":2,\"columns\":2,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Sum_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Min\",\"unit\":\"count\",\"aggregation\":\"min\"}]}\n0\t3\t8\n"
    , "{\"time\":0,\"rows\":2,\"columns\":2,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Sum_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Min\",\"unit\":\"count\",\"aggregation\":\"min\"}]}\n0\tnan\t9\n"
    , "{\"time\":0,\"rows\":2,\"columns\":2,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Sum_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Min\",\"unit\":\"count\",\"aggregation\":\"min\"}]}\n0\tnan\t10\n"
    , "{\"time\":0,\"rows\":2,\"columns\":2,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Sum_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Min\",\"unit\":\"count\",\"aggregation\":\"min\"}]}\n0\t1\tnan\n"
    , "{\"time\":0,\"rows\":2,\"columns\":2,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Sum_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Min\",\"unit\":\"count\",\"aggregation\":\"min\"}]}\n0\t1\tnan\n"
    , "{\"time\":0,\"rows\":2,\"columns\":2,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Sum_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Min\",\"unit\":\"count\",\"aggregation\":\"min\"}]}\n0\t-2\t0\n"
    , ""
    , "{\"time\":0,\"rows\":2,\"columns\":2,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Sum_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Min\",\"unit\":\"count\",\"aggregation\":\"min\"}]}\n0\t3\t4\n"
    , "{\"time\":0,\"rows\":3,\"columns\":3,\"seconds_per_row\":1,\"column_info\":[{\"name\":\"Add_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Set_column\",\"unit\":\"count\",\"aggregation\":\"sum\"},{\"name\":\"Get_column\",\"unit\":\"count\",\"aggregation\":\"sum\"}]}\n0\tinf\t-inf\tinf\n"
    , NULL
  };
