switch(action) {

#ifdef temp
        case A_ODDQ:
            DECIDE((x1 & 1) && (y1 & 1));

        case A_EVENQ:
            DECIDE((x1 & 1) == 0 && (y1 & 1) == 0);
#endif
        case A_NEGATE:
            x1 = -x1;
            y1 = -y1;
            goto setPair;
#ifdef temp
        case A_COMPLEMENT:
            x1 = ~x1;
            y1 = ~y1;
            goto setPair;
#endif
        case A_ABSOLUTE:
            if (x1 < 0) x1 = -x1;
            if (y1 < 0) y1 = -y1;
            goto setPair;

        case A_ROUND:
            {
                REBDEC d64;
                n = Get_Round_Flags(call_);
                if (D_REF(2))
                    d64 = Dec64(D_ARG(3));
                else {
                    d64 = 1.0L;
                    n |= 1;
                }
                x1 = (REBD32)Round_Dec(x1, n, d64);
                y1 = (REBD32)Round_Dec(y1, n, d64);
            }
            goto setPair;

        case A_REVERSE:
            x2 = x1;
            x1 = y1;
            y1 = x2;
            goto setPair;

        case A_RANDOM:
            if (D_REF(2)) fail (Error(RE_BAD_REFINES)); // seed
            x1 = (REBD32)Random_Range((REBINT)x1, (REBOOL)D_REF(3));
            y1 = (REBD32)Random_Range((REBINT)y1, (REBOOL)D_REF(3));
            goto setPair;

        case A_PICK:
            assert(D_ARGC > 1);
            if (IS_WORD(arg)) {
                if (VAL_WORD_CANON(arg) == SYM_X)
                    n = 0;
                else if (VAL_WORD_CANON(arg) == SYM_Y)
                    n = 1;
                else
                    fail (Error_Invalid_Arg(arg));
            }
            else {
                n = Get_Num_Arg(arg);
                if (n < 1 || n > 2) fail (Error_Out_Of_Range(arg));
                n--;
            }
///     case A_POKE:
///         if (action == A_POKE) {
///             arg = D_ARG(3);
///             if (IS_INTEGER(arg)) {
///                 if (index == 0) x1 = VAL_INT32(arg);
///                 else y1 = VAL_INT32(arg);
///             }
///             else if (IS_DECIMAL(arg)) {
///                 if (index == 0) x1 = (REBINT)VAL_DECIMAL(arg);
///                 else y1 = (REBINT)VAL_DECIMAL(arg);
///             } else
///                 fail (Error_Invalid_Arg(arg));
///             goto setPair;
///         }
            SET_DECIMAL(D_OUT, n == 0 ? x1 : y1);
            return R_OUT;

        case A_MAKE:
        case A_TO:
            assert(D_ARGC > 1);
            val = D_ARG(2);

            if (IS_PAIR(val)) {
                *D_OUT = *val;
                return R_OUT;
            }
            if (IS_STRING(val)) {
                REBYTE *bp;
                REBCNT len;
                // -1234567890x-1234567890
                bp = Temp_Byte_Chars_May_Fail(val, VAL_LEN_AT(val), &len, FALSE);
                if (Scan_Pair(bp, len, D_OUT)) return R_OUT;
            }
            if (IS_INTEGER(val)) {
                x1 = y1 = (REBD32)VAL_INT64(val);
                goto setPair;
            }
            if (IS_DECIMAL(val)) {
                x1 = y1 = (REBD32)VAL_DECIMAL(val);
                goto setPair;
            }
            if (ANY_ARRAY(val) && VAL_LEN_AT(val) <= 2) {
                if (MT_Pair(D_OUT, val, REB_PAIR))
                    return R_OUT;
            }

            fail (Error_Bad_Make(REB_PAIR, val));
        }
