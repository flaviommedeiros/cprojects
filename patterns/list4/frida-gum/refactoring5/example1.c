#ifndef G_OS_WIN32
if (gum_is_debugger_present ())
  {
    g_print (
        "\n"
        "***\n"
        "NOTE: Skipping BoundsChecker tests because debugger is attached\n"
        "***\n"
        "\n");
  }
  else
#endif
  {
#ifdef G_OS_WIN32
    TEST_RUN_LIST (boundschecker);
#endif
  }
