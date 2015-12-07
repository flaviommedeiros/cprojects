#ifdef CONFIG_BINFMT_ZFLAT
if (flags & FLAT_FLAG_GZDATA) {
			result = decompress_exec(bprm, fpos, (char *) datapos, 
						 data_len + (relocs * sizeof(unsigned long)), 0);
		} else
#endif
		{
			result = bprm->file->f_op->read(bprm->file, (char *) datapos,
					data_len + (relocs * sizeof(unsigned long)), &fpos);
		}
