return can_transmit(CAN1,
                      id,     /* (EX/ST)ID: CAN ID */
#ifdef USE_CAN_EXT_ID
                      true,  /* IDE: CAN ID extended */
#else
                      false, /* IDE: CAN ID not extended */
#endif
                      false, /* RTR: Request transmit? */
                      len,   /* DLC: Data length */
                      (uint8_t *)buf);
