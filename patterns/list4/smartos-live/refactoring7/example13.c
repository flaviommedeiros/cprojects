return js_InitArrayClass(cx, obj) &&
           js_InitBlockClass(cx, obj) &&
           js_InitBooleanClass(cx, obj) &&
           js_InitCallClass(cx, obj) &&
           js_InitExceptionClasses(cx, obj) &&
           js_InitMathClass(cx, obj) &&
           js_InitNumberClass(cx, obj) &&
           js_InitRegExpClass(cx, obj) &&
           js_InitStringClass(cx, obj) &&
#if JS_HAS_SCRIPT_OBJECT
           js_InitScriptClass(cx, obj) &&
#endif
#if JS_HAS_XML_SUPPORT
           js_InitXMLClasses(cx, obj) &&
#endif
#if JS_HAS_FILE_OBJECT
           js_InitFileClass(cx, obj) &&
#endif
#if JS_HAS_GENERATORS
           js_InitIteratorClasses(cx, obj) &&
#endif
           js_InitDateClass(cx, obj);
