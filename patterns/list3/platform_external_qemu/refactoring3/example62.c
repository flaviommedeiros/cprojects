switch (finfo.type) {
		case FB_TYPE_PACKED_PIXELS:
			/* Supported, no worries.. */
			break;
#ifdef VGA16_FBCON_SUPPORT
		case FB_TYPE_VGA_PLANES:
			/* VGA16 is supported, but that's it */
			if ( finfo.type_aux == FB_AUX_VGA_PLANES_VGA4 ) {
				if ( ioperm(0x3b4, 0x3df - 0x3b4 + 1, 1) < 0 ) {
					SDL_SetError("No I/O port permissions");
					FB_VideoQuit(this);
					return(-1);
				}
				this->SetVideoMode = FB_SetVGA16Mode;
				break;
			}
			/* Fall through to unsupported case */
#endif /* VGA16_FBCON_SUPPORT */
		default:
			SDL_SetError("Unsupported console hardware");
			FB_VideoQuit(this);
			return(-1);
	}
