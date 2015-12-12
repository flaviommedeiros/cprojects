switch (action) {

	case A_HEAD: VAL_INDEX(value) = 0; break;
	case A_TAIL: VAL_INDEX(value) = (REBCNT)tail; break;
	case A_HEADQ: DECIDE(index == 0);
	case A_TAILQ: DECIDE(index >= tail);
	case A_NEXT: if (index < tail) VAL_INDEX(value)++; break;
	case A_BACK: if (index > 0) VAL_INDEX(value)--; break;

#ifdef removed_feature
	case A_AND:
	case A_OR:
	case A_XOR:
		if (IS_IMAGE(value) && IS_IMAGE(arg)) {
			Xandor_Image(action, value, arg); // sets DS_RETURN
			return R_RET;
		}
		else Trap_Action(VAL_TYPE(value), action);
#endif

	case A_COMPLEMENT:
		series = Complement_Image(value);
		SET_IMAGE(value, series); // use series var not func
		break;

	case A_INDEXQ:
		if (D_REF(2)) {
			VAL_SET(D_RET, REB_PAIR);
			VAL_PAIR_X(D_RET) = (REBD32)(index % VAL_IMAGE_WIDE(value));
			VAL_PAIR_Y(D_RET) = (REBD32)(index / VAL_IMAGE_WIDE(value));
			return R_RET;
		} else {
			DS_RET_INT(index + 1);
			return R_RET;
		}
	case A_LENGTHQ:
		DS_RET_INT(tail > index ? tail - index : 0);
		return R_RET;

	case A_PICK:
		Pick_Path(value, arg, 0);
		return R_TOS;

	case A_POKE:
		Pick_Path(value, arg, D_ARG(3));
		return R_ARG3;

	case A_SKIP:
	case A_AT:
		// This logic is somewhat complicated by the fact that INTEGER args use
		// base-1 indexing, but PAIR args use base-0.
		if (IS_PAIR(arg)) {
			if (action == A_AT) action = A_SKIP;
			diff = (VAL_PAIR_Y_INT(arg) * VAL_IMAGE_WIDE(value) + VAL_PAIR_X_INT(arg)) +
				((action == A_SKIP) ? 0 : 1);
		} else
			diff = Get_Num_Arg(arg);

		index += diff;
		if (action == A_SKIP) {
			if (IS_LOGIC(arg)) index--;
		} else {
			if (diff > 0) index--; // For at, pick, poke.
		}

		if (index > tail) index = tail;
		else if (index < 0) index = 0;
		VAL_INDEX(value) = (REBCNT)index;
		break;

#ifdef obsolete
		if (action == A_SKIP || action == A_AT) {
		}

		if (diff == 0 || index < 0 || index >= tail) {
			if (action == A_POKE)
				Trap_Range(arg);
			goto is_none;
		}

		if (action == A_POKE) {
			REBINT *dp = QUAD_SKIP(series, index));
			REBINT n;

			arg = D_ARG(3);
			if (IS_TUPLE(arg) && (IS_IMAGE(value))) {
				Set_Pixel_Tuple(QUAD_SKIP(series, index), arg);
				//*dp = (long) (VAL_TUPLE_LEN(arg) < 4) ?
				//	((*dp & 0xff000000) | (VAL_TUPLE(arg)[0] << 16) | (VAL_TUPLE(arg)[1] << 8) | (VAL_TUPLE(arg)[2])) :
				//	((VAL_TUPLE(arg)[3] << 24) | (VAL_TUPLE(arg)[0] << 16) | (VAL_TUPLE(arg)[1] << 8) | (VAL_TUPLE(arg)[2]));
				DS_RET_VALUE(arg);
				return R_RET;
			}
			if (IS_INTEGER(arg) && VAL_INT64(arg) > 0 && VAL_INT64(arg) < 255)
				n = VAL_INT32(arg);
			else if (IS_CHAR(arg))
				n = VAL_CHAR(arg);
			else
				Trap_Arg(arg);

			*dp = (*dp & 0xffffff) | (n << 24);
			DS_RET_VALUE(arg);
			return R_RET; //was value;

		} else {
			Set_Tuple_Pixel(QUAD_SKIP(series, index), D_RET);
			return R_RET;
		}
		break;
