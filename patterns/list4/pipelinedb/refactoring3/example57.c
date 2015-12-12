switch (var->type)
		{
				int			element;

			case ECPGt_short:
				if (!(mallocedval = ecpg_alloc(asize * 20, lineno)))
					return false;

				if (asize > 1)
				{
					strcpy(mallocedval, "{");

					for (element = 0; element < asize; element++)
						sprintf(mallocedval + strlen(mallocedval), "%hd,", ((short *) var->value)[element]);

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
					sprintf(mallocedval, "%hd", *((short *) var->value));

				*tobeinserted_p = mallocedval;
				break;

			case ECPGt_int:
				if (!(mallocedval = ecpg_alloc(asize * 20, lineno)))
					return false;

				if (asize > 1)
				{
					strcpy(mallocedval, "{");

					for (element = 0; element < asize; element++)
						sprintf(mallocedval + strlen(mallocedval), "%d,", ((int *) var->value)[element]);

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
					sprintf(mallocedval, "%d", *((int *) var->value));

				*tobeinserted_p = mallocedval;
				break;

			case ECPGt_unsigned_short:
				if (!(mallocedval = ecpg_alloc(asize * 20, lineno)))
					return false;

				if (asize > 1)
				{
					strcpy(mallocedval, "{");

					for (element = 0; element < asize; element++)
						sprintf(mallocedval + strlen(mallocedval), "%hu,", ((unsigned short *) var->value)[element]);

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
					sprintf(mallocedval, "%hu", *((unsigned short *) var->value));

				*tobeinserted_p = mallocedval;
				break;

			case ECPGt_unsigned_int:
				if (!(mallocedval = ecpg_alloc(asize * 20, lineno)))
					return false;

				if (asize > 1)
				{
					strcpy(mallocedval, "{");

					for (element = 0; element < asize; element++)
						sprintf(mallocedval + strlen(mallocedval), "%u,", ((unsigned int *) var->value)[element]);

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
					sprintf(mallocedval, "%u", *((unsigned int *) var->value));

				*tobeinserted_p = mallocedval;
				break;

			case ECPGt_long:
				if (!(mallocedval = ecpg_alloc(asize * 20, lineno)))
					return false;

				if (asize > 1)
				{
					strcpy(mallocedval, "{");

					for (element = 0; element < asize; element++)
						sprintf(mallocedval + strlen(mallocedval), "%ld,", ((long *) var->value)[element]);

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
					sprintf(mallocedval, "%ld", *((long *) var->value));

				*tobeinserted_p = mallocedval;
				break;

			case ECPGt_unsigned_long:
				if (!(mallocedval = ecpg_alloc(asize * 20, lineno)))
					return false;

				if (asize > 1)
				{
					strcpy(mallocedval, "{");

					for (element = 0; element < asize; element++)
						sprintf(mallocedval + strlen(mallocedval), "%lu,", ((unsigned long *) var->value)[element]);

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
					sprintf(mallocedval, "%lu", *((unsigned long *) var->value));

				*tobeinserted_p = mallocedval;
				break;
#ifdef HAVE_LONG_LONG_INT
			case ECPGt_long_long:
				if (!(mallocedval = ecpg_alloc(asize * 30, lineno)))
					return false;

				if (asize > 1)
				{
					strcpy(mallocedval, "{");

					for (element = 0; element < asize; element++)
						sprintf(mallocedval + strlen(mallocedval), "%lld,", ((long long int *) var->value)[element]);

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
					sprintf(mallocedval, "%lld", *((long long int *) var->value));

				*tobeinserted_p = mallocedval;
				break;

			case ECPGt_unsigned_long_long:
				if (!(mallocedval = ecpg_alloc(asize * 30, lineno)))
					return false;

				if (asize > 1)
				{
					strcpy(mallocedval, "{");

					for (element = 0; element < asize; element++)
						sprintf(mallocedval + strlen(mallocedval), "%llu,", ((unsigned long long int *) var->value)[element]);

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
					sprintf(mallocedval, "%llu", *((unsigned long long int *) var->value));

				*tobeinserted_p = mallocedval;
				break;
#endif   /* HAVE_LONG_LONG_INT */
			case ECPGt_float:
				if (!(mallocedval = ecpg_alloc(asize * 25, lineno)))
					return false;

				if (asize > 1)
				{
					strcpy(mallocedval, "{");

					for (element = 0; element < asize; element++)
						sprintf_float_value(mallocedval + strlen(mallocedval), ((float *) var->value)[element], ",");

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
					sprintf_float_value(mallocedval, *((float *) var->value), "");

				*tobeinserted_p = mallocedval;
				break;

			case ECPGt_double:
				if (!(mallocedval = ecpg_alloc(asize * 25, lineno)))
					return false;

				if (asize > 1)
				{
					strcpy(mallocedval, "{");

					for (element = 0; element < asize; element++)
						sprintf_double_value(mallocedval + strlen(mallocedval), ((double *) var->value)[element], ",");

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
					sprintf_double_value(mallocedval, *((double *) var->value), "");

				*tobeinserted_p = mallocedval;
				break;

			case ECPGt_bool:
				if (!(mallocedval = ecpg_alloc(var->arrsize + sizeof("{}"), lineno)))
					return false;

				if (var->arrsize > 1)
				{
					strcpy(mallocedval, "{");

					if (var->offset == sizeof(char))
						for (element = 0; element < asize; element++)
							sprintf(mallocedval + strlen(mallocedval), "%c,", (((char *) var->value)[element]) ? 't' : 'f');

					/*
					 * this is necessary since sizeof(C++'s bool)==sizeof(int)
					 */
					else if (var->offset == sizeof(int))
						for (element = 0; element < asize; element++)
							sprintf(mallocedval + strlen(mallocedval), "%c,", (((int *) var->value)[element]) ? 't' : 'f');
					else
						ecpg_raise(lineno, ECPG_CONVERT_BOOL, ECPG_SQLSTATE_DATATYPE_MISMATCH, NULL);

					strcpy(mallocedval + strlen(mallocedval) - 1, "}");
				}
				else
				{
					if (var->offset == sizeof(char))
						sprintf(mallocedval, "%c", (*((char *) var->value)) ? 't' : 'f');
					else if (var->offset == sizeof(int))
						sprintf(mallocedval, "%c", (*((int *) var->value)) ? 't' : 'f');
					else
						ecpg_raise(lineno, ECPG_CONVERT_BOOL, ECPG_SQLSTATE_DATATYPE_MISMATCH, NULL);
				}

				*tobeinserted_p = mallocedval;
				break;

			case ECPGt_char:
			case ECPGt_unsigned_char:
			case ECPGt_string:
				{
					/* set slen to string length if type is char * */
					int			slen = (var->varcharsize == 0) ? strlen((char *) var->value) : (unsigned int) var->varcharsize;

					if (!(newcopy = ecpg_alloc(slen + 1, lineno)))
						return false;

					strncpy(newcopy, (char *) var->value, slen);
					newcopy[slen] = '\0';

					mallocedval = quote_postgres(newcopy, quote, lineno);
					if (!mallocedval)
						return false;

					*tobeinserted_p = mallocedval;
				}
				break;
			case ECPGt_const:
			case ECPGt_char_variable:
				{
					int			slen = strlen((char *) var->value);

					if (!(mallocedval = ecpg_alloc(slen + 1, lineno)))
						return false;

					strncpy(mallocedval, (char *) var->value, slen);
					mallocedval[slen] = '\0';

					*tobeinserted_p = mallocedval;
				}
				break;
			case ECPGt_varchar:
				{
					struct ECPGgeneric_varchar *variable =
					(struct ECPGgeneric_varchar *) (var->value);

					if (!(newcopy = (char *) ecpg_alloc(variable->len + 1, lineno)))
						return false;

					strncpy(newcopy, variable->arr, variable->len);
					newcopy[variable->len] = '\0';

					mallocedval = quote_postgres(newcopy, quote, lineno);
					if (!mallocedval)
						return false;

					*tobeinserted_p = mallocedval;
				}
				break;

			case ECPGt_decimal:
			case ECPGt_numeric:
				{
					char	   *str = NULL;
					int			slen;
					numeric    *nval;

					if (var->arrsize > 1)
						mallocedval = ecpg_strdup("{", lineno);
					else
						mallocedval = ecpg_strdup("", lineno);

					if (!mallocedval)
							return false;

					for (element = 0; element < asize; element++)
					{
						int			result;

						nval = PGTYPESnumeric_new();
						if (!nval)
						{
							ecpg_free(mallocedval);
							return false;
						}

						if (var->type == ECPGt_numeric)
							result = PGTYPESnumeric_copy(&(((numeric *) (var->value))[element]), nval);
						else
							result = PGTYPESnumeric_from_decimal(&(((decimal *) (var->value))[element]), nval);

						if (result != 0)
						{
							PGTYPESnumeric_free(nval);
							ecpg_free(mallocedval);
							return false;
						}

						str = PGTYPESnumeric_to_asc(nval, nval->dscale);
						slen = strlen(str);
						PGTYPESnumeric_free(nval);

						if (!(newcopy = ecpg_realloc(mallocedval, strlen(mallocedval) + slen + 2, lineno)))
						{
							ecpg_free(mallocedval);
							ecpg_free(str);
							return false;
						}
						mallocedval = newcopy;

						/* also copy trailing '\0' */
						memcpy(mallocedval + strlen(mallocedval), str, slen + 1);
						if (var->arrsize > 1)
							strcpy(mallocedval + strlen(mallocedval), ",");

						ecpg_free(str);
					}

					if (var->arrsize > 1)
						strcpy(mallocedval + strlen(mallocedval) - 1, "}");

					*tobeinserted_p = mallocedval;
				}
				break;

			case ECPGt_interval:
				{
					char	   *str = NULL;
					int			slen;

					if (var->arrsize > 1)
						mallocedval = ecpg_strdup("{", lineno);
					else
						mallocedval = ecpg_strdup("", lineno);

					if (!mallocedval)
							return false;

					for (element = 0; element < asize; element++)
					{
						str = quote_postgres(PGTYPESinterval_to_asc(&(((interval *) (var->value))[element])), quote, lineno);
						if (!str)
						{
							ecpg_free(mallocedval);
							return false;
						}

						slen = strlen(str);

						if (!(newcopy = ecpg_realloc(mallocedval, strlen(mallocedval) + slen + 2, lineno)))
						{
							ecpg_free(mallocedval);
							ecpg_free(str);
							return false;
						}
						mallocedval = newcopy;

						/* also copy trailing '\0' */
						memcpy(mallocedval + strlen(mallocedval), str, slen + 1);
						if (var->arrsize > 1)
							strcpy(mallocedval + strlen(mallocedval), ",");

						ecpg_free(str);
					}

					if (var->arrsize > 1)
						strcpy(mallocedval + strlen(mallocedval) - 1, "}");

					*tobeinserted_p = mallocedval;
				}
				break;

			case ECPGt_date:
				{
					char	   *str = NULL;
					int			slen;

					if (var->arrsize > 1)
						mallocedval = ecpg_strdup("{", lineno);
					else
						mallocedval = ecpg_strdup("", lineno);

					if (!mallocedval)
							return false;

					for (element = 0; element < asize; element++)
					{
						str = quote_postgres(PGTYPESdate_to_asc(((date *) (var->value))[element]), quote, lineno);
						if (!str)
						{
							ecpg_free(mallocedval);
							return false;
						}

						slen = strlen(str);

						if (!(newcopy = ecpg_realloc(mallocedval, strlen(mallocedval) + slen + 2, lineno)))
						{
							ecpg_free(mallocedval);
							ecpg_free(str);
							return false;
						}
						mallocedval = newcopy;

						/* also copy trailing '\0' */
						memcpy(mallocedval + strlen(mallocedval), str, slen + 1);
						if (var->arrsize > 1)
							strcpy(mallocedval + strlen(mallocedval), ",");

						ecpg_free(str);
					}

					if (var->arrsize > 1)
						strcpy(mallocedval + strlen(mallocedval) - 1, "}");

					*tobeinserted_p = mallocedval;
				}
				break;

			case ECPGt_timestamp:
				{
					char	   *str = NULL;
					int			slen;

					if (var->arrsize > 1)
						mallocedval = ecpg_strdup("{", lineno);
					else
						mallocedval = ecpg_strdup("", lineno);

					if (!mallocedval)
							return false;

					for (element = 0; element < asize; element++)
					{
						str = quote_postgres(PGTYPEStimestamp_to_asc(((timestamp *) (var->value))[element]), quote, lineno);
						if (!str)
						{
							ecpg_free(mallocedval);
							return false;
						}

						slen = strlen(str);

						if (!(newcopy = ecpg_realloc(mallocedval, strlen(mallocedval) + slen + 2, lineno)))
						{
							ecpg_free(mallocedval);
							ecpg_free(str);
							return false;
						}
						mallocedval = newcopy;

						/* also copy trailing '\0' */
						memcpy(mallocedval + strlen(mallocedval), str, slen + 1);
						if (var->arrsize > 1)
							strcpy(mallocedval + strlen(mallocedval), ",");

						ecpg_free(str);
					}

					if (var->arrsize > 1)
						strcpy(mallocedval + strlen(mallocedval) - 1, "}");

					*tobeinserted_p = mallocedval;
				}
				break;

			case ECPGt_descriptor:
			case ECPGt_sqlda:
				break;

			default:
				/* Not implemented yet */
				ecpg_raise(lineno, ECPG_UNSUPPORTED, ECPG_SQLSTATE_ECPG_INTERNAL_ERROR, ecpg_type_name(var->type));
				return false;
				break;
		}
