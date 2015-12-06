#ifdef ACC_MPU6000_ALIGN
if (mpu6500AccDetect(&acc) || mpu6500SpiAccDetect(&acc))
#else
            if (mpu6500AccDetect(&acc))
#endif
            {
#ifdef ACC_MPU6500_ALIGN
                accAlign = ACC_MPU6500_ALIGN;
#endif
                accHardware = ACC_MPU6500;
                break;
            }
