switch( LCD_Code )
  {
     default:		 /* 0x9320 0x9325 0x9328 0x9331 0x5408 0x1505 0x0505 0x7783 0x4531 0x4535 */
          LCD_WR_CMD(0x0020, y );     
          LCD_WR_CMD(0x0021, x );     
	      break; 
#ifndef SAVE_ON_FLASH
     case SSD1298: 	 /* 0x8999 */
     case SSD1289:   /* 0x8989 */
	      LCD_WR_CMD(0x004e, y );      
          LCD_WR_CMD(0x004f, x );
	      break;  

     case HX8346A: 	 /* 0x0046 */
     case HX8347A: 	 /* 0x0047 */
     case HX8347D: 	 /* 0x0047 */
	      LCD_WR_CMD(0x02, y>>8 );                                                  
	      LCD_WR_CMD(0x03, y );  

	      LCD_WR_CMD(0x06, x>>8 );                           
	      LCD_WR_CMD(0x07, x );    
	
	      break;     
     case SSD2119:	 /* 3.5 LCD 0x9919 */
	      break; 
#endif
  }