#endif

	case A_CLEAR:	// clear series
		if (index < tail) {
			VAL_TAIL(value) = (REBCNT)index;
			Reset_Height(value);
		}
		break;

	case A_REMOVE:	// remove series /part count
		if (D_REF(2)) {
			val = D_ARG(3);
			if (IS_INTEGER(val)) {
				len = VAL_INT32(val);
			} else if (IS_IMAGE(val)) {
				if (!VAL_IMAGE_WIDE(val)) Trap_Arg(val);
				len = VAL_INDEX(val) - VAL_INDEX(value); // may not be same, is ok
			} else
				Trap_Type(val);
		} else len = 1;
		index = (REBINT)VAL_INDEX(value);
		if (index < tail && len != 0) {
			Remove_Series(series, VAL_INDEX(value), len);
		}
		Reset_Height(value);
		break;

	case A_APPEND:
	case A_INSERT:	// insert ser val /part len /only /dup count
	case A_CHANGE:	// change ser val /part len /only /dup count
		value = Modify_Image(ds, action); // sets DS_RETURN
		break;

	case A_FIND:	// find   ser val /part len /only /case /any /with wild /match /tail
		Find_Image(ds); // sets DS_RETURN
		break;

	case A_TO:
		if (IS_IMAGE(arg)) goto makeCopy;
		else if (IS_GOB(arg)) {
			//value = Make_Image(ROUND_TO_INT(GOB_W(VAL_GOB(arg))), ROUND_TO_INT(GOB_H(VAL_GOB(arg))));
			//*D_RET = *value;
			series = OS_GOB_TO_IMAGE(VAL_GOB(arg));
			if (!series) Trap_Make(REB_IMAGE, arg);
			SET_IMAGE(value, series);
			break;
		}
		else if (IS_BINARY(arg)) {
			diff = VAL_LEN(arg) / 4;
			if (diff == 0) Trap_Make(REB_IMAGE, arg);
			if (diff < 100) w = diff;
			else if (diff < 10000) w = 100;
			else w = 500;
			h = diff / w;
			if (w * h < diff) h++; // partial line
			series = Make_Image(w, h, TRUE);
			SET_IMAGE(value, series);
			Bin_To_RGBA(IMG_DATA(series), w*h, VAL_BIN_DATA(arg), VAL_LEN(arg)/4, 0);
			break;
		}
		Trap_Type(arg);
		break;

	case A_MAKE:
		// make image! img
		if (IS_IMAGE(arg)) goto makeCopy;

		// make image! [] (or none)
		if (IS_IMAGE(value) && (IS_NONE(arg) || (IS_BLOCK(arg) && (VAL_BLK_LEN(arg) == 0)))) {
			arg = value;
			goto makeCopy;
		}

		// make image! size
		if (IS_PAIR(arg)) {
			w = VAL_PAIR_X_INT(arg);
			h = VAL_PAIR_Y_INT(arg);
			w = MAX(w, 0);
			h = MAX(h, 0);
			series = Make_Image(w, h, TRUE);
			SET_IMAGE(value, series);
			break;
		}
//		else if (IS_NONE(arg)) {
//			*value = *Make_Image(0, 0);
//			CLEAR_IMAGE(VAL_IMAGE_HEAD(value), 0, 0);
//			break;
//		}
		// make image! [size rgb alpha index]
		else if (IS_BLOCK(arg)) {
			if (Create_Image(VAL_BLK_DATA(arg), value, 0)) break;
		}
		Trap_Type(arg);
		break;

	case A_COPY:  // copy series /part len
		if (!D_REF(2)) {
			arg = value;
			goto makeCopy;
		}
		arg = D_ARG(3); // can be image, integer, pair.
		if (IS_IMAGE(arg)) {
			if (VAL_SERIES(arg) != VAL_SERIES(value)) Trap_Arg(arg);
			len = VAL_INDEX(arg) - VAL_INDEX(value);
			arg = value;
			goto makeCopy2;
		}
		if (IS_INTEGER(arg)) {
			len = VAL_INT32(arg);
			arg = value;
			goto makeCopy2;
		}
		if (IS_PAIR(arg)) {
			w = VAL_PAIR_X_INT(arg);
			h = VAL_PAIR_Y_INT(arg);
			w = MAX(w, 0);
			h = MAX(h, 0);
			diff = MIN(VAL_TAIL(value), VAL_INDEX(value)); // index offset
			diff = MAX(0, diff);
			index = VAL_IMAGE_WIDE(value); // width
			if (index) {
				len = diff / index; // compute y offset
				diff %= index; // compute x offset
			} else len = diff = 0; // avoid div zero
			w = MIN(w, index - diff); // img-width - x-pos
			h = MIN(h, (int)(VAL_IMAGE_HIGH(value) - len)); // img-high - y-pos
			series = Make_Image(w, h, TRUE);
			SET_IMAGE(D_RET, series);
			Copy_Rect_Data(D_RET, 0, 0, w, h, value, diff, len);
//			VAL_IMAGE_TRANSP(D_RET) = VAL_IMAGE_TRANSP(value);
			return R_RET;
		}
		Trap_Type(arg);

makeCopy:
		// Src image is arg.
		len = VAL_IMAGE_LEN(arg);
makeCopy2:
		len = MAX(len, 0); // no negatives
		len = MIN(len, (REBINT)VAL_IMAGE_LEN(arg));
		w = VAL_IMAGE_WIDE(arg);
		w = MAX(w, 1);
		if (len <= w) h = 1, w = len;
		else h = len / w;
		if (w == 0) h = 0;
		series = Make_Image(w, h, TRUE);
		SET_IMAGE(D_RET, series);
		memcpy(VAL_IMAGE_HEAD(D_RET), VAL_IMAGE_DATA(arg), w * h * 4);
//		VAL_IMAGE_TRANSP(D_RET) = VAL_IMAGE_TRANSP(arg);
		return R_RET;
		break;

	default:
		Trap_Action(VAL_TYPE(value), action);
	}
