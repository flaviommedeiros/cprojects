#ifdef __BORLANDC__
if ((handle= findfirst(tmp_path,&find,0)) == -1L)
#else
  if ((handle=_findfirst(tmp_path,&find)) == -1L)
#endif
  {
    DBUG_PRINT("info", ("findfirst returned error, errno: %d", errno));
    if  (errno != EINVAL)
      goto error;
    /*
      Could not read the directory, no read access.
      Probably because by "chmod -r".
      continue and return zero files in dir
    */
  }
  else
  {

    do
    {
#ifdef __BORLANDC__
      attrib= find.ff_attrib;
#else
      attrib= find.attrib;
      /*
        Do not show hidden and system files which Windows sometimes create.
        Note. Because Borland's findfirst() is called with the third
        argument = 0 hidden/system files are excluded from the search.
      */
      if (attrib & (_A_HIDDEN | _A_SYSTEM))
        continue;
#endif
#ifdef __BORLANDC__
      if (!(finfo.name= strdup_root(names_storage, find.ff_name)))
        goto error;
#else
      if (!(finfo.name= strdup_root(names_storage, find.name)))
        goto error;
#endif
      if (MyFlags & MY_WANT_STAT)
      {
        if (!(finfo.mystat= (MY_STAT*)alloc_root(names_storage,
                                                 sizeof(MY_STAT))))
          goto error;

        memset(finfo.mystat, 0, sizeof(MY_STAT));
#ifdef __BORLANDC__
        finfo.mystat->st_size=find.ff_fsize;
#else
        finfo.mystat->st_size=find.size;
#endif
        mode= MY_S_IREAD;
        if (!(attrib & _A_RDONLY))
          mode|= MY_S_IWRITE;
        if (attrib & _A_SUBDIR)
          mode|= MY_S_IFDIR;
        finfo.mystat->st_mode= mode;
#ifdef __BORLANDC__
        finfo.mystat->st_mtime= ((uint32) find.ff_ftime);
#else
        finfo.mystat->st_mtime= ((uint32) find.time_write);
#endif
      }
      else
        finfo.mystat= NULL;

      if (push_dynamic(dir_entries_storage, (uchar*)&finfo))
        goto error;
    }
#ifdef __BORLANDC__
    while (findnext(&find) == 0);
#else
    while (_findnext(handle,&find) == 0);

    _findclose(handle);
#endif
  }
