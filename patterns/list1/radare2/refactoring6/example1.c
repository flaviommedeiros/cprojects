if (r_buf_fread_at (bin->b, bin->shdr[i].sh_offset, (ut8*)sym,
#if R_BIN_ELF64
					bin->endian? "I2cS2L": "i2cs2l",
#else
					bin->endian? "3I2cS": "3i2cs",
#endif
					nsym) == -1) {
				eprintf ("Warning: read (sym)\n");
				free (ret);
				free (sym);
				free (strtab);
				return NULL;
			}
