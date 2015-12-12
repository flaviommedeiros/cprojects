switch (ELF32_R_TYPE(rel[i].r_info)) {
		case R_ARM_CALL:
		case R_ARM_PC24:
		case R_ARM_JUMP24:
			if (!duplicate_rel(base, rel, i,
					   __opcode_to_mem_arm(0x00ffffff)))
				ret++;
			break;
#ifdef CONFIG_THUMB2_KERNEL
		case R_ARM_THM_CALL:
		case R_ARM_THM_JUMP24:
			if (!duplicate_rel(base, rel, i,
					   __opcode_to_mem_thumb32(0x07ff2fff)))
				ret++;
#endif
		}
