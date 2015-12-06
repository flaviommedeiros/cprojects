switch (masterConfig.blackbox_device) {

#ifdef USE_FLASHFS
        case BLACKBOX_DEVICE_FLASH:
            length = strlen(s);
            flashfsWrite((const uint8_t*) s, length, false); // Write asynchronously
        break;
#endif

        case BLACKBOX_DEVICE_SERIAL:
        default:
            pos = (uint8_t*) s;
            while (*pos) {
                serialWrite(blackboxPort, *pos);
                pos++;
            }

            length = pos - (uint8_t*) s;
        break;
    }
