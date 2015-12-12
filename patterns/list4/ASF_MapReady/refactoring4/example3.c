#ifdef win32
if (odir[strlen(odir)-1]=='/' || odir[strlen(odir)-1]=='\\')
#else
    if (odir[strlen(odir)-1]=='/')
#endif
      sprintf(cp->out_file, "%s%s", odir, ofile);
    else
      sprintf(cp->out_file, "%s/%s", odir, ofile);
