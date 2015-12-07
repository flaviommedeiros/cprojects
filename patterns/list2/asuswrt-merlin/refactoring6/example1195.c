if (dbus_protocol_setup(poll_api,
                                config.disable_user_service_publishing,
                                config.n_clients_max,
                                config.n_objects_per_client_max,
                                config.n_entries_per_entry_group_max,
                                !c->fail_on_missing_dbus
#ifdef ENABLE_CHROOT
                                && !config.use_chroot
#endif
            ) < 0) {

            avahi_log_warn("WARNING: Failed to contact D-Bus daemon.");

            if (c->fail_on_missing_dbus)
                goto finish;
        }
