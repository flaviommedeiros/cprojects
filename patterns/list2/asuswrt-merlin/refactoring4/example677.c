#if defined(HAVE_STATVFS) || defined(HAVE_STATFS)
if (statvfs(disks[disknum].path, &fsd) == -1)
#else
    if (statvfs(disks[disknum].path, &vfs) == -1)
#endif
    {
        snmp_log(LOG_ERR, "Couldn't open device %s\n",
                 disks[disknum].device);
        setPerrorstatus("statvfs dev/disk");
        return -1;
    }
