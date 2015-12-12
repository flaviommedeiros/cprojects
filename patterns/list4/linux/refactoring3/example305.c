switch (info->var.bits_per_pixel) {
	case 1:
		current_par.palette_size = 2;
		info->fix.visual = FB_VISUAL_MONO10;
		break;
	case 2:
		current_par.palette_size = 4;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		break;
	case 4:
		current_par.palette_size = 16;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		break;
	case 8:
		current_par.palette_size = VIDC_PALETTE_SIZE;
		info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
		break;
#ifdef HAS_VIDC20
	case 16:
		current_par.palette_size = 32;
		info->fix.visual = FB_VISUAL_DIRECTCOLOR;
		break;
	case 32:
		current_par.palette_size = VIDC_PALETTE_SIZE;
		info->fix.visual = FB_VISUAL_DIRECTCOLOR;
		break;
#endif
	default:
		BUG();
	}
