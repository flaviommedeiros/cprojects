___HIDDEN ___SCMOBJ path_expand_to_absolute
   ___P((char *path,
         char *directory,/******************* currently ignored*/
         char *new_path,
         ___SIZE_TS max_length),
        (path,
         directory,
         new_path,
         max_length)
char *path;
char *directory;
char *new_path;
___SIZE_TS max_length;)
{
  ___BOOL result = 0;
  FSSpec spec;
  short vol;
  ___SIZE_TS dir;
  char tmp[___PATH_MAX_LENGTH+1];
  Str255 ppath;

  if (path[0] == '~')
    {
      if (path[1] == '~')
        {
          /* "~~" or "~~:xxx..." */

          int i = 0;
          int j = 0;
          int sep = 0;
          char *tilde_dir;

          if (!has_FindFolder)
            goto ret;

          if (path[2]!='\0' && !DIR_SEPARATOR(path[2]))
            goto ret;

          tilde_dir = ___GSTATE->setup_params.gambitdir;
          if (tilde_dir == 0)
#ifdef ___GAMBITDIR
            tilde_dir = ___GAMBITDIR;
#else
            tilde_dir = ":Gambit";
#endif

          i += 2;

          while (*tilde_dir != '\0')
            if (j < ___PATH_MAX_LENGTH)
              {
                tmp[j] = *tilde_dir++;
                j++;
              }
            else
              goto ret;

          while (path[i] != '\0')
            if (j < ___PATH_MAX_LENGTH)
              {
                if (DIR_SEPARATOR(path[i]))
                  sep = 1;
                tmp[j++] = path[i++];
              }
            else
              goto ret;

          if (!sep)
            if (j < ___PATH_MAX_LENGTH)
              tmp[j++] = DIR_SEPARATOR1;
            else
              goto ret;

          tmp[j] = '\0';
          path = tmp;

          if (FindFolder (kOnSystemDisk,
                          kPreferencesFolderType,
                          0,
                          &vol,
                          &dir)
              != noErr)
            goto ret;
        }
      else if (path[1]!='\0' && !DIR_SEPARATOR(path[1]))
        {
          /* "~user" or "~user:xxx..." */

          goto ret; /* no equivalent on Macintosh */
        }
      else
        {
          /* "~" or "~:xxx..." */

          path++;
          vol = 0; /* use default volume and directory
                      (folder containing application) */
          dir = 0;
        }
    }
  else
    {
      vol = 0; /* use default volume and directory
                  (folder containing application) */
      dir = 0;
    }

  if (!c2pascal (path, ppath, 255) ||
      make_ResolvedFSSpec (vol, dir, ppath, &spec) != noErr ||
      ResolvedFSSpec_to_fullpath (&spec, ppath) != noErr ||
      !pascal2c (ppath, new_path, max_length))
    goto ret;

  result = 1;

 ret:

  return result;
}
