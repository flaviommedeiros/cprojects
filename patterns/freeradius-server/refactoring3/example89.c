switch (dtype) {
#ifdef SQLT_AFC
		case SQLT_AFC:	/* ansii fixed char */
#endif
#ifdef SQLT_AFV
		case SQLT_AFV:	/* ansii var char */
#endif
		case SQLT_VCS:	/* var char */
		case SQLT_CHR:	/* char */
		case SQLT_STR:	/* string */
			status = OCIAttrGet((dvoid *)param, OCI_DTYPE_PARAM, (dvoid *)&dsize, NULL,
					    OCI_ATTR_DATA_SIZE, conn->error);
			if (status != OCI_SUCCESS) {
				ERROR("rlm_sql_oracle: OCIAttrGet() failed in sql_select_query");

				goto error;
			}

			MEM(row[i] = talloc_zero_array(row, char, dsize + 1));

			break;
		case SQLT_DAT:
		case SQLT_INT:
		case SQLT_UIN:
		case SQLT_FLT:
		case SQLT_PDN:
		case SQLT_BIN:
		case SQLT_NUM:
			MEM(row[i] = talloc_zero_array(row, char, dsize + 1));

			break;
		default:
			dsize = 0;
			row[i] = NULL;
			break;
		}
