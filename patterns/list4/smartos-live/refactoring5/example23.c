#ifdef DUMP_CALL_TABLE
if (cx->options & JSOPTION_LOGCALL_TOSOURCE) {
        const char *classname = OBJ_GET_CLASS(cx, obj)->name;
        size_t classnchars = strlen(classname);
        static const char classpropid[] = "C";
        const char *cp;
        size_t onchars = nchars;

        /* 2 for ': ', 2 quotes around classname, 2 for ', ' after. */
        classnchars += sizeof classpropid - 1 + 2 + 2;
        if (ida->length)
            classnchars += 2;

        /* 2 for the braces, 1 for the terminator */
        chars = (jschar *)
            realloc((ochars = chars),
                    (nchars + classnchars + 2 + 1) * sizeof(jschar));
        if (!chars) {
            free(ochars);
            goto error;
        }

        chars[nchars++] = '{';          /* 1 from the 2 braces */
        for (cp = classpropid; *cp; cp++)
            chars[nchars++] = (jschar) *cp;
        chars[nchars++] = ':';
        chars[nchars++] = ' ';          /* 2 for ': ' */
        chars[nchars++] = '"';
        for (cp = classname; *cp; cp++)
            chars[nchars++] = (jschar) *cp;
        chars[nchars++] = '"';          /* 2 quotes */
        if (ida->length) {
            chars[nchars++] = ',';
            chars[nchars++] = ' ';      /* 2 for ', ' */
        }

        JS_ASSERT(nchars - onchars == 1 + classnchars);
    } else
#endif
    chars[nchars++] = '{';
