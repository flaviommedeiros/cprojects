switch (reg_info[i].width) {
			case sizeof(u8):
				__get_user(FRAME_REG(i, u8),
					   (u8 __user *)addr);
				break;
			case sizeof(u16):
				__get_user(FRAME_REG(i, u16),
					   (u16 __user *)addr);
				break;
			case sizeof(u32):
				__get_user(FRAME_REG(i, u32),
					   (u32 __user *)addr);
				break;
#ifdef CONFIG_64BIT
			case sizeof(u64):
				__get_user(FRAME_REG(i, u64),
					   (u64 __user *)addr);
				break;
#endif
			default:
				return -EIO;
			}
