switch (classId)
	{
		case AuthIdRelationId:
			if (!SearchSysCacheExists1(AUTHOID, ObjectIdGetDatum(objectId)))
				ereport(ERROR,
						(errcode(ERRCODE_UNDEFINED_OBJECT),
						 errmsg("role %u was concurrently dropped",
								objectId)));
			break;

			/*
			 * Currently, this routine need not support any other shared
			 * object types besides roles.  If we wanted to record explicit
			 * dependencies on databases or tablespaces, we'd need code along
			 * these lines:
			 */
#ifdef NOT_USED
		case TableSpaceRelationId:
			{
				/* For lack of a syscache on pg_tablespace, do this: */
				char	   *tablespace = get_tablespace_name(objectId);

				if (tablespace == NULL)
					ereport(ERROR,
							(errcode(ERRCODE_UNDEFINED_OBJECT),
							 errmsg("tablespace %u was concurrently dropped",
									objectId)));
				pfree(tablespace);
				break;
			}
#endif

		case DatabaseRelationId:
			{
				/* For lack of a syscache on pg_database, do this: */
				char	   *database = get_database_name(objectId);

				if (database == NULL)
					ereport(ERROR,
							(errcode(ERRCODE_UNDEFINED_OBJECT),
							 errmsg("database %u was concurrently dropped",
									objectId)));
				pfree(database);
				break;
			}


		default:
			elog(ERROR, "unrecognized shared classId: %u", classId);
	}
