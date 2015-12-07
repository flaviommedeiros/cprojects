if (pattern == NULL && (isdup == 0 || mflag != 0 ||
#ifdef	CONFIG_TEST
	    data_buf_size != 0 ||
#endif
	    flag == DB_SET_RECNO || flag == DB_GET_BOTH ||
	    flag == DB_CONSUME || flag == DB_CONSUME_WAIT)) {
#ifdef	CONFIG_TEST
		if (data_buf_size == 0) {
			F_CLR(&save, DB_DBT_USERMEM);
			F_SET(&save, DB_DBT_MALLOC);
		} else {
			(void)__os_malloc(
			    NULL, (size_t)data_buf_size, &save.data);
			save.ulen = (u_int32_t)data_buf_size;
			F_CLR(&save, DB_DBT_MALLOC);
			F_SET(&save, DB_DBT_USERMEM);
		}
#endif
		if (flag == DB_GET_BOTH) {
			if (userecno) {
				result = _GetUInt32(interp,
				    objv[(objc - 2)], &recno);
				if (result == TCL_OK) {
					key.data = &recno;
					key.size = sizeof(db_recno_t);
				} else
					goto out;
			} else {
				/*
				 * Some get calls (SET_*) can change the
				 * key pointers.  So, we need to store
				 * the allocated key space in a tmp.
				 */
				ret = _CopyObjBytes(interp, objv[objc-2],
				    &key.data, &key.size, &freekey);
				if (ret != 0) {
					result = _ReturnSetup(interp, ret,
					    DB_RETOK_DBGET(ret), "db get");
					goto out;
				}
			}
			ktmp = key.data;
			/*
			 * Already checked args above.  Fill in key and save.
			 * Save is used in the dbp->get call below to fill in
			 * data.
			 *
			 * If the "data" here is really a primary key--that
			 * is, if we're in a pget--and that primary key
			 * is a recno, treat it appropriately as an int.
			 */
			if (useprecno) {
				result = _GetUInt32(interp,
				    objv[objc - 1], &precno);
				if (result == TCL_OK) {
					save.data = &precno;
					save.size = sizeof(db_recno_t);
				} else
					goto out;
			} else {
				ret = _CopyObjBytes(interp, objv[objc-1],
				    &dtmp, &save.size, &freedata);
				if (ret != 0) {
					result = _ReturnSetup(interp, ret,
					    DB_RETOK_DBGET(ret), "db get");
					goto out;
				}
				save.data = dtmp;
			}
		} else if (flag != DB_CONSUME && flag != DB_CONSUME_WAIT) {
			if (userecno) {
				result = _GetUInt32(
				    interp, objv[(objc - 1)], &recno);
				if (result == TCL_OK) {
					key.data = &recno;
					key.size = sizeof(db_recno_t);
				} else
					goto out;
			} else {
				/*
				 * Some get calls (SET_*) can change the
				 * key pointers.  So, we need to store
				 * the allocated key space in a tmp.
				 */
				ret = _CopyObjBytes(interp, objv[objc-1],
				    &key.data, &key.size, &freekey);
				if (ret != 0) {
					result = _ReturnSetup(interp, ret,
					    DB_RETOK_DBGET(ret), "db get");
					goto out;
				}
			}
			ktmp = key.data;
#ifdef CONFIG_TEST
			if (mflag & DB_MULTIPLE) {
				if ((ret = __os_malloc(dbp->env,
				    (size_t)bufsize, &save.data)) != 0) {
					Tcl_SetResult(interp,
					    db_strerror(ret), TCL_STATIC);
					goto out;
				}
				save.ulen = (u_int32_t)bufsize;
				F_CLR(&save, DB_DBT_MALLOC);
				F_SET(&save, DB_DBT_USERMEM);
			}
#endif
		}

		data = save;

		if (ispget) {
			if (flag == DB_GET_BOTH) {
				pkey.data = save.data;
				pkey.size = save.size;
				data.data = NULL;
				data.size = 0;
			}
			F_SET(&pkey, DB_DBT_MALLOC);
			_debug_check();
			ret = dbp->pget(dbp,
			    txn, &key, &pkey, &data, flag | rmw);
		} else {
			_debug_check();
			ret = dbp->get(dbp,
			    txn, &key, &data, flag | rmw | mflag);
		}
		result = _ReturnSetup(interp, ret, DB_RETOK_DBGET(ret),
		    "db get");
		if (ret == 0) {
			/*
			 * Success.  Return a list of the form {name value}
			 * If it was a recno in key.data, we need to convert
			 * into a string/object representation of that recno.
			 */
			if (mflag & DB_MULTIPLE)
				result = _SetMultiList(interp,
				    retlist, &key, &data, type, flag);
			else if (type == DB_RECNO || type == DB_QUEUE)
				if (ispget)
					result = _Set3DBTList(interp,
					    retlist, &key, 1, &pkey,
					    useprecno, &data);
				else
					result = _SetListRecnoElem(interp,
					    retlist, *(db_recno_t *)key.data,
					    data.data, data.size);
			else {
				if (ispget)
					result = _Set3DBTList(interp,
					    retlist, &key, 0, &pkey,
					    useprecno, &data);
				else
					result = _SetListElem(interp, retlist,
					    key.data, key.size,
					    data.data, data.size);
			}
		}
		/*
		 * Free space from DBT.
		 *
		 * If we set DB_DBT_MALLOC, we need to free the space if and
		 * only if we succeeded and if DB allocated anything (the
		 * pointer has changed from what we passed in).  If
		 * DB_DBT_MALLOC is not set, this is a bulk get buffer, and
		 * needs to be freed no matter what.
		 */
		if (F_ISSET(&key, DB_DBT_MALLOC) && ret == 0 &&
		    key.data != ktmp)
			__os_ufree(dbp->env, key.data);
		if (F_ISSET(&data, DB_DBT_MALLOC) && ret == 0 &&
		    data.data != dtmp)
			__os_ufree(dbp->env, data.data);
		else if (!F_ISSET(&data, DB_DBT_MALLOC))
			__os_free(dbp->env, data.data);
		if (ispget && ret == 0 && pkey.data != save.data)
			__os_ufree(dbp->env, pkey.data);
		if (result == TCL_OK)
			Tcl_SetObjResult(interp, retlist);
		goto out;
	}
