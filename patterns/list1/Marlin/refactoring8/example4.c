static const uint8_t u8g_dev_st7565_dogm132_init_seq[] PROGMEM = {
  U8G_ESC_CS(0),             /* disable chip */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_RST(1),           /* do reset low pulse with (1*16)+2 milliseconds */
  U8G_ESC_CS(1),             /* enable chip */

  0x040,		/* set display start line to 0 */
  0x0a1,		/* ADC set to reverse */
  0x0c0,		/* common output mode */
  0x0a6,		/* display normal, bit val 0: LCD pixel off. */
  0x0a2,		/* LCD bias 1/9 */
  0x02f,		/* all power  control circuits on */
  0x0f8,		/* set booster ratio to */
  0x000,		/* 4x */
  0x023,		/* set V0 voltage resistor ratio to large */
  0x081,		/* set contrast */
  0x01f,		/* contrast value, EA default: 0x01f */
  0x0ac,		/* indicator */
  0x000,		/* disable */
  0x0af,		/* display on */

#ifdef OBSOLETE_DOGM128  
  0x040,		                /* set display start line */
  0x0c8,		                /* set scan direction inverse operation */
  0x0a2,		                /* LCD bias 1/9 */
  0x02f,		                /* all power  control circuits on */
  0x0f8,		                /* set booster ratio to */
  0x000,		                /* 4x */
  0x027,		                /* set V0 voltage resistor ratio to large */
  0x081,		                /* set contrast */
  0x018,		                /* contrast value, EA default: 0x016 */
  0x0ac,		                /* indicator */
  0x000,		                /* disable */
  0x0af,		                /* display on */
#endif


  U8G_ESC_DLY(100),       /* delay 100 ms */
  0x0a5,		                /* display all points, ST7565 */
  U8G_ESC_DLY(100),       /* delay 100 ms */
  U8G_ESC_DLY(100),       /* delay 100 ms */
  0x0a4,		                /* normal display */
  U8G_ESC_CS(0),             /* disable chip */
  U8G_ESC_END                /* end of sequence */
};
