if ((
#ifdef DUMP_CALL_TABLE
                     (cx->options & JSOPTION_LOGCALL_TOSOURCE) ||
#endif
                     (sprop->attrs & JSPROP_ENUMERATE)) &&
                    !(sprop->flags & SPROP_IS_ALIAS) &&
                    (!SCOPE_HAD_MIDDLE_DELETE(scope) ||
                     SCOPE_HAS_PROPERTY(scope, sprop))) {
                    length++;
                }
