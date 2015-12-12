switch (var->bits_per_pixel) {
	case 1:	case 2:	case 4:	case 8:
		var->red.offset    = 0;
		var->red.length    = var->bits_per_pixel;
		var->green         = var->red;
		var->blue          = var->red;
		var->transp.offset = 0;
		var->transp.length = 0;
		break;

#ifdef HAS_VIDC20
	case 16:
		var->red.offset    = 0;
		var->red.length    = 5;
		var->green.offset  = 5;
		var->green.length  = 5;
		var->blue.offset   = 10;
		var->blue.length   = 5;
		var->transp.offset = 15;
		var->transp.length = 1;
		break;

	case 32:
		var->red.offset    = 0;
		var->red.length    = 8;
		var->green.offset  = 8;
		var->green.length  = 8;
		var->blue.offset   = 16;
		var->blue.length   = 8;
		var->transp.offset = 24;
		var->transp.length = 4;
		break;
#endif
	default:
		return -EINVAL;
	}
