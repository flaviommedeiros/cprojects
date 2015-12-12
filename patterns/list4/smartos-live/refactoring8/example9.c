static JSFunctionSpec number_methods[] = {
#if JS_HAS_TOSOURCE
    {js_toSource_str,       num_toSource,       0,JSFUN_THISP_NUMBER,0},
#endif
    {js_toString_str,       num_toString,       0,JSFUN_THISP_NUMBER,0},
    {js_toLocaleString_str, num_toLocaleString, 0,JSFUN_THISP_NUMBER,0},
    {js_valueOf_str,        num_valueOf,        0,JSFUN_THISP_NUMBER,0},
    {"toFixed",             num_toFixed,        1,JSFUN_THISP_NUMBER,0},
    {"toExponential",       num_toExponential,  1,JSFUN_THISP_NUMBER,0},
    {"toPrecision",         num_toPrecision,    1,JSFUN_THISP_NUMBER,0},
    {0,0,0,0,0}
};
