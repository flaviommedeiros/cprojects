struct test_case tests[] = {
  { "testStatus",           &testStatus           },
  { "testFilterClusterLog", &testFilterClusterLog },
  /*{ "testSetLogLevelClusterLog", &testSetLogLevelClusterLog },*/
  /*{ "testSetLogLevelNode",  &testSetLogLevelNode  },*/
  { "testRestartNode",      &testRestartNode      },
  { "testGetStatPort",      &testGetStatPort      },
#ifdef VM_TRACE
  { "testLogSignals",       &testLogSignals       },
  { "testStartSignalLog",   &testStartSignalLog   },
  { "testStopSignalLog",    &testStopSignalLog    },
  { "testSetTrace",         &testSetTrace         },
  { "testDumpState",        &testDumpState        },
  { "testInsertError",      &testInsertError      }
#endif
};
