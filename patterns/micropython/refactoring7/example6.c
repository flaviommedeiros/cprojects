return snprintf(dest, destsize, "%srw-rw-r--   1 root  root %9u %s %2u %02u:%02u %s\r\n",
                        type, (_u32)fno->fsize, ftp_month[mindex].month, day,
                    #if _USE_LFN
                        (fno->ftime >> 11) & 0x1f, (fno->ftime >> 5) & 0x3f, *fno->lfname ? fno->lfname : fno->fname);
