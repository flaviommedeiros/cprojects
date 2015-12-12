switch(sisbios_mode[mode_idx].mode_no[ivideo->mni]) {
	case 0x59:
	case 0x41:
	case 0x4f:
	case 0x50:
	case 0x56:
	case 0x53:
	case 0x2f:
	case 0x5d:
	case 0x5e:
		return true;
#ifdef CONFIG_FB_SIS_315
	case 0x5a:
	case 0x5b:
		if(ivideo->sisvga_engine == SIS_315_VGA) return true;
#endif
	}
