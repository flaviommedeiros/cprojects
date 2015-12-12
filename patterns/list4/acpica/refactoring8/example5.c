static const PR_DIRECTIVE_INFO      Gbl_DirectiveInfo[] =
{
    {"define",          1},
    {"elif",            0}, /* Converted to #else..#if internally */
    {"else",            0},
    {"endif",           0},
    {"error",           1},
    {"if",              1},
    {"ifdef",           1},
    {"ifndef",          1},
    {"include",         0}, /* Argument is not standard format, so just use 0 here */
    {"includebuffer",   0}, /* Argument is not standard format, so just use 0 here */
    {"line",            1},
    {"pragma",          1},
    {"undef",           1},
    {"warning",         1},
    {NULL,              0}
};
