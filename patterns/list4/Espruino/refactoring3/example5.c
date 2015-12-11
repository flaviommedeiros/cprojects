switch (hpcd->Init.speed)
  {
#ifndef STM32F1  
  case PCD_SPEED_HIGH:
    speed = USBD_SPEED_HIGH;
    break;
#endif    
  case PCD_SPEED_FULL:
    speed = USBD_SPEED_FULL;    
    break;

  default:
    speed = USBD_SPEED_FULL;    
    break;    
  }
