switch (i2c_get_index(obj)) {
#ifdef I2C0
        case 0:
            irq_number = I2C0_IRQn;
            break;
#endif
#ifdef I2C1
        case 1:
            irq_number = I2C1_IRQn;
            break;
#endif
    }
