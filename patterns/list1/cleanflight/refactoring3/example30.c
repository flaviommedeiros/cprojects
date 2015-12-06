switch (masterConfig.blackbox_device) {
        case BLACKBOX_DEVICE_SERIAL:
            //Nothing to speed up flushing on serial, as serial is continuously being drained out of its buffer
            return isSerialTransmitBufferEmpty(blackboxPort);

#ifdef USE_FLASHFS
        case BLACKBOX_DEVICE_FLASH:
            return flashfsFlushAsync();
#endif

        default:
            return false;
    }
