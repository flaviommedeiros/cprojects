switch (status){
	/*
	 *  Successful completion of a command returning no data.
	 */
	case PGRES_COMMAND_OK:
		/*
		 *  Affected_rows function only returns the number of affected rows of a command
		 *  returning no data...
		 */
		conn->affected_rows = affected_rows(conn->result);
		DEBUG("rlm_sql_postgresql: query affected rows = %i", conn->affected_rows);
		return RLM_SQL_OK;
	/*
	 *  Successful completion of a command returning data (such as a SELECT or SHOW).
	 */
#ifdef HAVE_PGRES_SINGLE_TUPLE
	case PGRES_SINGLE_TUPLE:
#endif
	case PGRES_TUPLES_OK:
		conn->cur_row = 0;
		conn->affected_rows = PQntuples(conn->result);
		numfields = PQnfields(conn->result); /*Check row storing functions..*/
		DEBUG("rlm_sql_postgresql: query affected rows = %i , fields = %i", conn->affected_rows, numfields);
		return RLM_SQL_OK;

#ifdef HAVE_PGRES_COPY_BOTH
	case PGRES_COPY_BOTH:
#endif
	case PGRES_COPY_OUT:
	case PGRES_COPY_IN:
		DEBUG("rlm_sql_postgresql: Data transfer started");
		return RLM_SQL_OK;

	/*
	 *  Weird.. this shouldn't happen.
	 */
	case PGRES_EMPTY_QUERY:
		ERROR("rlm_sql_postgresql: Empty query");
		return RLM_SQL_QUERY_INVALID;

	/*
	 *  The server's response was not understood.
	 */
	case PGRES_BAD_RESPONSE:
		ERROR("rlm_sql_postgresql: Bad Response From Server");
		return RLM_SQL_RECONNECT;


	case PGRES_NONFATAL_ERROR:
	case PGRES_FATAL_ERROR:
		return sql_classify_error(conn->result);
	}
