switch (ELF32_R_TYPE(rel->r_info)) {
		case R_ARM_NONE:
			/* ignore */
			break;

		case R_ARM_ABS32:
		case R_ARM_TARGET1:
			*(u32 *)loc += sym->st_value;
			break;

		case R_ARM_PC24:
		case R_ARM_CALL:
		case R_ARM_JUMP24:
			if (sym->st_value & 3) {
				pr_err("%s: section %u reloc %u sym '%s': unsupported interworking call (ARM -> Thumb)\n",
				       module->name, relindex, i, symname);
				return -ENOEXEC;
			}

			offset = __mem_to_opcode_arm(*(u32 *)loc);
			offset = (offset & 0x00ffffff) << 2;
			if (offset & 0x02000000)
				offset -= 0x04000000;

			offset += sym->st_value - loc;

			/*
			 * Route through a PLT entry if 'offset' exceeds the
			 * supported range. Note that 'offset + loc + 8'
			 * contains the absolute jump target, i.e.,
			 * @sym + addend, corrected for the +8 PC bias.
			 */
			if (IS_ENABLED(CONFIG_ARM_MODULE_PLTS) &&
			    (offset <= (s32)0xfe000000 ||
			     offset >= (s32)0x02000000))
				offset = get_module_plt(module, loc,
							offset + loc + 8)
					 - loc - 8;

			if (offset <= (s32)0xfe000000 ||
			    offset >= (s32)0x02000000) {
				pr_err("%s: section %u reloc %u sym '%s': relocation %u out of range (%#lx -> %#x)\n",
				       module->name, relindex, i, symname,
				       ELF32_R_TYPE(rel->r_info), loc,
				       sym->st_value);
				return -ENOEXEC;
			}

			offset >>= 2;
			offset &= 0x00ffffff;

			*(u32 *)loc &= __opcode_to_mem_arm(0xff000000);
			*(u32 *)loc |= __opcode_to_mem_arm(offset);
			break;

	       case R_ARM_V4BX:
		       /* Preserve Rm and the condition code. Alter
			* other bits to re-code instruction as
			* MOV PC,Rm.
			*/
		       *(u32 *)loc &= __opcode_to_mem_arm(0xf000000f);
		       *(u32 *)loc |= __opcode_to_mem_arm(0x01a0f000);
		       break;

		case R_ARM_PREL31:
			offset = *(u32 *)loc + sym->st_value - loc;
			*(u32 *)loc = offset & 0x7fffffff;
			break;

		case R_ARM_MOVW_ABS_NC:
		case R_ARM_MOVT_ABS:
			offset = tmp = __mem_to_opcode_arm(*(u32 *)loc);
			offset = ((offset & 0xf0000) >> 4) | (offset & 0xfff);
			offset = (offset ^ 0x8000) - 0x8000;

			offset += sym->st_value;
			if (ELF32_R_TYPE(rel->r_info) == R_ARM_MOVT_ABS)
				offset >>= 16;

			tmp &= 0xfff0f000;
			tmp |= ((offset & 0xf000) << 4) |
				(offset & 0x0fff);

			*(u32 *)loc = __opcode_to_mem_arm(tmp);
			break;

#ifdef CONFIG_THUMB2_KERNEL
		case R_ARM_THM_CALL:
		case R_ARM_THM_JUMP24:
			/*
			 * For function symbols, only Thumb addresses are
			 * allowed (no interworking).
			 *
			 * For non-function symbols, the destination
			 * has no specific ARM/Thumb disposition, so
			 * the branch is resolved under the assumption
			 * that interworking is not required.
			 */
			if (ELF32_ST_TYPE(sym->st_info) == STT_FUNC &&
			    !(sym->st_value & 1)) {
				pr_err("%s: section %u reloc %u sym '%s': unsupported interworking call (Thumb -> ARM)\n",
				       module->name, relindex, i, symname);
				return -ENOEXEC;
			}

			upper = __mem_to_opcode_thumb16(*(u16 *)loc);
			lower = __mem_to_opcode_thumb16(*(u16 *)(loc + 2));

			/*
			 * 25 bit signed address range (Thumb-2 BL and B.W
			 * instructions):
			 *   S:I1:I2:imm10:imm11:0
			 * where:
			 *   S     = upper[10]   = offset[24]
			 *   I1    = ~(J1 ^ S)   = offset[23]
			 *   I2    = ~(J2 ^ S)   = offset[22]
			 *   imm10 = upper[9:0]  = offset[21:12]
			 *   imm11 = lower[10:0] = offset[11:1]
			 *   J1    = lower[13]
			 *   J2    = lower[11]
			 */
			sign = (upper >> 10) & 1;
			j1 = (lower >> 13) & 1;
			j2 = (lower >> 11) & 1;
			offset = (sign << 24) | ((~(j1 ^ sign) & 1) << 23) |
				((~(j2 ^ sign) & 1) << 22) |
				((upper & 0x03ff) << 12) |
				((lower & 0x07ff) << 1);
			if (offset & 0x01000000)
				offset -= 0x02000000;
			offset += sym->st_value - loc;

			/*
			 * Route through a PLT entry if 'offset' exceeds the
			 * supported range.
			 */
			if (IS_ENABLED(CONFIG_ARM_MODULE_PLTS) &&
			    (offset <= (s32)0xff000000 ||
			     offset >= (s32)0x01000000))
				offset = get_module_plt(module, loc,
							offset + loc + 4)
					 - loc - 4;

			if (offset <= (s32)0xff000000 ||
			    offset >= (s32)0x01000000) {
				pr_err("%s: section %u reloc %u sym '%s': relocation %u out of range (%#lx -> %#x)\n",
				       module->name, relindex, i, symname,
				       ELF32_R_TYPE(rel->r_info), loc,
				       sym->st_value);
				return -ENOEXEC;
			}

			sign = (offset >> 24) & 1;
			j1 = sign ^ (~(offset >> 23) & 1);
			j2 = sign ^ (~(offset >> 22) & 1);
			upper = (u16)((upper & 0xf800) | (sign << 10) |
					    ((offset >> 12) & 0x03ff));
			lower = (u16)((lower & 0xd000) |
				      (j1 << 13) | (j2 << 11) |
				      ((offset >> 1) & 0x07ff));

			*(u16 *)loc = __opcode_to_mem_thumb16(upper);
			*(u16 *)(loc + 2) = __opcode_to_mem_thumb16(lower);
			break;

		case R_ARM_THM_MOVW_ABS_NC:
		case R_ARM_THM_MOVT_ABS:
			upper = __mem_to_opcode_thumb16(*(u16 *)loc);
			lower = __mem_to_opcode_thumb16(*(u16 *)(loc + 2));

			/*
			 * MOVT/MOVW instructions encoding in Thumb-2:
			 *
			 * i	= upper[10]
			 * imm4	= upper[3:0]
			 * imm3	= lower[14:12]
			 * imm8	= lower[7:0]
			 *
			 * imm16 = imm4:i:imm3:imm8
			 */
			offset = ((upper & 0x000f) << 12) |
				((upper & 0x0400) << 1) |
				((lower & 0x7000) >> 4) | (lower & 0x00ff);
			offset = (offset ^ 0x8000) - 0x8000;
			offset += sym->st_value;

			if (ELF32_R_TYPE(rel->r_info) == R_ARM_THM_MOVT_ABS)
				offset >>= 16;

			upper = (u16)((upper & 0xfbf0) |
				      ((offset & 0xf000) >> 12) |
				      ((offset & 0x0800) >> 1));
			lower = (u16)((lower & 0x8f00) |
				      ((offset & 0x0700) << 4) |
				      (offset & 0x00ff));
			*(u16 *)loc = __opcode_to_mem_thumb16(upper);
			*(u16 *)(loc + 2) = __opcode_to_mem_thumb16(lower);
			break;
#endif

		default:
			pr_err("%s: unknown relocation: %u\n",
			       module->name, ELF32_R_TYPE(rel->r_info));
			return -ENOEXEC;
		}
