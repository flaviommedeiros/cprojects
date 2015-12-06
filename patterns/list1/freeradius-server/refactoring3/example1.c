switch (check_item->op) {
		case T_OP_EQ:
		default:
			RWDEBUG("Invalid operator '%s' for item %s: reverting to '=='",
				fr_int2str(fr_tokens_table, check_item->op, "<INVALID>"), check_item->da->name);
			/* FALL-THROUGH */
		case T_OP_CMP_TRUE:
		case T_OP_CMP_FALSE:
		case T_OP_CMP_EQ:
			if (compare != 0) result = -1;
			break;

		case T_OP_NE:
			if (compare == 0) result = -1;
			break;

		case T_OP_LT:
			if (compare >= 0) result = -1;
			break;

		case T_OP_GT:
			if (compare <= 0) result = -1;
			break;

		case T_OP_LE:
			if (compare > 0) result = -1;
			break;

		case T_OP_GE:
			if (compare < 0) result = -1;
			break;

#ifdef HAVE_REGEX
		case T_OP_REG_EQ:
		case T_OP_REG_NE:
			if (compare != 0) result = -1;
			break;
#endif
		}
