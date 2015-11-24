switch (masterConfig.blackbox_device) {
#ifdef USE_FLASHFS
        case BLACKBOX_DEVICE_FLASH:
            flashfsWriteByte(value); // Write byte asynchronously
        break;
#endif
        case BLACKBOX_DEVICE_SERIAL:
        default:
            serialWrite(blackboxPort, value);
        break;
    }
