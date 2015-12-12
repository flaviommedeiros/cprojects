switch (ELF_R_TYPE(rel[i].r_info)) {

#define MUNGE(func) (*location = ((*location & ~func(-1)) | func(value)))

#ifndef __tilegx__
		case R_TILE_32:
			*(uint32_t *)location = value;
			break;
		case R_TILE_IMM16_X0_HA:
			value = (value + 0x8000) >> 16;
			/*FALLTHROUGH*/
		case R_TILE_IMM16_X0_LO:
			MUNGE(create_Imm16_X0);
			break;
		case R_TILE_IMM16_X1_HA:
			value = (value + 0x8000) >> 16;
			/*FALLTHROUGH*/
		case R_TILE_IMM16_X1_LO:
			MUNGE(create_Imm16_X1);
			break;
		case R_TILE_JOFFLONG_X1:
			value -= (unsigned long) location;  /* pc-relative */
			value = (long) value >> 3;     /* count by instrs */
			MUNGE(create_JOffLong_X1);
			break;
#else
		case R_TILEGX_64:
			*location = value;
			break;
		case R_TILEGX_IMM16_X0_HW2_LAST:
			if (!validate_hw2_last(value, me))
				return -ENOEXEC;
			value >>= 16;
			/*FALLTHROUGH*/
		case R_TILEGX_IMM16_X0_HW1:
			value >>= 16;
			/*FALLTHROUGH*/
		case R_TILEGX_IMM16_X0_HW0:
			MUNGE(create_Imm16_X0);
			break;
		case R_TILEGX_IMM16_X1_HW2_LAST:
			if (!validate_hw2_last(value, me))
				return -ENOEXEC;
			value >>= 16;
			/*FALLTHROUGH*/
		case R_TILEGX_IMM16_X1_HW1:
			value >>= 16;
			/*FALLTHROUGH*/
		case R_TILEGX_IMM16_X1_HW0:
			MUNGE(create_Imm16_X1);
			break;
		case R_TILEGX_JUMPOFF_X1:
			value -= (unsigned long) location;  /* pc-relative */
			value = (long) value >> 3;     /* count by instrs */
			if (!validate_jumpoff(value)) {
				pr_warning("module %s: Out of range jump to"
					   " %#llx at %#llx (%p)\n", me->name,
					   sym->st_value + rel[i].r_addend,
					   rel[i].r_offset, location);
				return -ENOEXEC;
			}
			MUNGE(create_JumpOff_X1);
			break;
#endif

#undef MUNGE

		default:
			pr_err("module %s: Unknown relocation: %d\n",
			       me->name, (int) ELF_R_TYPE(rel[i].r_info));
			return -ENOEXEC;
		}
