static DPB dpb[] = {
/*      name    capac           spt     bsh     blm     exm     dsm     drm
        al0     al1     cks     off     psh     phm     ss      off skew                                                */
    { "HDSK",   HDSK_CAPACITY,  32,     0x05,   0x1F,   0x01,   0x07f9, 0x03FF,
        0xFF,   0x00,   0x0000, 0x0006, 0x00,   0x00,   0,      0,  NULL },             /* AZ80 HDSK                    */

    { "CPM68K", (1 << 24),      (1<<17),0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,  NULL },             /* CP/M-68K HDSK                */
    
    { "EZ80FL", 131072,         32,     0x03,   0x07,   0x00,   127,    0x003E,
        0xC0,   0x00,   0x0000, 0x0000, 0x02,   0x03,   0,      0,  NULL },             /* 128K FLASH                   */

    { "P112",   1474560,        72,     0x04,   0x0F,   0x00,   710,    0x00FE,
        0xF0,   0x00,   0x0000, 0x0002, 0x02,   0x03,   0,      0,  NULL },             /* 1.44M P112                   */

    { "SU720",  737280,         36,     0x04,   0x0F,   0x00,   354,    0x007E,
        0xC0,   0x00,   0x0020, 0x0002, 0x02,   0x03,   0,      0,  NULL },             /* 720K Super I/O               */

    { "OSB1",   102400,         20,     0x04,   0x0F,   0x01,   45,     0x003F,
        0x80,   0x00,   0x0000, 0x0003, 0x02,   0x03,   0,      0,  NULL },             /* Osborne1 5.25" SS SD         */

    { "OSB2",   204800,         40,     0x03,   0x07,   0x00,   184,    0x003F,
        0xC0,   0x00,   0x0000, 0x0003, 0x02,   0x03,   0,      0,  NULL },             /* Osborne1 5.25" SS DD         */

    { "NSSS1",  179200,         40,     0x03,   0x07,   0x00,   0xA4,   0x003F,
        0xC0,   0x00,   0x0010, 0x0002, 0x02,   0x03,   0,      0,  NULL },             /* Northstar SSDD Format 1      */

    { "NSSS2",  179200,         40,     0x04,   0x0F,   0x01,   0x51,   0x003F,
        0x80,   0x00,   0x0010, 0x0002, 0x02,   0x03,   0,      0,  NULL },             /* Northstar SSDD Format 2      */

    { "NSDS2",  358400,         40,     0x04,   0x0F,   0x01,   0xA9,   0x003F,
        0x80,   0x00,   0x0010, 0x0002, 0x02,   0x03,   0,      0,  NULL },             /* Northstar DSDD Format 2      */

    { "VGSS",   315392,         32,     0x04,   0x0F,   0x00,   149,    0x007F,
        0xC0,   0x00,   0x0020, 0x0002, 0x02,   0x03,   0,      0,  NULL },             /* Vector SS SD                 */

    { "VGDS",   630784,         32,     0x04,   0x0F,   0x00,   299,    0x007F,
        0xC0,   0x00,   0x0020, 0x0004, 0x02,   0x03,   0,      0,  NULL },             /* Vector DS SD                 */

    { "DISK1A", 630784,         64,     0x04,   0x0F,   0x00,   299,    0x007F,
        0xC0,   0x00,   0x0020, 0x0002, 0x02,   0x03,   0,      0,  NULL },             /* CompuPro Disk1A 8" SS SD     */

    { "SSSD8",  256256,         SPT26,  0x03,   0x07,   0x00,   242,    0x003F,
        0xC0,   0x00,   0x0000, 0x0002, 0x00,   0x00,   0,      0,  NULL },             /* Standard 8" SS SD            */

    { "SSSD8S",  256256,        SPT26,  0x03,   0x07,   0x00,   242,    0x003F,
        0xC0,   0x00,   0x0000, 0x0002, 0x00,   0x00,   0,      0,  standard8 },        /* Standard 8" SS SD with skew  */

    { "SSDD8",  512512,         SPT52,  0x04,   0x0F,   0x01,   242,    0x007F,
        0xC0,   0x00,   0x0000, 0x0002, 0x01,   0x01,   0,      0,  NULL },             /* Standard 8" SS DD            */

    { "SSDD8S", 512512,         SPT52,  0x04,   0x0F,   0x01,   242,    0x007F,
        0xC0,   0x00,   0x0000, 0x0002, 0x01,   0x01,   0,      0,  standard8 },        /* Standard 8" SS DD with skew  */

    { "DSDD8",  1025024,        SPT52,  0x04,   0x0F,   0x00,   493,    0x007F,
        0xC0,   0x00,   0x0000, 0x0002, 0x01,   0x01,   0,      0,  NULL },             /* Standard 8" DS DD            */

    { "DSDD8S", 1025024,        SPT52,  0x04,   0x0F,   0x00,   493,    0x007F,
        0xC0,   0x00,   0x0000, 0x0002, 0x01,   0x01,   0,      0,  NULL },             /* Standard 8" DS DD with skew  */

    {"512SSDD8",591360,         60,     0x04,   0x0F,   0x00,   280,    0x007F,
        0xC0,   0x00,   0x0000, 0x0002, 0x02,   0x03,   0,      0,  NULL },             /* Standard 8" SS DD with 512 byte sectors  */

    {"512DSDD8",1182720,        60,     0x04,   0x0F,   0x00,   569,    0x007F,
        0xC0,   0x00,   0x0000, 0x0002, 0x02,   0x03,   0,      0,  NULL },             /* Standard 8" DS DD with 512 byte sectors  */

#if 0
    /* CP/M 3 BIOS currently does not support physical sector size 1024 */
    {"1024SSDD8",630784,        64,     0x04,   0x0F,   0x00,   299,    0x007F,
        0xC0,   0x00,   0x0000, 0x0002, 0x03,   0x07,   0,      0,  NULL },             /* Standard 8" SS DD with 1024 byte sectors  */

    {"1024DSDD8",1261568,       64,     0x04,   0x0F,   0x00,   607,    0x007F,
        0xC0,   0x00,   0x0000, 0x0002, 0x03,   0x07,   0,      0,  NULL },             /* Standard 8" DS DD with 1024 byte sectors  */
#endif

    { "APPLE-DO",143360,        SPT32,  0x03,   0x07,   0x00,   127,    0x003F,
        0xC0,   0x00,   0x0000, 0x0003, 0x01,   0x01,   0,      0,  apple_ii_DOS },     /* Apple II DOS 3.3             */

    { "APPLE-PO",143360,        SPT32,  0x03,   0x07,   0x00,   127,    0x003F,
        0xC0,   0x00,   0x0000, 0x0003, 0x01,   0x01,   0,      0,  apple_ii_PRODOS },  /* Apple II PRODOS              */

    { "APPLE-D2",143360,        SPT32,  0x03,   0x07,   0x00,   127,    0x003F,
        0xC0,   0x00,   0x0000, 0x0003, 0x00,   0x00,   0,      0,  apple_ii_DOS2 },    /* Apple II DOS 3.3, deblocked */

    { "APPLE-P2",143360,        SPT32,  0x03,   0x07,   0x00,   127,    0x003F,
        0xC0,   0x00,   0x0000, 0x0003, 0x00,   0x00,   0,      0,  apple_ii_PRODOS2 }, /* Apple II PRODOS, deblocked  */

    { "MITS",   337568,         SPT32,  0x03,   0x07,   0x00,   254,    0x00FF,
        0xFF,   0x00,   0x0000, 0x0006, 0x00,   0x00,   137,    3,  mits },             /* MITS Altair original         */

    { "MITS2",  1113536,        SPT32,  0x04,   0x0F,   0x00,   0x1EF,  0x00FF,
        0xF0,   0x00,   0x0000, 0x0006, 0x00,   0x00,   137,    3,  mits },             /* MITS Altair original, extra  */

    /*
     dw     40              ;#128 byte records/track
     db     4,0fh           ;block shift mask (2K)
     db     1               ;extent  mask
     dw     194             ;maximun  block number
     dw     127             ;max number of dir entry - 1
     db     0C0H,00h        ;alloc vector for directory
     dw     0020h           ;checksum size
     dw     2               ;offset for sys tracks
     db     2,3             ;physical sector shift (512 sector)
     */
    { "V1050",  409600,             40, 0x04,   0x0F,   0x01,   194,    0x007F,
        0xC0,   0x00,   0x0000, 0x0002, 0x02,   0x03,   0,      0, NULL },              /* Visual Technology Visual 1050, http://www.metabarn.com/v1050/index.html  */

    { "", 0 }
};
