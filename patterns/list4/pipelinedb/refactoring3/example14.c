switch (type)
		{
			case BOOLOID:
				if (DatumGetBool(value))
					return "true";
				else
					return "false";

			case DATEOID:
				{
					DateADT		date;
					struct pg_tm tm;
					char		buf[MAXDATELEN + 1];

					date = DatumGetDateADT(value);
					/* XSD doesn't support infinite values */
					if (DATE_NOT_FINITE(date))
						ereport(ERROR,
								(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
								 errmsg("date out of range"),
								 errdetail("XML does not support infinite date values.")));
					j2date(date + POSTGRES_EPOCH_JDATE,
						   &(tm.tm_year), &(tm.tm_mon), &(tm.tm_mday));
					EncodeDateOnly(&tm, USE_XSD_DATES, buf);

					return pstrdup(buf);
				}

			case TIMESTAMPOID:
				{
					Timestamp	timestamp;
					struct pg_tm tm;
					fsec_t		fsec;
					char		buf[MAXDATELEN + 1];

					timestamp = DatumGetTimestamp(value);

					/* XSD doesn't support infinite values */
					if (TIMESTAMP_NOT_FINITE(timestamp))
						ereport(ERROR,
								(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
								 errmsg("timestamp out of range"),
								 errdetail("XML does not support infinite timestamp values.")));
					else if (timestamp2tm(timestamp, NULL, &tm, &fsec, NULL, NULL) == 0)
						EncodeDateTime(&tm, fsec, false, 0, NULL, USE_XSD_DATES, buf);
					else
						ereport(ERROR,
								(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
								 errmsg("timestamp out of range")));

					return pstrdup(buf);
				}

			case TIMESTAMPTZOID:
				{
					TimestampTz timestamp;
					struct pg_tm tm;
					int			tz;
					fsec_t		fsec;
					const char *tzn = NULL;
					char		buf[MAXDATELEN + 1];

					timestamp = DatumGetTimestamp(value);

					/* XSD doesn't support infinite values */
					if (TIMESTAMP_NOT_FINITE(timestamp))
						ereport(ERROR,
								(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
								 errmsg("timestamp out of range"),
								 errdetail("XML does not support infinite timestamp values.")));
					else if (timestamp2tm(timestamp, &tz, &tm, &fsec, &tzn, NULL) == 0)
						EncodeDateTime(&tm, fsec, true, tz, tzn, USE_XSD_DATES, buf);
					else
						ereport(ERROR,
								(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
								 errmsg("timestamp out of range")));

					return pstrdup(buf);
				}

#ifdef USE_LIBXML
			case BYTEAOID:
				{
					bytea	   *bstr = DatumGetByteaPP(value);
					PgXmlErrorContext *xmlerrcxt;
					volatile xmlBufferPtr buf = NULL;
					volatile xmlTextWriterPtr writer = NULL;
					char	   *result;

					xmlerrcxt = pg_xml_init(PG_XML_STRICTNESS_ALL);

					PG_TRY();
					{
						buf = xmlBufferCreate();
						if (buf == NULL || xmlerrcxt->err_occurred)
							xml_ereport(xmlerrcxt, ERROR, ERRCODE_OUT_OF_MEMORY,
										"could not allocate xmlBuffer");
						writer = xmlNewTextWriterMemory(buf, 0);
						if (writer == NULL || xmlerrcxt->err_occurred)
							xml_ereport(xmlerrcxt, ERROR, ERRCODE_OUT_OF_MEMORY,
										"could not allocate xmlTextWriter");

						if (xmlbinary == XMLBINARY_BASE64)
							xmlTextWriterWriteBase64(writer, VARDATA_ANY(bstr),
												 0, VARSIZE_ANY_EXHDR(bstr));
						else
							xmlTextWriterWriteBinHex(writer, VARDATA_ANY(bstr),
												 0, VARSIZE_ANY_EXHDR(bstr));

						/* we MUST do this now to flush data out to the buffer */
						xmlFreeTextWriter(writer);
						writer = NULL;

						result = pstrdup((const char *) xmlBufferContent(buf));
					}
					PG_CATCH();
					{
						if (writer)
							xmlFreeTextWriter(writer);
						if (buf)
							xmlBufferFree(buf);

						pg_xml_done(xmlerrcxt, true);

						PG_RE_THROW();
					}
					PG_END_TRY();

					xmlBufferFree(buf);

					pg_xml_done(xmlerrcxt, false);

					return result;
				}
#endif   /* USE_LIBXML */

		}
