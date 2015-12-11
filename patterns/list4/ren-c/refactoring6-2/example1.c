while (
#ifdef COMP_LINES
        linenum=scan_state->line_count,
#endif
        ((token = Locate_Token(scan_state)) != TOKEN_END)
    ) {

        bp = scan_state->begin;
        ep = scan_state->end;
        len = (REBCNT)(ep - bp);

        if (token < 0) {    // Check for error tokens
            token = -token;
            scan_state->begin = scan_state->end; // skip malformed token
            goto syntax_error;
        }

        // Is output block buffer large enough?
        if (token >= TOKEN_WORD && SERIES_FULL(ARRAY_SERIES(emitbuf)))
            Extend_Series(ARRAY_SERIES(emitbuf), 1024);

        value = ARRAY_TAIL(emitbuf);
        SET_END(value);

        // If in a path, handle start of path /word or word//word cases:
        if (mode_char == '/' && *bp == '/') {
            SET_NONE(value);
            SET_ARRAY_LEN(emitbuf, ARRAY_LEN(emitbuf) + 1);
            scan_state->begin = bp + 1;
            continue;
        }

        // Check for new path: /word or word/word:
        if (
            (
                token == TOKEN_PATH
                || (
                    (
                        token == TOKEN_WORD
                        || token == TOKEN_LIT
                        || token == TOKEN_GET
                    )
                    && *ep == '/'
                )
            )
            && mode_char != '/'
        ) {
            block = Scan_Block(scan_state, '/');  // (could realloc emitbuf)
            value = ARRAY_TAIL(emitbuf);
            if (token == TOKEN_LIT) {
                token = REB_LIT_PATH;
                VAL_RESET_HEADER(ARRAY_HEAD(block), REB_WORD);
                assert(!VAL_WORD_TARGET(ARRAY_HEAD(block)));
            }
            else if (IS_GET_WORD(ARRAY_HEAD(block))) {
                if (*scan_state->end == ':') goto syntax_error;
                token = REB_GET_PATH;
                VAL_RESET_HEADER(ARRAY_HEAD(block), REB_WORD);
                assert(!VAL_WORD_TARGET(ARRAY_HEAD(block)));
            }
            else {
                if (*scan_state->end == ':') {
                    token = REB_SET_PATH;
                    scan_state->begin = ++(scan_state->end);
                } else token = REB_PATH;
            }
            VAL_RESET_HEADER(value, cast(enum Reb_Kind, token));
            VAL_ARRAY(value) = block;
            VAL_INDEX(value) = 0;
            token = TOKEN_PATH;
        } else {
            scan_state->begin = scan_state->end; // accept token
        }

        // Process each lexical token appropriately:
        switch (token) {  // (idea is that compiler selects computed branch)

        case TOKEN_NEWLINE:
#ifdef TEST_SCAN
            Wait_User("next...");
#endif
            line = TRUE;
            scan_state->head_line = ep;
            continue;

        case TOKEN_LIT:
        case TOKEN_GET:
            if (ep[-1] == ':') {
                if (len == 1 || mode_char != '/') goto syntax_error;
                len--, scan_state->end--;
            }
            bp++;
        case TOKEN_SET:
            len--;
            if (mode_char == '/' && token == TOKEN_SET) {
                token = TOKEN_WORD; // will be a PATH_SET
                scan_state->end--;  // put ':' back on end but not beginning
            }
        case TOKEN_WORD:
            if (len == 0) {bp--; goto syntax_error;}
            Val_Init_Word_Unbound(
                value,
                cast(enum Reb_Kind, REB_WORD + (token - TOKEN_WORD)),
                Make_Word(bp, len)
            );
            break;

        case TOKEN_REFINE:
            Val_Init_Word_Unbound(
                value, REB_REFINEMENT, Make_Word(bp + 1, len - 1)
            );
            break;

        case TOKEN_ISSUE:
            if (len == 1) {
                if (bp[1] == '(') {
                    token = TOKEN_CONSTRUCT;
                    goto syntax_error;
                }
                SET_NONE(value);  // A single # means NONE
            }
            else {
                REBCNT sym = Scan_Issue(bp + 1, len - 1);
                if (sym == SYM_0)
                    goto syntax_error;
                Val_Init_Word_Unbound(value, REB_ISSUE, sym);
            }
            break;

        case TOKEN_BLOCK_BEGIN:
        case TOKEN_PAREN_BEGIN:
            block = Scan_Block(
                scan_state, (token == TOKEN_BLOCK_BEGIN) ? ']' : ')'
            );
            // (above line could have realloced emitbuf)
            ep = scan_state->end;
            value = ARRAY_TAIL(emitbuf);
            if (scan_state->errors) {
                *value = *ARRAY_LAST(block); // Copy the error
                SET_ARRAY_LEN(emitbuf, ARRAY_LEN(emitbuf) + 1);
                goto exit_block;
            }
            Val_Init_Array(
                value,
                (token == TOKEN_BLOCK_BEGIN) ? REB_BLOCK : REB_PAREN,
                block
            );
            break;

        case TOKEN_PATH:
            break;

        case TOKEN_BLOCK_END:
            if (!mode_char) { mode_char = '['; goto extra_error; }
            else if (mode_char != ']') goto missing_error;
            else goto exit_block;

        case TOKEN_PAREN_END:
            if (!mode_char) { mode_char = '('; goto extra_error; }
            else if (mode_char != ')') goto missing_error;
            else goto exit_block;

        case TOKEN_INTEGER:     // or start of DATE
            if (*ep != '/' || mode_char == '/') {
                VAL_RESET_HEADER(value, REB_INTEGER);
                if (!Scan_Integer(&VAL_INT64(value), bp, len))
                    goto syntax_error;
            }
            else {              // A / and not in block
                token = TOKEN_DATE;
                while (*ep == '/' || IS_LEX_NOT_DELIMIT(*ep)) ep++;
                scan_state->begin = ep;
                len = (REBCNT)(ep - bp);
                if (ep != Scan_Date(bp, len, value)) goto syntax_error;
            }
            break;

        case TOKEN_DECIMAL:
        case TOKEN_PERCENT:
            // Do not allow 1.2/abc:
            VAL_RESET_HEADER(value, REB_DECIMAL);
            if (*ep == '/' || !Scan_Decimal(&VAL_DECIMAL(value), bp, len, 0))
                goto syntax_error;
            if (bp[len-1] == '%') {
                VAL_RESET_HEADER(value, REB_PERCENT);
                VAL_DECIMAL(value) /= 100.0;
            }
            break;

        case TOKEN_MONEY:
            // Do not allow $1/$2:
            if (*ep == '/') {ep++; goto syntax_error;}
            if (!Scan_Money(bp, len, value)) goto syntax_error;
            break;

        case TOKEN_TIME:
            if (bp[len-1] == ':' && mode_char == '/') { // could be path/10: set
                VAL_RESET_HEADER(value, REB_INTEGER);
                if (!Scan_Integer(&VAL_INT64(value), bp, len - 1))
                    goto syntax_error;
                scan_state->end--;  // put ':' back on end but not beginning
                break;
            }
            if (ep != Scan_Time(bp, len, value)) goto syntax_error;
            break;

        case TOKEN_DATE:
            while (*ep == '/' && mode_char != '/') {  // Is it a date/time?
                ep++;
                while (IS_LEX_NOT_DELIMIT(*ep)) ep++;
                len = (REBCNT)(ep - bp);
                if (len > 50) {
                    // prevent infinite loop, should never be longer than this
                    break;
                }
                scan_state->begin = ep;  // End point extended to cover time
            }
            if (ep != Scan_Date(bp, len, value)) goto syntax_error;
            break;

        case TOKEN_CHAR:
            bp += 2; // skip #"
            if (!Scan_UTF8_Char_Escapable(&VAL_CHAR(value), bp))
                goto syntax_error;
            VAL_RESET_HEADER(value, REB_CHAR);
            break;

        case TOKEN_STRING:
            // During scan above, string was stored in BUF_MOLD (with Uni width)
            Val_Init_String(value, Copy_String(BUF_MOLD, 0, -1));
            LABEL_SERIES(VAL_SERIES(value), "scan string");
            break;

        case TOKEN_BINARY:
            Scan_Binary(bp, len, value);
            LABEL_SERIES(VAL_SERIES(value), "scan binary");
            break;

        case TOKEN_PAIR:
            Scan_Pair(bp, len, value);
            break;

        case TOKEN_TUPLE:
            if (!Scan_Tuple(bp, len, value)) goto syntax_error;
            break;

        case TOKEN_FILE:
            Scan_File(bp, len, value);
            LABEL_SERIES(VAL_SERIES(value), "scan file");
            break;

        case TOKEN_EMAIL:
            Scan_Email(bp, len, value);
            LABEL_SERIES(VAL_SERIES(value), "scan email");
            break;

        case TOKEN_URL:
            Scan_URL(bp, len, value);
            LABEL_SERIES(VAL_SERIES(value), "scan url");
            break;

        case TOKEN_TAG:
            Scan_Any(bp+1, len-2, value, REB_TAG);
            LABEL_SERIES(VAL_SERIES(value), "scan tag");
            break;

        case TOKEN_CONSTRUCT:
            block = Scan_Full_Block(scan_state, ']');
            value = ARRAY_TAIL(emitbuf);
            SET_ARRAY_LEN(emitbuf, ARRAY_LEN(emitbuf) + 1); // Protect from GC
            Bind_Values_All_Deep(ARRAY_HEAD(block), Lib_Context);
            if (!Construct_Value(value, block)) {
                if (IS_END(value)) Val_Init_Block(value, block);
                fail (Error(RE_MALCONSTRUCT, value));
            }
            SET_ARRAY_LEN(emitbuf, ARRAY_LEN(emitbuf) - 1); // Unprotect
            break;

        case TOKEN_END:
            continue;

        default:
            SET_NONE(value);
        }

        if (line) {
            line = FALSE;
            VAL_SET_OPT(value, OPT_VALUE_LINE);
        }

#ifdef TEST_SCAN
        Print((REBYTE*)"%s - %s", Token_Names[token], Use_Buf(bp,ep));
        if (VAL_TYPE(value) >= REB_STRING && VAL_TYPE(value) <= REB_URL)
            Print_Str(VAL_BIN(value));
        //Wait_User(0);
#endif

#ifdef COMP_LINES
        VAL_LINE(value)=linenum;
        VAL_FLAGS(value)|=FLAGS_LINE;
#endif
        if (!IS_END(value))
            SET_ARRAY_LEN(emitbuf, ARRAY_LEN(emitbuf) + 1);
        else {
            REBFRM *error;
        syntax_error:
            error = Error_Bad_Scan(
                RE_INVALID,
                scan_state,
                cast(REBCNT, token),
                bp,
                cast(REBCNT, ep - bp)
            );
            if (GET_FLAG(scan_state->opts, SCAN_RELAX)) {
                Val_Init_Error(ARRAY_TAIL(emitbuf), error);
                SET_ARRAY_LEN(emitbuf, ARRAY_LEN(emitbuf) + 1);
                goto exit_block;
            }
            fail (error);

        missing_error:
            scan_state->line_count = start; // where block started
            scan_state->head_line = start_line;
        extra_error: {
                REBYTE tmp_buf[4];  // Temporary error string
                tmp_buf[0] = mode_char;
                tmp_buf[1] = 0;
                error = Error_Bad_Scan(
                    RE_MISSING,
                    scan_state,
                    cast(REBCNT, token),
                    tmp_buf,
                    1
                );
                if (GET_FLAG(scan_state->opts, SCAN_RELAX)) {
                    Val_Init_Error(ARRAY_TAIL(emitbuf), error);
                    SET_ARRAY_LEN(emitbuf, ARRAY_LEN(emitbuf) + 1);
                    goto exit_block;
                }
                fail (error);
            }
        }

        // Check for end of path:
        if (mode_char == '/') {
            if (*ep == '/') {
                ep++;
                scan_state->begin = ep;  // skip next /
                if (*ep != '(' && IS_LEX_DELIMIT(*ep)) {
                    token = TOKEN_PATH;
                    goto syntax_error;
                }
            }
            else goto exit_block;
        }

        // Added for load/next
        if (GET_FLAG(scan_state->opts, SCAN_ONLY) || just_once)
            goto exit_block;
    }
