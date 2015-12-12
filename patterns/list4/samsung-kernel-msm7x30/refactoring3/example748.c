switch (ELF_R_TYPE(rel[i].r_info) & 0xff) {
#ifdef CONFIG_SPARC64
		case R_SPARC_64:
			location[0] = v >> 56;
			location[1] = v >> 48;
			location[2] = v >> 40;
			location[3] = v >> 32;
			location[4] = v >> 24;
			location[5] = v >> 16;
			location[6] = v >>  8;
			location[7] = v >>  0;
			break;

		case R_SPARC_DISP32:
			v -= (Elf_Addr) location;
			*loc32 = v;
			break;

		case R_SPARC_WDISP19:
			v -= (Elf_Addr) location;
			*loc32 = (*loc32 & ~0x7ffff) |
				((v >> 2) & 0x7ffff);
			break;

		case R_SPARC_OLO10:
			*loc32 = (*loc32 & ~0x1fff) |
				(((v & 0x3ff) +
				  (ELF_R_TYPE(rel[i].r_info) >> 8))
				 & 0x1fff);
			break;
#endif /* CONFIG_SPARC64 */

		case R_SPARC_32:
		case R_SPARC_UA32:
			location[0] = v >> 24;
			location[1] = v >> 16;
			location[2] = v >>  8;
			location[3] = v >>  0;
			break;

		case R_SPARC_WDISP30:
			v -= (Elf_Addr) location;
			*loc32 = (*loc32 & ~0x3fffffff) |
				((v >> 2) & 0x3fffffff);
			break;

		case R_SPARC_WDISP22:
			v -= (Elf_Addr) location;
			*loc32 = (*loc32 & ~0x3fffff) |
				((v >> 2) & 0x3fffff);
			break;

		case R_SPARC_LO10:
			*loc32 = (*loc32 & ~0x3ff) | (v & 0x3ff);
			break;

		case R_SPARC_HI22:
			*loc32 = (*loc32 & ~0x3fffff) |
				((v >> 10) & 0x3fffff);
			break;

		default:
			printk(KERN_ERR "module %s: Unknown relocation: %x\n",
			       me->name,
			       (int) (ELF_R_TYPE(rel[i].r_info) & 0xff));
			return -ENOEXEC;
		}
