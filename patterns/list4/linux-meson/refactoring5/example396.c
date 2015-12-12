#ifdef CONFIG_BINFMT_ZFLAT
if (flags & FLAT_FLAG_GZDATA) {
			result = decompress_exec(bprm, fpos, (char *) datapos, 
						 full_data, 0);
		} else
#endif
		{
			result = read_code(bprm->file, datapos, fpos,
					full_data);
		}
