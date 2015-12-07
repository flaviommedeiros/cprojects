#ifndef DB_WINCE
if (__os_is_winnt()) {
			if (!MoveFileEx(
			    toldname, tnewname, MOVEFILE_REPLACE_EXISTING))
				ret = __os_get_syserr();
		} else
#endif
		{
			/*
			 * There is no MoveFileEx for Win9x/Me/CE, so we have to
			 * do the best we can.  Note that the MoveFile call
			 * above would have succeeded if oldname and newname
			 * refer to the same file, so we don't need to check
			 * that here.
			 */
			(void)DeleteFile(tnewname);
			if (!MoveFile(toldname, tnewname))
				ret = __os_get_syserr();
		}
