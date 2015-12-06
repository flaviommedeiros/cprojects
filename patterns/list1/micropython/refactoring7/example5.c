return snprintf(dest, destsize, "%srw-rw-r--   1 root  root %9u %s %2u %5u %s\r\n",
                        type, (_u32)fno->fsize, ftp_month[mindex].month, day,
                    #if _USE_LFN
                        1980 + ((fno->fdate >> 9) & 0x7f), *fno->lfname ? fno->lfname : fno->fname);
