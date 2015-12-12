switch (reg_info[i].width) {
			case sizeof(u8):
				FRAME_REG(i, u8) = state.regs[i].value;
				break;
			case sizeof(u16):
				FRAME_REG(i, u16) = state.regs[i].value;
				break;
			case sizeof(u32):
				FRAME_REG(i, u32) = state.regs[i].value;
				break;
#ifdef CONFIG_64BIT
			case sizeof(u64):
				FRAME_REG(i, u64) = state.regs[i].value;
				break;
#endif
			default:
				return -EIO;
			}
