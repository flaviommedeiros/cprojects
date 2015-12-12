switch (type)
			{
					long		res;
					unsigned long ures;
					double		dres;
					char	   *scan_length;
					numeric    *nres;
					date		ddres;
					timestamp	tres;
					interval   *ires;
					char *endptr, endchar;

				case ECPGt_short:
				case ECPGt_int:
				case ECPGt_long:
					res = strtol(pval, &scan_length, 10);
					if (garbage_left(isarray, scan_length, compat))
					{
						ecpg_raise(lineno, ECPG_INT_FORMAT,
								   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
						return (false);
					}
					pval = scan_length;

					switch (type)
					{
						case ECPGt_short:
							*((short *) (var + offset * act_tuple)) = (short) res;
							break;
						case ECPGt_int:
							*((int *) (var + offset * act_tuple)) = (int) res;
							break;
						case ECPGt_long:
							*((long *) (var + offset * act_tuple)) = (long) res;
							break;
						default:
							/* Cannot happen */
							break;
					}
					break;

				case ECPGt_unsigned_short:
				case ECPGt_unsigned_int:
				case ECPGt_unsigned_long:
					ures = strtoul(pval, &scan_length, 10);
					if (garbage_left(isarray, scan_length, compat))
					{
						ecpg_raise(lineno, ECPG_UINT_FORMAT,
								   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
						return (false);
					}
					pval = scan_length;

					switch (type)
					{
						case ECPGt_unsigned_short:
							*((unsigned short *) (var + offset * act_tuple)) = (unsigned short) ures;
							break;
						case ECPGt_unsigned_int:
							*((unsigned int *) (var + offset * act_tuple)) = (unsigned int) ures;
							break;
						case ECPGt_unsigned_long:
							*((unsigned long *) (var + offset * act_tuple)) = (unsigned long) ures;
							break;
						default:
							/* Cannot happen */
							break;
					}
					break;

#ifdef HAVE_LONG_LONG_INT
#ifdef HAVE_STRTOLL
				case ECPGt_long_long:
					*((long long int *) (var + offset * act_tuple)) = strtoll(pval, &scan_length, 10);
					if (garbage_left(isarray, scan_length, compat))
					{
						ecpg_raise(lineno, ECPG_INT_FORMAT, ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
						return (false);
					}
					pval = scan_length;

					break;
#endif   /* HAVE_STRTOLL */
#ifdef HAVE_STRTOULL
				case ECPGt_unsigned_long_long:
					*((unsigned long long int *) (var + offset * act_tuple)) = strtoull(pval, &scan_length, 10);
					if ((isarray && *scan_length != ',' && *scan_length != '}')
						|| (!isarray && !(INFORMIX_MODE(compat) && *scan_length == '.') && *scan_length != '\0' && *scan_length != ' '))		/* Garbage left */
					{
						ecpg_raise(lineno, ECPG_UINT_FORMAT, ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
						return (false);
					}
					pval = scan_length;

					break;
#endif   /* HAVE_STRTOULL */
#endif   /* HAVE_LONG_LONG_INT */

				case ECPGt_float:
				case ECPGt_double:
					if (isarray && *pval == '"')
						pval++;

					if (!check_special_value(pval, &dres, &scan_length))
						dres = strtod(pval, &scan_length);

					if (isarray && *scan_length == '"')
						scan_length++;

					if (garbage_left(isarray, scan_length, compat))
					{
						ecpg_raise(lineno, ECPG_FLOAT_FORMAT,
								   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
						return (false);
					}
					pval = scan_length;

					switch (type)
					{
						case ECPGt_float:
							*((float *) (var + offset * act_tuple)) = dres;
							break;
						case ECPGt_double:
							*((double *) (var + offset * act_tuple)) = dres;
							break;
						default:
							/* Cannot happen */
							break;
					}
					break;

				case ECPGt_bool:
					if (pval[0] == 'f' && pval[1] == '\0')
					{
						if (offset == sizeof(char))
							*((char *) (var + offset * act_tuple)) = false;
						else if (offset == sizeof(int))
							*((int *) (var + offset * act_tuple)) = false;
						else
							ecpg_raise(lineno, ECPG_CONVERT_BOOL,
									   ECPG_SQLSTATE_DATATYPE_MISMATCH,
									   NULL);
						pval++;
						break;
					}
					else if (pval[0] == 't' && pval[1] == '\0')
					{
						if (offset == sizeof(char))
							*((char *) (var + offset * act_tuple)) = true;
						else if (offset == sizeof(int))
							*((int *) (var + offset * act_tuple)) = true;
						else
							ecpg_raise(lineno, ECPG_CONVERT_BOOL,
									   ECPG_SQLSTATE_DATATYPE_MISMATCH,
									   NULL);
						pval++;
						break;
					}
					else if (pval[0] == '\0' && PQgetisnull(results, act_tuple, act_field))
					{
						/* NULL is valid */
						break;
					}

					ecpg_raise(lineno, ECPG_CONVERT_BOOL,
							   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
					return (false);
					break;

				case ECPGt_char:
				case ECPGt_unsigned_char:
				case ECPGt_string:
					{
						char	   *str = (char *) (var + offset * act_tuple);

						/*
						 * If varcharsize is unknown and the offset is that of
						 * char *, then this variable represents the array of
						 * character pointers. So, use extra indirection.
						 */
						if (varcharsize == 0 && offset == sizeof(char *))
							str = *(char **) str;

						if (varcharsize == 0 || varcharsize > size)
						{
							strncpy(str, pval, size + 1);
							/* do the rtrim() */
							if (type == ECPGt_string)
							{
								char	   *last = str + size;

								while (last > str && (*last == ' ' || *last == '\0'))
								{
									*last = '\0';
									last--;
								}
							}
						}
						else
						{
							strncpy(str, pval, varcharsize);

							if (varcharsize < size)
							{
								/* truncation */
								switch (ind_type)
								{
									case ECPGt_short:
									case ECPGt_unsigned_short:
										*((short *) (ind + ind_offset * act_tuple)) = size;
										break;
									case ECPGt_int:
									case ECPGt_unsigned_int:
										*((int *) (ind + ind_offset * act_tuple)) = size;
										break;
									case ECPGt_long:
									case ECPGt_unsigned_long:
										*((long *) (ind + ind_offset * act_tuple)) = size;
										break;
#ifdef HAVE_LONG_LONG_INT
									case ECPGt_long_long:
									case ECPGt_unsigned_long_long:
										*((long long int *) (ind + ind_offset * act_tuple)) = size;
										break;
#endif   /* HAVE_LONG_LONG_INT */
									default:
										break;
								}
								sqlca->sqlwarn[0] = sqlca->sqlwarn[1] = 'W';
							}
						}
						pval += size;
					}
					break;

				case ECPGt_varchar:
					{
						struct ECPGgeneric_varchar *variable =
						(struct ECPGgeneric_varchar *) (var + offset * act_tuple);

						variable->len = size;
						if (varcharsize == 0)
							strncpy(variable->arr, pval, variable->len);
						else
						{
							strncpy(variable->arr, pval, varcharsize);

							if (variable->len > varcharsize)
							{
								/* truncation */
								switch (ind_type)
								{
									case ECPGt_short:
									case ECPGt_unsigned_short:
										*((short *) (ind + ind_offset * act_tuple)) = variable->len;
										break;
									case ECPGt_int:
									case ECPGt_unsigned_int:
										*((int *) (ind + ind_offset * act_tuple)) = variable->len;
										break;
									case ECPGt_long:
									case ECPGt_unsigned_long:
										*((long *) (ind + ind_offset * act_tuple)) = variable->len;
										break;
#ifdef HAVE_LONG_LONG_INT
									case ECPGt_long_long:
									case ECPGt_unsigned_long_long:
										*((long long int *) (ind + ind_offset * act_tuple)) = variable->len;
										break;
#endif   /* HAVE_LONG_LONG_INT */
									default:
										break;
								}
								sqlca->sqlwarn[0] = sqlca->sqlwarn[1] = 'W';

								variable->len = varcharsize;
							}
						}
						pval += size;
					}
					break;

				case ECPGt_decimal:
				case ECPGt_numeric:
					for (endptr = pval; *endptr && *endptr != ',' && *endptr != '}'; endptr++);
					endchar = *endptr;
					*endptr = '\0';
					nres = PGTYPESnumeric_from_asc(pval, &scan_length);
					*endptr = endchar;

					/* did we get an error? */
					if (nres == NULL)
					{
						ecpg_log("ecpg_get_data on line %d: RESULT %s; errno %d\n",
								 lineno, pval ? pval : "", errno);

						if (INFORMIX_MODE(compat))
						{
							/*
							 * Informix wants its own NULL value here instead
							 * of an error
							 */
							nres = PGTYPESnumeric_new();
							if (nres)
								ECPGset_noind_null(ECPGt_numeric, nres);
							else
							{
								ecpg_raise(lineno, ECPG_OUT_OF_MEMORY,
									 ECPG_SQLSTATE_ECPG_OUT_OF_MEMORY, NULL);
								return (false);
							}
						}
						else
						{
							ecpg_raise(lineno, ECPG_NUMERIC_FORMAT,
									   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
							return (false);
						}
					}
					else
					{
						if (!isarray && garbage_left(isarray, scan_length, compat))
						{
							free(nres);
							ecpg_raise(lineno, ECPG_NUMERIC_FORMAT,
									   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
							return (false);
						}
					}
					pval = scan_length;

					if (type == ECPGt_numeric)
						PGTYPESnumeric_copy(nres, (numeric *) (var + offset * act_tuple));
					else
						PGTYPESnumeric_to_decimal(nres, (decimal *) (var + offset * act_tuple));

					PGTYPESnumeric_free(nres);
					break;

				case ECPGt_interval:
					if (*pval == '"')
						pval++;

					for (endptr = pval; *endptr && *endptr != ',' && *endptr != '"' && *endptr != '}'; endptr++);
					endchar = *endptr;
					*endptr = '\0';
					ires = PGTYPESinterval_from_asc(pval, &scan_length);
					*endptr = endchar;

					/* did we get an error? */
					if (ires == NULL)
					{
						ecpg_log("ecpg_get_data on line %d: RESULT %s; errno %d\n",
								 lineno, pval ? pval : "", errno);

						if (INFORMIX_MODE(compat))
						{
							/*
							 * Informix wants its own NULL value here instead
							 * of an error
							 */
							ires = (interval *) ecpg_alloc(sizeof(interval), lineno);
							if (!ires)
								return (false);

							ECPGset_noind_null(ECPGt_interval, ires);
						}
						else
						{
							ecpg_raise(lineno, ECPG_INTERVAL_FORMAT,
									   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
							return (false);
						}
					}
					else
					{
						if (*scan_length == '"')
							scan_length++;

						if (!isarray && garbage_left(isarray, scan_length, compat))
						{
							free(ires);
							ecpg_raise(lineno, ECPG_INTERVAL_FORMAT,
									   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
							return (false);
						}
					}
					pval = scan_length;

					PGTYPESinterval_copy(ires, (interval *) (var + offset * act_tuple));
					free(ires);
					break;

				case ECPGt_date:
					if (*pval == '"')
						pval++;

					for (endptr = pval; *endptr && *endptr != ',' && *endptr != '"' && *endptr != '}'; endptr++);
					endchar = *endptr;
					*endptr = '\0';
					ddres = PGTYPESdate_from_asc(pval, &scan_length);
					*endptr = endchar;

					/* did we get an error? */
					if (errno != 0)
					{
						ecpg_log("ecpg_get_data on line %d: RESULT %s; errno %d\n",
								 lineno, pval ? pval : "", errno);

						if (INFORMIX_MODE(compat))
						{
							/*
							 * Informix wants its own NULL value here instead
							 * of an error
							 */
							ECPGset_noind_null(ECPGt_date, &ddres);
						}
						else
						{
							ecpg_raise(lineno, ECPG_DATE_FORMAT,
									   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
							return (false);
						}
					}
					else
					{
						if (*scan_length == '"')
							scan_length++;

						if (!isarray && garbage_left(isarray, scan_length, compat))
						{
							ecpg_raise(lineno, ECPG_DATE_FORMAT,
									   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
							return (false);
						}
					}

					*((date *) (var + offset * act_tuple)) = ddres;
					pval = scan_length;
					break;

				case ECPGt_timestamp:
					if (*pval == '"')
						pval++;

					for (endptr = pval; *endptr && *endptr != ',' && *endptr != '"' && *endptr != '}'; endptr++);
					endchar = *endptr;
					*endptr = '\0';
					tres = PGTYPEStimestamp_from_asc(pval, &scan_length);
					*endptr = endchar;

					/* did we get an error? */
					if (errno != 0)
					{
						ecpg_log("ecpg_get_data on line %d: RESULT %s; errno %d\n",
								 lineno, pval ? pval : "", errno);

						if (INFORMIX_MODE(compat))
						{
							/*
							 * Informix wants its own NULL value here instead
							 * of an error
							 */
							ECPGset_noind_null(ECPGt_timestamp, &tres);
						}
						else
						{
							ecpg_raise(lineno, ECPG_TIMESTAMP_FORMAT,
									   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
							return (false);
						}
					}
					else
					{
						if (*scan_length == '"')
							scan_length++;

						if (!isarray && garbage_left(isarray, scan_length, compat))
						{
							ecpg_raise(lineno, ECPG_TIMESTAMP_FORMAT,
									   ECPG_SQLSTATE_DATATYPE_MISMATCH, pval);
							return (false);
						}
					}

					*((timestamp *) (var + offset * act_tuple)) = tres;
					pval = scan_length;
					break;

				default:
					ecpg_raise(lineno, ECPG_UNSUPPORTED,
							   ECPG_SQLSTATE_ECPG_INTERNAL_ERROR,
							   ecpg_type_name(type));
					return (false);
					break;
			}
