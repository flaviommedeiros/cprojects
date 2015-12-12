static JSFunctionSpec string_functions[] = {
    {js_escape_str,             js_str_escape,              1,0,0},
    {js_unescape_str,           str_unescape,               1,0,0},
#if JS_HAS_UNEVAL
    {js_uneval_str,             str_uneval,                 1,0,0},
#endif
    {js_decodeURI_str,          str_decodeURI,              1,0,0},
    {js_encodeURI_str,          str_encodeURI,              1,0,0},
    {js_decodeURIComponent_str, str_decodeURI_Component,    1,0,0},
    {js_encodeURIComponent_str, str_encodeURI_Component,    1,0,0},

    {0,0,0,0,0}
};
