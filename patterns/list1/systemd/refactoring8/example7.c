static const MountPoint mount_table[] = {
                { "proc",      "/proc",          "proc",   NULL,        MS_NOSUID|MS_NOEXEC|MS_NODEV,                              true,  true, false  },
                { "/proc/sys", "/proc/sys",      NULL,     NULL,        MS_BIND,                                                   true,  true, false  },   /* Bind mount first */
                { NULL,        "/proc/sys",      NULL,     NULL,        MS_BIND|MS_RDONLY|MS_NOSUID|MS_NOEXEC|MS_NODEV|MS_REMOUNT, true,  true, false  },   /* Then, make it r/o */
                { "tmpfs",     "/sys",           "tmpfs",  "mode=755",  MS_NOSUID|MS_NOEXEC|MS_NODEV,                              true,  false, true },
                { "sysfs",     "/sys",           "sysfs",  NULL,        MS_RDONLY|MS_NOSUID|MS_NOEXEC|MS_NODEV,                    true,  false, false },
                { "tmpfs",     "/dev",           "tmpfs",  "mode=755",  MS_NOSUID|MS_STRICTATIME,                                  true,  false, false },
                { "tmpfs",     "/dev/shm",       "tmpfs",  "mode=1777", MS_NOSUID|MS_NODEV|MS_STRICTATIME,                         true,  false, false },
                { "tmpfs",     "/run",           "tmpfs",  "mode=755",  MS_NOSUID|MS_NODEV|MS_STRICTATIME,                         true,  false, false },
                { "tmpfs",     "/tmp",           "tmpfs",  "mode=1777", MS_STRICTATIME,                                            true,  false, false },
#ifdef HAVE_SELINUX
                { "/sys/fs/selinux", "/sys/fs/selinux", NULL, NULL,     MS_BIND,                                                   false, false, false },  /* Bind mount first */
                { NULL,              "/sys/fs/selinux", NULL, NULL,     MS_BIND|MS_RDONLY|MS_NOSUID|MS_NOEXEC|MS_NODEV|MS_REMOUNT, false, false, false },  /* Then, make it r/o */
#endif
        };
