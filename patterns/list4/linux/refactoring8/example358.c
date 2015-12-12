static const unsigned int irq_prio[PNX833X_PIC_NUM_IRQ] =
{
    0, /* unused */
    4, /* PNX833X_PIC_I2C0_INT		       1 */
    4, /* PNX833X_PIC_I2C1_INT		       2 */
    1, /* PNX833X_PIC_UART0_INT		       3 */
    1, /* PNX833X_PIC_UART1_INT		       4 */
    6, /* PNX833X_PIC_TS_IN0_DV_INT	       5 */
    6, /* PNX833X_PIC_TS_IN0_DMA_INT	       6 */
    7, /* PNX833X_PIC_GPIO_INT		       7 */
    4, /* PNX833X_PIC_AUDIO_DEC_INT	       8 */
    5, /* PNX833X_PIC_VIDEO_DEC_INT	       9 */
    4, /* PNX833X_PIC_CONFIG_INT	      10 */
    4, /* PNX833X_PIC_AOI_INT		      11 */
    9, /* PNX833X_PIC_SYNC_INT		      12 */
    9, /* PNX8335_PIC_SATA_INT		      13 */
    4, /* PNX833X_PIC_OSD_INT		      14 */
    9, /* PNX833X_PIC_DISP1_INT		      15 */
    4, /* PNX833X_PIC_DEINTERLACER_INT	      16 */
    9, /* PNX833X_PIC_DISPLAY2_INT	      17 */
    4, /* PNX833X_PIC_VC_INT		      18 */
    4, /* PNX833X_PIC_SC_INT		      19 */
    9, /* PNX833X_PIC_IDE_INT		      20 */
    9, /* PNX833X_PIC_IDE_DMA_INT	      21 */
    6, /* PNX833X_PIC_TS_IN1_DV_INT	      22 */
    6, /* PNX833X_PIC_TS_IN1_DMA_INT	      23 */
    4, /* PNX833X_PIC_SGDX_DMA_INT	      24 */
    4, /* PNX833X_PIC_TS_OUT_INT	      25 */
    4, /* PNX833X_PIC_IR_INT		      26 */
    3, /* PNX833X_PIC_VMSP1_INT		      27 */
    3, /* PNX833X_PIC_VMSP2_INT		      28 */
    4, /* PNX833X_PIC_PIBC_INT		      29 */
    4, /* PNX833X_PIC_TS_IN0_TRD_INT	      30 */
    4, /* PNX833X_PIC_SGDX_TPD_INT	      31 */
    5, /* PNX833X_PIC_USB_INT		      32 */
    4, /* PNX833X_PIC_TS_IN1_TRD_INT	      33 */
    4, /* PNX833X_PIC_CLOCK_INT		      34 */
    4, /* PNX833X_PIC_SGDX_PARSER_INT	      35 */
    4, /* PNX833X_PIC_VMSP_DMA_INT	      36 */
#if defined(CONFIG_SOC_PNX8335)
    4, /* PNX8335_PIC_MIU_INT		      37 */
    4, /* PNX8335_PIC_AVCHIP_IRQ_INT	      38 */
    9, /* PNX8335_PIC_SYNC_HD_INT	      39 */
    9, /* PNX8335_PIC_DISP_HD_INT	      40 */
    9, /* PNX8335_PIC_DISP_SCALER_INT	      41 */
    4, /* PNX8335_PIC_OSD_HD1_INT	      42 */
    4, /* PNX8335_PIC_DTL_WRITER_Y_INT	      43 */
    4, /* PNX8335_PIC_DTL_WRITER_C_INT	      44 */
    4, /* PNX8335_PIC_DTL_EMULATOR_Y_IR_INT   45 */
    4, /* PNX8335_PIC_DTL_EMULATOR_C_IR_INT   46 */
    4, /* PNX8335_PIC_DENC_TTX_INT	      47 */
    4, /* PNX8335_PIC_MMI_SIF0_INT	      48 */
    4, /* PNX8335_PIC_MMI_SIF1_INT	      49 */
    4, /* PNX8335_PIC_MMI_CDMMU_INT	      50 */
    4, /* PNX8335_PIC_PIBCS_INT		      51 */
   12, /* PNX8335_PIC_ETHERNET_INT	      52 */
    3, /* PNX8335_PIC_VMSP1_0_INT	      53 */
    3, /* PNX8335_PIC_VMSP1_1_INT	      54 */
    4, /* PNX8335_PIC_VMSP1_DMA_INT	      55 */
    4, /* PNX8335_PIC_TDGR_DE_INT	      56 */
    4, /* PNX8335_PIC_IR1_IRQ_INT	      57 */
#endif
};
