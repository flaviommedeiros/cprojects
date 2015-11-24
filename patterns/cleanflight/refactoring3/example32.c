switch (masterConfig.blackbox_device) {
        case BLACKBOX_DEVICE_SERIAL:
            closeSerialPort(blackboxPort);
            blackboxPort = NULL;

            /*
             * Normally this would be handled by mw.c, but since we take an unknown amount
             * of time to shut down asynchronously, we're the only ones that know when to call it.
             */
            if (blackboxPortSharing == PORTSHARING_SHARED) {
                mspAllocateSerialPorts(&masterConfig.serialConfig);
            }
            break;
#ifdef USE_FLASHFS
        case BLACKBOX_DEVICE_FLASH:
            // No-op since the flash doesn't have a "close" and there's nobody else to hand control of it to.
            break;
#endif
    }
