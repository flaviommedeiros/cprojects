switch (info->var.bits_per_pixel) {
	case 8:
		/* PseudoColor, 256 */
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		break;
	case 16:
		/* TrueColor, 64k */
		info->fix.visual = FB_VISUAL_TRUECOLOR;

		for (i = 0; i < 64; i++) {
			outb(i, 0x3c8);

			outb(i << 1, 0x3c9);
			outb(i, 0x3c9);
			outb(i << 1, 0x3c9);
		}
		break;
	case 24:
#ifdef NO_32BIT_SUPPORT_YET
	case 32:
#endif
		/* TrueColor, 16m */
		info->fix.visual = FB_VISUAL_TRUECOLOR;

		for (i = 0; i < 256; i++) {
			outb(i, 0x3c8);

			outb(i, 0x3c9);
			outb(i, 0x3c9);
			outb(i, 0x3c9);
		}
		break;
	}
