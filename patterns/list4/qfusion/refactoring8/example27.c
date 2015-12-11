UNITTEST_START

  const char *values[] = {
    /* -E parameter */        /* exp. cert name */  /* exp. passphrase */
    "foo:bar:baz",            "foo",                "bar:baz",
    "foo\\:bar:baz",          "foo:bar",            "baz",
    "foo\\\\:bar:baz",        "foo\\",              "bar:baz",
    "foo:bar\\:baz",          "foo",                "bar\\:baz",
    "foo:bar\\\\:baz",        "foo",                "bar\\\\:baz",
    "foo\\bar\\baz",          "foo\\bar\\baz",      NULL,
    "foo\\\\bar\\\\baz",      "foo\\bar\\baz",      NULL,
    "foo\\",                  "foo\\",              NULL,
    "foo\\\\",                "foo\\",              NULL,
    "foo:bar\\",              "foo",                "bar\\",
    "foo:bar\\\\",            "foo",                "bar\\\\",
    "foo:bar:",               "foo",                "bar:",
    "foo\\::bar\\:",          "foo:",               "bar\\:",
#ifdef WIN32
    "c:\\foo:bar:baz",        "c:\\foo",            "bar:baz",
    "c:\\foo\\:bar:baz",      "c:\\foo:bar",        "baz",
    "c:\\foo\\\\:bar:baz",    "c:\\foo\\",          "bar:baz",
    "c:\\foo:bar\\:baz",      "c:\\foo",            "bar\\:baz",
    "c:\\foo:bar\\\\:baz",    "c:\\foo",            "bar\\\\:baz",
    "c:\\foo\\bar\\baz",      "c:\\foo\\bar\\baz",  NULL,
    "c:\\foo\\\\bar\\\\baz",  "c:\\foo\\bar\\baz",  NULL,
    "c:\\foo\\",              "c:\\foo\\",          NULL,
    "c:\\foo\\\\",            "c:\\foo\\",          NULL,
    "c:\\foo:bar\\",          "c:\\foo",            "bar\\",
    "c:\\foo:bar\\\\",        "c:\\foo",            "bar\\\\",
    "c:\\foo:bar:",           "c:\\foo",            "bar:",
    "c:\\foo\\::bar\\:",      "c:\\foo:",           "bar\\:",
#endif
    NULL,                     NULL,                 NULL,
  };
