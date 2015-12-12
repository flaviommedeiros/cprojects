#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
if (imajor(inode) == MISC_MAJOR)
		mousedev = mousedev_mix;
	else
#endif
		mousedev = container_of(inode->i_cdev, struct mousedev, cdev);
