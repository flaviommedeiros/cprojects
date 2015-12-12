switch (device) {
#ifdef USE_DMA1
    case I2C_1:
            return &pub_drivers[0];
#endif	/* USE_DMA1 */
#ifdef USE_DMA2
    case I2C_2:
        return &pub_drivers[1];
#endif	/* USE_DMA2 */
    default:
        return NULL;
    }
