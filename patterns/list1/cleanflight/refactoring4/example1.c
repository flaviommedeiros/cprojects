#ifdef GYRO_MPU6000_ALIGN
if (mpu6500GyroDetect(&gyro) || mpu6500SpiGyroDetect(&gyro))
#else
            if (mpu6500GyroDetect(&gyro))
#endif
            {
                gyroHardware = GYRO_MPU6500;
#ifdef GYRO_MPU6500_ALIGN
                gyroAlign = GYRO_MPU6500_ALIGN;
#endif

                break;
            }
