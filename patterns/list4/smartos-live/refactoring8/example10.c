static JSFunctionSpec regexp_methods[] = {
#if JS_HAS_TOSOURCE
    {js_toSource_str,   js_regexp_toString,     0,0,0},
#endif
    {js_toString_str,   js_regexp_toString,     0,0,0},
    {"compile",         regexp_compile,         1,0,0},
    {"exec",            regexp_exec,            0,0,0},
    {"test",            regexp_test,            0,0,0},
    {0,0,0,0,0}
};
