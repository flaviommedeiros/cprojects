static JSFunctionSpec boolean_methods[] = {
#if JS_HAS_TOSOURCE
    {js_toSource_str,   bool_toSource,          0,JSFUN_THISP_BOOLEAN,0},
#endif
    {js_toString_str,   bool_toString,          0,JSFUN_THISP_BOOLEAN,0},
    {js_valueOf_str,    bool_valueOf,           0,JSFUN_THISP_BOOLEAN,0},
    {0,0,0,0,0}
};
