switch (LCD_Code) {
     default:
        LCD_WR_CMD(0x50, y1);
        LCD_WR_CMD(0x51, y2);
        LCD_WR_CMD(0x52, x2);
        LCD_WR_CMD(0x53, x1);
        break;
#ifndef SAVE_ON_FLASH
     case SSD1289:   /* 0x8989 */
        LCD_WR_CMD(0x44, y1 | (y2<<8));
        LCD_WR_CMD(0x45, x2);
        LCD_WR_CMD(0x46, x1);
        break;
     case HX8346A: 
     case HX8347A: 
     case HX8347D: 
        LCD_WR_CMD(0x02,y1>>8);
        LCD_WR_CMD(0x03,y1);
        LCD_WR_CMD(0x04,y2>>8);
        LCD_WR_CMD(0x05,y2);
        LCD_WR_CMD(0x06,x2>>8);
        LCD_WR_CMD(0x07,x2);
        LCD_WR_CMD(0x08,x1>>8); 
        LCD_WR_CMD(0x09,x1); 
        break;
#endif
  }
