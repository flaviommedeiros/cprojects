switch (address) {
#ifdef GPS
        case 0x8A:
#ifdef HOTT_DEBUG
            hottGPSRequests++;
#endif
            if (sensors(SENSOR_GPS)) {
                hottSendGPSResponse();
            }
            break;
#endif
        case 0x8E:
#ifdef HOTT_DEBUG
            hottEAMRequests++;
#endif
            hottSendEAMResponse();
            break;
    }
