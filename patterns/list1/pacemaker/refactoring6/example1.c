if (safe_str_eq(action, "monitor") && (
#if SUPPORT_HEARTBEAT
        safe_str_eq(standard, "heartbeat") ||
#endif
        safe_str_eq(standard, "lsb") || safe_str_eq(standard, "service"))) {
        action = "status";
    }
