switch ((int)obj->i2c.i2c) {
#ifdef I2C0
        case I2C_0:
            index = 0;
            break;
#endif
#ifdef I2C1
        case I2C_1:
            index = 1;
            break;
#endif
        default:
            printf("I2C module not available.. Out of bound access.");
            break;
    }
