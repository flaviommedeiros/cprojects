switch (masterConfig.blackbox_device) {
        case BLACKBOX_DEVICE_SERIAL:
            {
                serialPortConfig_t *portConfig = findSerialPortConfig(FUNCTION_BLACKBOX);
                baudRate_e baudRateIndex;
                portOptions_t portOptions = SERIAL_PARITY_NO | SERIAL_NOT_INVERTED;

                if (!portConfig) {
                    return false;
                }

                blackboxPortSharing = determinePortSharing(portConfig, FUNCTION_BLACKBOX);
                baudRateIndex = portConfig->blackbox_baudrateIndex;

                if (baudRates[baudRateIndex] == 230400) {
                    /*
                     * OpenLog's 230400 baud rate is very inaccurate, so it requires a larger inter-character gap in
                     * order to maintain synchronization.
                     */
                    portOptions |= SERIAL_STOPBITS_2;
                } else {
                    portOptions |= SERIAL_STOPBITS_1;
                }

                blackboxPort = openSerialPort(portConfig->identifier, FUNCTION_BLACKBOX, NULL, baudRates[baudRateIndex],
                    BLACKBOX_SERIAL_PORT_MODE, portOptions);

                /*
                 * The slowest MicroSD cards have a write latency approaching 150ms. The OpenLog's buffer is about 900
                 * bytes. In order for its buffer to be able to absorb this latency we must write slower than 6000 B/s.
                 *
                 * So:
                 *     Bytes per loop iteration = floor((looptime_ns / 1000000.0) * 6000)
                 *                              = floor((looptime_ns * 6000) / 1000000.0)
                 *                              = floor((looptime_ns * 3) / 500.0)
                 *                              = (looptime_ns * 3) / 500
                 */
                blackboxMaxHeaderBytesPerIteration = constrain((masterConfig.looptime * 3) / 500, 1, BLACKBOX_TARGET_HEADER_BUDGET_PER_ITERATION);

                return blackboxPort != NULL;
            }
            break;
#ifdef USE_FLASHFS
        case BLACKBOX_DEVICE_FLASH:
            if (flashfsGetSize() == 0 || isBlackboxDeviceFull()) {
                return false;
            }

            blackboxMaxHeaderBytesPerIteration = BLACKBOX_TARGET_HEADER_BUDGET_PER_ITERATION;

            return true;
        break;
#endif
        default:
            return false;
    }
