switch (type) {
    case GDB_BREAKPOINT_SW:
    case GDB_BREAKPOINT_HW:
        for (env = first_cpu; env != NULL; env = env->next_cpu) {
            err = cpu_breakpoint_remove(env, addr, BP_GDB);
            if (err)
                break;
        }
        return err;
#ifndef CONFIG_USER_ONLY
    case GDB_WATCHPOINT_WRITE:
    case GDB_WATCHPOINT_READ:
    case GDB_WATCHPOINT_ACCESS:
        for (env = first_cpu; env != NULL; env = env->next_cpu) {
            err = cpu_watchpoint_remove(env, addr, len, xlat_gdb_type[type]);
            if (err)
                break;
        }
        return err;
#endif
    default:
        return -ENOSYS;
    }
