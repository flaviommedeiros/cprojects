#ifdef CONFIG_THUMB2_KERNEL
if (thumb_mode(regs)) {
			instr = __mem_to_opcode_thumb16(((u16 *)pc)[0]);
			if (is_wide_instruction(instr)) {
				u16 inst2;
				inst2 = __mem_to_opcode_thumb16(((u16 *)pc)[1]);
				instr = __opcode_thumb32_compose(instr, inst2);
			}
		} else
#endif
			instr = __mem_to_opcode_arm(*(u32 *) pc);
