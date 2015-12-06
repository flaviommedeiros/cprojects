switch (masterConfig.blackbox_device) {
        case BLACKBOX_DEVICE_SERIAL:
            freeSpace = serialTxBytesFree(blackboxPort);
        break;
#ifdef USE_FLASHFS
        case BLACKBOX_DEVICE_FLASH:
            freeSpace = flashfsGetWriteBufferFreeSpace();
        break;
#endif
        default:
            freeSpace = 0;
    }
