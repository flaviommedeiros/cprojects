switch (fb->var.bits_per_pixel) {
		case 16:
			((u32 *) fb->pseudo_palette)[regno] =
				((red & 0xf800)) | ((green & 0xfc00) >> 5) |
				((blue & 0xf800) >> 11);
			break;
		case 24:
			((u32 *) fb->pseudo_palette)[regno] =
				((red & 0xff00) << 8) | ((green & 0xff00)) |
				((blue & 0xff00) >> 8);
			break;
#ifdef NO_32BIT_SUPPORT_YET
		case 32:
			((u32 *) fb->pseudo_palette)[regno] =
				((transp & 0xff00) << 16) | ((red & 0xff00) << 8) |
				((green & 0xff00)) | ((blue & 0xff00) >> 8);
			break;
#endif
		default:
			return 1;
		}
