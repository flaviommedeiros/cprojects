switch(afs_entry_point){
#if defined(AFS_SYSCALL) || defined(AFS_SYSCALL2) || defined(AFS_SYSCALL3)
    case SINGLE_ENTRY_POINT:
    case SINGLE_ENTRY_POINT2:
    case SINGLE_ENTRY_POINT3:
	return syscall(afs_syscalls[0], AFSCALL_PIOCTL,
		       a_path, o_opcode, a_paramsP, a_followSymlinks);
#endif
#if defined(AFS_PIOCTL)
    case MULTIPLE_ENTRY_POINT:
	return syscall(afs_syscalls[0],
		       a_path, o_opcode, a_paramsP, a_followSymlinks);
#endif
    case LINUX_PROC_POINT: {
	struct procdata data = { 0, 0, 0, 0, AFSCALL_PIOCTL };
	data.param1 = (unsigned long)a_path;
	data.param2 = (unsigned long)o_opcode;
	data.param3 = (unsigned long)a_paramsP;
	data.param4 = (unsigned long)a_followSymlinks;
	return do_ioctl(&data);
    }
    case MACOS_DEV_POINT: {
	struct devdata data = { AFSCALL_PIOCTL, 0, 0, 0, 0, 0, 0, 0 };
	int ret;

	data.param1 = (unsigned long)a_path;
	data.param2 = (unsigned long)o_opcode;
	data.param3 = (unsigned long)a_paramsP;
	data.param4 = (unsigned long)a_followSymlinks;

	ret = do_ioctl(&data);
	if (ret)
	    return ret;

	return data.retval;
    }
    case SUN_PROC_POINT: {
	struct sundevdata data = { 0, 0, 0, 0, 0, 0, AFSCALL_PIOCTL };
	data.param1 = (unsigned long)a_path;
	data.param2 = (unsigned long)o_opcode;
	data.param3 = (unsigned long)a_paramsP;
	data.param4 = (unsigned long)a_followSymlinks;
	return do_ioctl(&data);
    }
#ifdef _AIX
    case AIX_ENTRY_POINTS:
	return Pioctl(a_path, o_opcode, a_paramsP, a_followSymlinks);
#endif
    }
