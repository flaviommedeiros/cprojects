switch (masterConfig.blackbox_device) {
        case BLACKBOX_DEVICE_SERIAL:
            /*
             * One byte of the tx buffer isn't available for user data (due to its circular list implementation),
             * hence the -1. Note that the USB VCP implementation doesn't use a buffer and has txBufferSize set to zero.
             */
            if (blackboxPort->txBufferSize && bytes > (int32_t) blackboxPort->txBufferSize - 1) {
                return BLACKBOX_RESERVE_PERMANENT_FAILURE;
            }

            return BLACKBOX_RESERVE_TEMPORARY_FAILURE;

#ifdef USE_FLASHFS
        case BLACKBOX_DEVICE_FLASH:
            if (bytes > (int32_t) flashfsGetWriteBufferSize()) {
                return BLACKBOX_RESERVE_PERMANENT_FAILURE;
            }

            if (bytes > (int32_t) flashfsGetWriteBufferFreeSpace()) {
                /*
                 * The write doesn't currently fit in the buffer, so try to make room for it. Our flushing here means
                 * that the Blackbox header writing code doesn't have to guess about the best time to ask flashfs to
                 * flush, and doesn't stall waiting for a flush that would otherwise not automatically be called.
                 */
                flashfsFlushAsync();
            }

            return BLACKBOX_RESERVE_TEMPORARY_FAILURE;
#endif

        default:
            return BLACKBOX_RESERVE_PERMANENT_FAILURE;
    }
