#ifdef TCC_TARGET_PE
if ((other & 2) && can_add_underscore) {
            sprintf(buf1, "_%s@%d", name, FUNC_ARGS(attr));
            name = buf1;
        } else
#endif
        if (tcc_state->leading_underscore && can_add_underscore) {
            buf1[0] = '_';
            pstrcpy(buf1 + 1, sizeof(buf1) - 1, name);
            name = buf1;
        }
