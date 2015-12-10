switch (metric_index) {
    case 0:
        return mem_total_func();
    case 1:
        return mem_free_func();
    case 2:
        return mem_shared_func();
    case 3:
        return mem_buffers_func();
    case 4:
        return mem_cached_func();
    case 5:
        return swap_free_func();
    case 6:
        return swap_total_func();
#ifdef LINUX
    case 7:
        return mem_sreclaimable_func();
#endif
#if HPUX
    case 7:
        return mem_arm_func();
    case 8:
        return mem_rm_func();
    case 9:
        return mem_avm_func();
    case 10:
        return mem_vm_func();
#endif
    }
