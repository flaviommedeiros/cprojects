#if defined(__v850e__)
if (v & 1)
#else
				if (v & 3)
#endif
					ret = obj_reloc_dangerous;
