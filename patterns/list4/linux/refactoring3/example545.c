switch (reg_info[state.regs[i].value].width) {
			case sizeof(u8):
				state.regs[i].value =
				FRAME_REG(state.regs[i].value, const u8);
				break;
			case sizeof(u16):
				state.regs[i].value =
				FRAME_REG(state.regs[i].value, const u16);
				break;
			case sizeof(u32):
				state.regs[i].value =
				FRAME_REG(state.regs[i].value, const u32);
				break;
#ifdef CONFIG_64BIT
			case sizeof(u64):
				state.regs[i].value =
				FRAME_REG(state.regs[i].value, const u64);
				break;
#endif
			default:
				return -EIO;
			}
