if (0 == opal_argv_count(mca_oob_tcp_component.ipv4conns)
#if OPAL_ENABLE_IPV6
        && 0 == opal_argv_count(mca_oob_tcp_component.ipv6conns)
#endif
        ) {
        if (including) {
            orte_show_help("help-oob-tcp.txt", "no-included-found", true, mca_oob_tcp_component.if_include);
        } else if (excluding) {
            orte_show_help("help-oob-tcp.txt", "excluded-all", true, mca_oob_tcp_component.if_exclude);
        }
        return false;
    }
