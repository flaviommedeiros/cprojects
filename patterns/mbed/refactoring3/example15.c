switch ((int)obj->i2c.i2c) {
#ifdef I2C0
        case I2C_0:
            clock = cmuClock_I2C0;
            break;
#endif
#ifdef I2C1
        case I2C_1:
            clock = cmuClock_I2C1;
            break;
#endif
        default:
            printf("I2C module not available.. Out of bound access. (clock)");
            clock = cmuClock_HFPER;
            break;
    }
