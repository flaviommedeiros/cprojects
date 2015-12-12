if ((*value == ':') &&
#ifdef _WIN32
               ((value[1] == '/') || (value[1] == '\\')))
#else
               (value[1] == '/')
