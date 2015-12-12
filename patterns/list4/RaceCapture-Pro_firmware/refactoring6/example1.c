if (ofs > fp->fsize					/* In read-only mode, clip offset with the file size */
#if !_FS_READONLY
            && !(fp->flag & FA_WRITE)
#endif
           ) ofs = fp->fsize;
