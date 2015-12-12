const char *formulae[] =
  {
    "1",
    "2.1",
#if defined(WIN32) && !defined(CYGWIN)
    "2.100000e-010",
#else
    "2.100000e-10",
#endif
    "foo",
    "1 + foo",
    "1 + 2",
    "1 + 2 * 3",
    "(1 - 2) * 3",
    "1 + -2 / 3",
    "1 + -2.000000e-100 / 3",
    "1 - -foo / 3",
    "2 * foo^bar + 3.1",
    "foo()",
    "foo(1)",
    "foo(1, bar)",
    "foo(1, bar, 2^-3)",
    "a / b * c",
    "a / (b * c)",
    "1 + 2 + 3",
    "pow(x, y)",
    ""
  };
