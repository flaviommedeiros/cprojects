#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
if (imajor(inode) == MISC_MAJOR)
		i = MOUSEDEV_MIX;
	else
#endif
		i = iminor(inode) - MOUSEDEV_MINOR_BASE;
