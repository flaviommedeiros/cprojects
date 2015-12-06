switch (mcfg.acc_hardware) {
        case ACC_NONE: // disable ACC
            sensorsClear(SENSOR_ACC);
            break;
        case ACC_DEFAULT: // autodetect
#ifndef CJMCU
        case ACC_ADXL345: // ADXL345
            acc_params.useFifo = false;
            acc_params.dataRate = 800; // unused currently
            if (adxl345Detect(&acc_params, &acc))
                accHardware = ACC_ADXL345;
            if (mcfg.acc_hardware == ACC_ADXL345)
                break;
            ; // fallthrough
#endif
        case ACC_MPU6050: // MPU6050
            if (haveMpu && mpu_config.deviceType == MPU_60x0) {
                accHardware = ACC_MPU6050;
                if (mcfg.acc_hardware == ACC_MPU6050)
                    break;
            }
            ; // fallthrough
#ifdef NAZE
        case ACC_MPU6500: // MPU6500
            if (haveMpu && (mpu_config.deviceType >= MPU_65xx_I2C)) {
                accHardware = ACC_MPU6500;
                if (mcfg.acc_hardware == ACC_MPU6500)
                    break;
            }
            ; // fallthrough
        case ACC_MMA8452: // MMA8452
            if (mma8452Detect(&acc)) {
                accHardware = ACC_MMA8452;
                if (mcfg.acc_hardware == ACC_MMA8452)
                    break;
            }
            ; // fallthrough
        case ACC_BMA280: // BMA280
            if (bma280Detect(&acc)) {
                accHardware = ACC_BMA280;
                if (mcfg.acc_hardware == ACC_BMA280)
                    break;
            }
#endif
    }
