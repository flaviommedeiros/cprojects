switch (masterConfig.blackbox_device) {
        case BLACKBOX_DEVICE_SERIAL:
            return false;

#ifdef USE_FLASHFS
        case BLACKBOX_DEVICE_FLASH:
            return flashfsIsEOF();
#endif

        default:
            return false;
    }
