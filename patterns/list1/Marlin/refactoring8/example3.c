static const uint8_t u8g_dev_st7687_c144mvgd_init_seq[] PROGMEM = {
  U8G_ESC_CS(0),             /* disable chip */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_CS(1),             /* enable chip */
  U8G_ESC_RST(15),           /* do reset low pulse with (15*16)+2 milliseconds (=maximum delay)*/
  
  0x001,                        /* A0=0, SW reset */
  U8G_ESC_DLY(200),         /* delay 200 ms */
  
  0x0d7,                        /* EEPROM data auto re-load control */
  U8G_ESC_ADR(1),           /* data mode */
  0x09f,                             /* ARD = 1 */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_DLY(100),         /* delay 100 ms */
  
  0x0e0,                        /* EEPROM control in */
  U8G_ESC_ADR(1),           /* data mode */
  0x000,                             /*  */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_DLY(100),         /* delay 100 ms */
  
#ifdef NOT_REQUIRED  
  0x0fa,                        /* EEPROM function selection 8.1.66 */
  U8G_ESC_ADR(1),           /* data mode */
  0x000,                             /*  */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_DLY(100),         /* delay 100 ms */
#endif 

  0x0e3,                        /* Read from EEPROM, 8.1.55 */
  U8G_ESC_DLY(100),         /* delay 100 ms */

  0x0e1,                        /* EEPROM control out, 8.1.53 */
  U8G_ESC_DLY(100),         /* delay 100 ms */
  
  //0x028,                        /* display off */
  0x011,                                /* Sleep out & booster on */
  U8G_ESC_DLY(100),         /* delay 100 ms */
  
  0x0c0,                        /* Vop setting, 8.1.42 */
  U8G_ESC_ADR(1),           /* data mode */
  0x000,                             /*  */
  0x001,                             /*  3.6 + 256*0.04 = 13.84 Volt */
  U8G_ESC_ADR(0),           /* instruction mode */
  U8G_ESC_DLY(100),         /* delay 100 ms */
  
  0x0c3,                                /* Bias selection, 8.1.45 */
  U8G_ESC_ADR(1),           /* data mode */
  0x003,
  U8G_ESC_ADR(0),           /* instruction mode */
  
  0x0c4,                                /* Booster setting 8.1.46 */
  U8G_ESC_ADR(1),           /* data mode */
  0x007,
  U8G_ESC_ADR(0),           /* instruction mode */
  
  0x0c5,                                /* ??? */
  U8G_ESC_ADR(1),           /* data mode */
  0x001,
  U8G_ESC_ADR(0),           /* instruction mode */
  
  0x0cb,                                /* FV3 with Booster x2 control, 8.1.47 */
  U8G_ESC_ADR(1),           /* data mode */
  0x001,
  U8G_ESC_ADR(0),           /* instruction mode */
  
  0x036,                                /* Memory data access control, 8.1.28 */
  U8G_ESC_ADR(1),           /* data mode */
  0x080,
  U8G_ESC_ADR(0),           /* instruction mode */

  0x0b5,                                /* N-line control, 8.1.37 */
  U8G_ESC_ADR(1),           /* data mode */
  0x089,
  U8G_ESC_ADR(0),           /* instruction mode */


  0x0d0,                                /* Analog circuit setting, 8.1.49 */
  U8G_ESC_ADR(1),           /* data mode */
  0x01d,
  U8G_ESC_ADR(0),           /* instruction mode */

  0x0b7,                                /* Com/Seg Scan Direction, 8.1.38 */
  U8G_ESC_ADR(1),           /* data mode */
  0x040,
  U8G_ESC_ADR(0),           /* instruction mode */

  0x025,                                /* Write contrast, 8.1.17 */
  U8G_ESC_ADR(1),           /* data mode */
  0x03f,
  U8G_ESC_ADR(0),           /* instruction mode */

  0x03a,                                /* Interface pixel format, 8.1.32 */
  U8G_ESC_ADR(1),           /* data mode */
  0x004,                                /* 3: 12 bit per pixel Type A, 4: 12 bit Type B, 5: 16bit per pixel */
  U8G_ESC_ADR(0),           /* instruction mode */

  0x0b0,                                /* Display Duty setting, 8.1.34 */
  U8G_ESC_ADR(1),           /* data mode */
  0x07f,
  U8G_ESC_ADR(0),           /* instruction mode */

  0x0f0,                                /* Frame Freq. in Temp range A,B,C and D, 8.1.59 */
  U8G_ESC_ADR(1),           /* data mode */
  0x007,
  0x00c,
  0x00c,
  0x015,
  U8G_ESC_ADR(0),           /* instruction mode */

  0x0f9,                                /* Frame RGB Value, 8.1.65 */
  U8G_ESC_ADR(1),           /* data mode */
  0x000,
  0x005,
  0x008,
  0x00a,
  0x00c,
  0x00e,
  0x010,
  0x011,
  0x012,
  0x013,
  0x014,
  0x015,
  0x016,
  0x018,
  0x01a,
  0x01b,
  U8G_ESC_ADR(0),           /* instruction mode */

  0x0f9,                                /* Frame RGB Value, 8.1.65 */
  U8G_ESC_ADR(1),           /* data mode */
  0x000,
  0x000,
  0x000,
  0x000,
  0x033,
  0x055,
  0x055,
  0x055,
  U8G_ESC_ADR(0),           /* instruction mode */

  0x029,                        /* display on */

  U8G_ESC_CS(0),             /* disable chip */
  U8G_ESC_END                /* end of sequence */

};
