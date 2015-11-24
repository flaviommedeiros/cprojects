switch (sql_errno) {
	case CR_SERVER_GONE_ERROR:
	case CR_SERVER_LOST:
	case -1:
		return RLM_SQL_RECONNECT;

	case CR_OUT_OF_MEMORY:
	case CR_COMMANDS_OUT_OF_SYNC:
	case CR_UNKNOWN_ERROR:
	default:
		return RLM_SQL_ERROR;

	/*
	 *	Constraints errors that signify a duplicate, or that we might
	 *	want to try an alternative query.
	 *
	 *	Error constants not found in the 3.23/4.0/4.1 manual page
	 *	are checked for.
	 *	Other error constants should always be available.
	 */
	case ER_DUP_UNIQUE:			/* Can't write, because of unique constraint, to table '%s'. */
	case ER_DUP_KEY:			/* Can't write; duplicate key in table '%s' */

	case ER_DUP_ENTRY:			/* Duplicate entry '%s' for key %d. */
	case ER_NO_REFERENCED_ROW:		/* Cannot add or update a child row: a foreign key constraint fails */
	case ER_ROW_IS_REFERENCED:		/* Cannot delete or update a parent row: a foreign key constraint fails */
#ifdef ER_FOREIGN_DUPLICATE_KEY
	case ER_FOREIGN_DUPLICATE_KEY: 		/* Upholding foreign key constraints for table '%s', entry '%s', key %d would lead to a duplicate entry. */
#endif
#ifdef ER_DUP_ENTRY_WITH_KEY_NAME
	case ER_DUP_ENTRY_WITH_KEY_NAME:	/* Duplicate entry '%s' for key '%s' */
#endif
#ifdef ER_NO_REFERENCED_ROW_2
	case ER_NO_REFERENCED_ROW_2:
#endif
#ifdef ER_ROW_IS_REFERENCED_2
	case ER_ROW_IS_REFERENCED_2:
#endif
		return RLM_SQL_ALT_QUERY;

	/*
	 *	Constraints errors that signify an invalid query
	 *	that can never succeed.
	 */
	case ER_BAD_NULL_ERROR:			/* Column '%s' cannot be null */
	case ER_NON_UNIQ_ERROR:			/* Column '%s' in %s is ambiguous */
		return RLM_SQL_QUERY_INVALID;

	}
