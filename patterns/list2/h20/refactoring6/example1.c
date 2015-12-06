if (conf.memcached.host == NULL && (conf.cache.setup == setup_cache_memcached
#if H2O_USE_SESSION_TICKETS
                                        || conf.ticket.update_thread == ticket_memcached_updater
#endif
                                        )) {
        h2o_configurator_errprintf(cmd, node, "configuration of memcached is missing");
        return -1;
    }
