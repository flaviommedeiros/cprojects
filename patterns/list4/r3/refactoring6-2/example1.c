while (
#ifdef COMP_LINES
		linenum=scan_state->line_count,
#endif
		((token = Scan_Token(scan_state)) != TOKEN_EOF)
	) {

		bp = scan_state->begin;
		ep = scan_state->end;
		len = (REBCNT)(ep - bp);

		if (token < 0) {	// Check for error tokens
			token = -token;
			ACCEPT_TOKEN(scan_state);
			goto syntax_error;
		}

		// Is output block buffer large enough?
		if (token >= TOKEN_WORD && SERIES_FULL(emitbuf))
			Extend_Series(emitbuf, 1024);

		value = BLK_TAIL(emitbuf);
		SET_END(value);
		// Line opt was set here. Moved to end in 3.0.

        // If in a path, handle start of path /word or word//word cases:
        if (mode_char == '/' && *bp == '/') {
			SET_NONE(value);
			emitbuf->tail++;
			scan_state->begin = bp + 1;
			continue;
        }

        // Check for new path: /word or word/word:
        if ((token == TOKEN_PATH || ((token == TOKEN_WORD || token == TOKEN_LIT ||
				token == TOKEN_GET) && *ep == '/'))
					&& mode_char != '/') {
			//line = VAL_GET_LINE(value);
			block = Scan_Block(scan_state, '/');  // (could realloc emitbuf)
			value = BLK_TAIL(emitbuf);
			VAL_SERIES(value) = block;
			if (token == TOKEN_LIT) {
				token = REB_LIT_PATH;
				VAL_SET(BLK_HEAD(block), REB_WORD); // NO_FRAME
			}
			else if (IS_GET_WORD(BLK_HEAD(block))) {
				if (*scan_state->end == ':') goto syntax_error;
				token = REB_GET_PATH;
				VAL_SET(BLK_HEAD(block), REB_WORD); // NO_FRAME
			}
			else {
				if (*scan_state->end == ':') {
					token = REB_SET_PATH;
					scan_state->begin = ++(scan_state->end);
				} else token = REB_PATH;
			}
//			if (IS_SET_WORD(BLK_SKIP(block, block->tail - 1)
			VAL_SET(value, token);
			VAL_INDEX(value) = 0;
			//if (line) line = FALSE, VAL_SET_LINE(value);
			token = TOKEN_PATH;
        } else {
            ACCEPT_TOKEN(scan_state);
        }

		// Process each lexical token appropriately:
		switch (token) {  // (idea is that compiler selects computed branch)

		case TOKEN_LINE:
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
				scan_state->end--;	// put ':' back on end but not beginning
			}
		case TOKEN_WORD:
			if (len == 0) {bp--; goto syntax_error;}
			VAL_SET(value, (REBYTE)(REB_WORD + (token - TOKEN_WORD))); // NO_FRAME
			if (!(VAL_WORD_SYM(value) = Make_Word(bp, len))) goto syntax_error;
			VAL_WORD_FRAME(value) = 0;
			break;

		case TOKEN_REFINE:
			VAL_SET(value, REB_REFINEMENT); // NO_FRAME
			if (!(VAL_WORD_SYM(value) = Make_Word(bp+1, len-1))) goto syntax_error;
			break;

		case TOKEN_ISSUE:
			if (len == 1) {
				if (bp[1] == '(') {token = TOKEN_CONSTRUCT; goto syntax_error;}
				SET_NONE(value);  // A single # means NONE
			}
			else {
				VAL_SET(value, REB_ISSUE); // NO_FRAME
				if (!(VAL_WORD_SYM(value) = Scan_Issue(bp+1, len-1))) goto syntax_error;
			}
			break;

		case TOKEN_BLOCK:
		case TOKEN_PAREN:
			//line = VAL_GET_LINE(value);
			block = Scan_Block(scan_state, (REBYTE)((token == TOKEN_BLOCK) ? ']' : ')'));
			// (above line could have realloced emitbuf)
			ep = scan_state->end;
			value = BLK_TAIL(emitbuf);
			if (scan_state->errors) {
				*value = *BLK_LAST(block); // Copy the error
				emitbuf->tail++;
				goto exit_block;
			}
			VAL_SERIES(value) = block;
			VAL_SET(value, (REBYTE)((token == TOKEN_BLOCK) ? REB_BLOCK : REB_PAREN));
			VAL_INDEX(value) = 0;
			//if (line) line = FALSE, VAL_SET_LINE(value);
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

		case TOKEN_INTEGER:		// or start of DATE
            if (*ep != '/' || mode_char == '/') {
				if (0 == Scan_Integer(bp, len, value))
					goto syntax_error;
			}
			else {				// A / and not in block
				token = TOKEN_DATE;
				while (*ep == '/' || IS_LEX_AT_LEAST_SPECIAL(*ep)) ep++;
				scan_state->begin = ep;
				len = (REBCNT)(ep - bp);
				if (ep != Scan_Date(bp, len, value)) goto syntax_error;
            }
			break;

		case TOKEN_DECIMAL:
		case TOKEN_PERCENT:
			// Do not allow 1.2/abc:
			if (*ep == '/' || !Scan_Decimal(bp, len, value, 0)) goto syntax_error;
			if (bp[len-1] == '%') {
				VAL_SET(value, REB_PERCENT);
				VAL_DECIMAL(value) /= 100.0;
			}
			break;

		case TOKEN_MONEY:
			// Do not allow $1/$2:
			if (*ep == '/') {ep++; goto syntax_error;}
			if (!Scan_Money(bp, len, value)) goto syntax_error;
			break;

		case TOKEN_TIME:
			if (bp[len-1] == ':' && mode_char == '/') {	// could be path/10: set
				if (!Scan_Integer(bp, len-1, value)) goto syntax_error;
				scan_state->end--;	// put ':' back on end but not beginning
				break;
			}
			if (ep != Scan_Time(bp, len, value)) goto syntax_error;
			break;

		case TOKEN_DATE:
			while (*ep == '/' && mode_char != '/') {  // Is it a date/time?
				ep++;
				while (IS_LEX_AT_LEAST_SPECIAL(*ep)) ep++;
				len = (REBCNT)(ep - bp);
				if (len > 50) break; // prevent inf-loop - should never be longer than this
				scan_state->begin = ep;  // End point extended to cover time
            }
			if (ep != Scan_Date(bp, len, value)) goto syntax_error;
			break;

		case TOKEN_CHAR:
			bp += 2; // skip #"
			VAL_CHAR(value) = Scan_Char(&bp);
			bp++; // skip end "
			VAL_SET(value, REB_CHAR);
			break;

		case TOKEN_STRING:
			// During scan above, string was stored in BUF_MOLD (with Uni width)
			Set_String(value, Copy_String(BUF_MOLD, 0, -1));
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
			value = BLK_TAIL(emitbuf);
			emitbuf->tail++; // Protect the block from GC
//			if (!Construct_Simple(value, block)) {
			Bind_Block(Lib_Context, BLK_HEAD(block), BIND_ALL|BIND_DEEP);
			//Bind_Global_Block(BLK_HEAD(block));
			if (!Construct_Value(value, block)) {
				if (IS_END(value)) Set_Block(value, block);
				Trap1(RE_MALCONSTRUCT, value);
			}
			emitbuf->tail--; // Unprotect
			break;

		case TOKEN_EOF: continue;

		default: ;
			SET_NONE(value);
		}

		if (line) {
			line = FALSE;
			VAL_SET_LINE(value);
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
		if (VAL_TYPE(value)) emitbuf->tail++;
		else {
		syntax_error:
			value = BLK_TAIL(emitbuf);
			Scan_Error(RE_INVALID, scan_state, (REBCNT)token, bp, (REBCNT)(ep-bp), GET_FLAG(scan_state->opts, SCAN_RELAX) ? value : 0);
			emitbuf->tail++;
			goto exit_block;
		missing_error:
			scan_state->line_count = start;	// where block started
			scan_state->head_line = start_line;
		extra_error: {
				REBYTE tmp_buf[4];	// Temporary error string
				tmp_buf[0] = mode_char;
				tmp_buf[1] = 0;
				value = BLK_TAIL(emitbuf);
				Scan_Error(RE_MISSING, scan_state, (REBCNT)token, tmp_buf, 1, GET_FLAG(scan_state->opts, SCAN_RELAX) ? value : 0);
				emitbuf->tail++;
				goto exit_block;
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
	    if (GET_FLAG(scan_state->opts, SCAN_ONLY) || just_once) goto exit_block;
	}
