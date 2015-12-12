static JSFunctionSpec exception_methods[] = {
#if JS_HAS_TOSOURCE
    {js_toSource_str,   exn_toSource,           0,0,3},
#endif
    {js_toString_str,   exn_toString,           0,0,0},
    {0,0,0,0,0}
};
