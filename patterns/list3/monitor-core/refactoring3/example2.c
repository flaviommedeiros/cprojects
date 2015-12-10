switch (metric_index) {
    case 0:
        return disk_total_func();
    case 1:
        return disk_free_func();
    case 2:
        return part_max_used_func();
#ifdef SOLARIS
    case 3:
        return bread_sec_func();
    case 4:
        return bwrite_sec_func();
    case 5:
        return lread_sec_func();
    case 6:
        return lwrite_sec_func();
    case 7:
        return phread_sec_func();
    case 8:
        return phwrite_sec_func();
    case 9:
        return rcache_func();
    case 10:
        return wcache_func();
#endif
    }
