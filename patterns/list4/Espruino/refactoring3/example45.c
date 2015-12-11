switch (device) {
   case EV_I2C1 : return I2C1;
   case EV_I2C2 : return I2C2;
#ifdef I2C3
   case EV_I2C3 : return I2C3;
#endif
   default: return 0;
 }
