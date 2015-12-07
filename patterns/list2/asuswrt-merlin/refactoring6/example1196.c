if (dbus_bus_request_name(
            server->bus,
            AVAHI_DBUS_NAME,
#if (DBUS_VERSION_MAJOR == 0) && (DBUS_VERSION_MINOR < 60)
            DBUS_NAME_FLAG_PROHIBIT_REPLACEMENT,
#else
            DBUS_NAME_FLAG_DO_NOT_QUEUE,
#endif
            &error) != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
        if (dbus_error_is_set(&error)) {
            avahi_log_error("dbus_bus_request_name(): %s", error.message);
            goto fail;
        }

        avahi_log_error("Failed to acquire D-Bus name '"AVAHI_DBUS_NAME"'");
        goto fail;
    }
