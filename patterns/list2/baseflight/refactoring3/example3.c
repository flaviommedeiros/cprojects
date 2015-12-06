switch (mcfg.mag_hardware) {
        case MAG_NONE: // disable MAG
            sensorsClear(SENSOR_MAG);
            break;
        case MAG_DEFAULT: // autodetect

        case MAG_HMC5883L:
            if (hmc5883lDetect(&mag)) {
                magHardware = MAG_HMC5883L;
                if (mcfg.mag_hardware == MAG_HMC5883L)
                    break;
            }
            ; // fallthrough

#ifdef NAZE
        case MAG_AK8975:
            if (ak8975detect(&mag)) {
                magHardware = MAG_AK8975;
                if (mcfg.mag_hardware == MAG_AK8975)
                    break;
            }
#endif
    }
