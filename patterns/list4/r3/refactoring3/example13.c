switch (VAL_TYPE(val)) {

		case REB_END:
			// We should never reach the end before len above.
			// Exception is the stack itself.
			if (series != DS_Series) Crash(RP_UNEXPECTED_END);
			break;

		case REB_UNSET:
		case REB_TYPESET:
		case REB_HANDLE:
			break;

		case REB_DATATYPE:
			if (VAL_TYPE_SPEC(val)) {	// allow it to be zero
				CHECK_MARK(VAL_TYPE_SPEC(val), depth); // check typespec.r file
			}
			break;

		case REB_ERROR:
			// If it has an actual error object, then mark it. Otherwise,
			// it is a THROW, and GC of a THROW value is invalid because
			// it contains temporary values on the stack that could be
			// above the current DSP (where the THROW was done).
			if (VAL_ERR_NUM(val) > RE_THROW_MAX) {
				if (VAL_ERR_OBJECT(val)) CHECK_MARK(VAL_ERR_OBJECT(val), depth);
			}
			// else Crash(RP_THROW_IN_GC); // !!!! in question - is it true?
			break;

		case REB_TASK: // not yet implemented
			break;

		case REB_FRAME:
			// Mark special word list. Contains no pointers because
			// these are special word bindings (to typesets if used).
			if (VAL_FRM_WORDS(val)) MARK_SERIES(VAL_FRM_WORDS(val));
			if (VAL_FRM_SPEC(val)) {CHECK_MARK(VAL_FRM_SPEC(val), depth);}
			break;

		case REB_PORT:
			// Debug_Fmt("\n\nmark port: %x %d", val, VAL_TAIL(val));
			// Debug_Values(VAL_OBJ_VALUE(val,1), VAL_TAIL(val)-1, 100);
			goto mark_obj;

		case REB_MODULE:
			if (VAL_MOD_BODY(val)) CHECK_MARK(VAL_MOD_BODY(val), depth);
		case REB_OBJECT:
			// Object is just a block with special first value (context):
mark_obj:
			if (!IS_MARK_SERIES(VAL_OBJ_FRAME(val))) {
				Mark_Series(VAL_OBJ_FRAME(val), depth);
				if (SERIES_TAIL(VAL_OBJ_FRAME(val)) >= 1)
					; //Dump_Frame(VAL_OBJ_FRAME(val), 4);
			}
			break;

		case REB_FUNCTION:
		case REB_COMMAND:
		case REB_CLOSURE:
		case REB_REBCODE:
			CHECK_MARK(VAL_FUNC_BODY(val), depth);
		case REB_NATIVE:
		case REB_ACTION:
		case REB_OP:
			CHECK_MARK(VAL_FUNC_SPEC(val), depth);
			MARK_SERIES(VAL_FUNC_ARGS(val));
			// There is a problem for user define function operators !!!
			// Their bodies are not GC'd!
			break;

		case REB_WORD:	// (and also used for function STACK backtrace frame)
		case REB_SET_WORD:
		case REB_GET_WORD:
		case REB_LIT_WORD:
		case REB_REFINEMENT:
		case REB_ISSUE:
			// Special word used in word frame, stack, or errors:
			if (VAL_GET_OPT(val, OPTS_UNWORD)) break;
			// Mark its context, if it has one:
			if (VAL_WORD_INDEX(val) > 0 && NZ(ser = VAL_WORD_FRAME(val))) {
				//if (SERIES_TAIL(ser) > 100) Dump_Word_Value(val);
				CHECK_MARK(ser, depth);
			}
			// Possible bug above!!! We cannot mark relative words (negative
			// index) because the frame pointer does not point to a context,
			// it may point to a function body, native code, or action number.
			// But, what if a function is GC'd during it's own evaluation, what
			// keeps the function's code block from being GC'd?
			break;

		case REB_NONE:
		case REB_LOGIC:
		case REB_INTEGER:
		case REB_DECIMAL:
		case REB_PERCENT:
		case REB_MONEY:
		case REB_TIME:
		case REB_DATE:
		case REB_CHAR:
		case REB_PAIR:
		case REB_TUPLE:
			break;

		case REB_STRING:
		case REB_BINARY:
		case REB_FILE:
		case REB_EMAIL:
		case REB_URL:
		case REB_TAG:
		case REB_BITSET:
			ser = VAL_SERIES(val);
			if (SERIES_WIDE(ser) > sizeof(REBUNI))
				Crash(RP_BAD_WIDTH, sizeof(REBUNI), SERIES_WIDE(ser), VAL_TYPE(val));
			MARK_SERIES(ser);
			break;

		case REB_IMAGE:
			//MARK_SERIES(VAL_SERIES_SIDE(val)); //????
			MARK_SERIES(VAL_SERIES(val));
			break;

		case REB_VECTOR:
			MARK_SERIES(VAL_SERIES(val));
			break;

		case REB_BLOCK:
		case REB_PAREN:
		case REB_PATH:
		case REB_SET_PATH:
		case REB_GET_PATH:
		case REB_LIT_PATH:
			ser = VAL_SERIES(val);
			ASSERT(ser != 0, RP_NULL_SERIES);
			if (IS_BARE_SERIES(ser)) {
				MARK_SERIES(ser);
				break;
			}
#if (ALEVEL>0)
			if (!IS_END(BLK_SKIP(ser, SERIES_TAIL(ser))) && ser != DS_Series)
				Crash(RP_MISSING_END);
#endif
			if (SERIES_WIDE(ser) != sizeof(REBVAL) && SERIES_WIDE(ser) != 4 && SERIES_WIDE(ser) != 0)
				Crash(RP_BAD_WIDTH, 16, SERIES_WIDE(ser), VAL_TYPE(val));
			CHECK_MARK(ser, depth);
			break;

		case REB_MAP:
			ser = VAL_SERIES(val);
			CHECK_MARK(ser, depth);
			if (ser->series) {
				MARK_SERIES(ser->series);
			}
			break;

#ifdef ndef
		case REB_ROUTINE:
		  // Deal with the co-joined struct value...
			CHECK_MARK(VAL_STRUCT_SPEC(VAL_ROUTINE_SPEC(val)), depth);
			CHECK_MARK(VAL_STRUCT_VALS(VAL_ROUTINE_SPEC(val)), depth);
			MARK_SERIES(VAL_STRUCT_DATA(VAL_ROUTINE_SPEC(val)));
			MARK_SERIES(VAL_ROUTINE_SPEC_SER(val));
//!!!			if (Current_Closing_Library && VAL_ROUTINE_ID(val) == Current_Closing_Library)
				VAL_ROUTINE_ID(val) = 0; // Invalidate the routine
			break;
#endif

		case REB_LIBRARY:
			MARK_SERIES(VAL_LIBRARY_NAME(val));
//!!!			if (Current_Closing_Library && VAL_LIBRARY_ID(val) == Current_Closing_Library)
				VAL_LIBRARY_ID(val) = 0; // Invalidate the library
			break;

		case REB_STRUCT:
			CHECK_MARK(VAL_STRUCT_SPEC(val), depth);  // is a block
			CHECK_MARK(VAL_STRUCT_VALS(val), depth);  // "    "
			MARK_SERIES(VAL_STRUCT_DATA(val));
			break;

		case REB_GOB:
			Mark_Gob(VAL_GOB(val), depth);
			break;

		case REB_EVENT:
			Mark_Event(val, depth);
			break;

		default:
			Crash(RP_DATATYPE+1, VAL_TYPE(val));
		}
