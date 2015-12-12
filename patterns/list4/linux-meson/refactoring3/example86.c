switch(mode)
	{
		case TVMODE_480I:
		case TVMODE_480I_RPT:
		case TVMODE_480CVBS:
		case TVMODE_480P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_480P_59HZ:
#endif
		case TVMODE_480P_RPT:
		case TVMODE_576I:
		case TVMODE_576CVBS:
		case TVMODE_576P:
			  //WRITE_MPEG_REG(HHI_VIID_CLK_DIV, (READ_MPEG_REG(HHI_VIID_CLK_DIV)&(~(0xff)))|0x3); // reg 0x104a 
			  #if MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8
			  WRITE_VCBUS_REG_BITS(VPU_VIU_VENC_MUX_CTRL, 1, 2, 2); //reg0x271a, select ENCT to VIU2
			  WRITE_CBUS_REG_BITS(HHI_VIID_DIVIDER_CNTL, 0x03, 0, 2);
			  WRITE_CBUS_REG_BITS(HHI_VID2_PLL_CNTL5, 1, 16, 1);
			  aml_write_reg32(P_HHI_VID2_PLL_CNTL, 0x41000032);//--set vid2 pll < 1.7G
			  aml_write_reg32(P_HHI_VID2_PLL_CNTL2, 0x0421a000);
			  aml_write_reg32(P_HHI_VID2_PLL_CNTL3, 0xca45b823);
			  aml_write_reg32(P_HHI_VID2_PLL_CNTL4, 0xd4000d67);
			  aml_write_reg32(P_HHI_VID2_PLL_CNTL5, 0x01700001);//--
			  WRITE_CBUS_REG_BITS(HHI_VID2_PLL_CNTL, 0x01, 24, 5);//clock tree N=1
			  WRITE_CBUS_REG_BITS(HHI_VID2_PLL_CNTL, 0x36, 0, 9);//clock tree M=54
			  WRITE_CBUS_REG_BITS(HHI_VID2_PLL_CNTL, 0x00, 9, 2);//clock tree OD=0
			  WRITE_CBUS_REG_BITS(HHI_VID2_PLL_CNTL5, 0x01, 24, 1);//select CLK1 = 24x54 = 1296M
			  WRITE_CBUS_REG_BITS(HHI_DSI_LVDS_EDP_CNTL1, 0x00, 4, 1);
			  WRITE_CBUS_REG_BITS(HHI_VIID_DIVIDER_CNTL, 0x03, 15, 2);
			  WRITE_CBUS_REG_BITS(HHI_VIID_DIVIDER_CNTL, 0x05, 4, 3);//select 6
			  WRITE_CBUS_REG_BITS(HHI_VIID_DIVIDER_CNTL, 0x00, 8, 2);//select 0
			  WRITE_CBUS_REG_BITS(HHI_VIID_DIVIDER_CNTL, 0x00, 12, 3);//select 0 clock = 1296/6 = 216M
			  WRITE_CBUS_REG_BITS(HHI_VIID_CLK_CNTL, 0x0c, 16, 4);//select vid2_pll_clk & open bit19
			  WRITE_CBUS_REG_BITS(HHI_VIID_CLK_DIV, 0x03, 0, 4);//select 4 clock = 216/4 = 54M
			  WRITE_CBUS_REG_BITS(HHI_VIID_CLK_CNTL, 0x07, 0, 5);//open div1 div2 div4
			  WRITE_CBUS_REG_BITS(HHI_VID_CLK_DIV, 0x09, 28, 4);//reg 0x1059, select v2_clk_div2 for cts_enci_clk , 27MHz
			  WRITE_CBUS_REG_BITS(HHI_VIID_CLK_DIV, 0x09, 28, 4); //0x104a, select v2_clk_div2 for cts_vdac_clk[0] 
			  WRITE_CBUS_REG_BITS(HHI_VIID_CLK_DIV, 0x09, 24, 4); //0x104a, select v2_clk_div2 for cts_vdac_clk[1] (DAC3)
			  WRITE_CBUS_REG_BITS(HHI_VID2_PLL_CNTL, 0x01, 29, 1);//reset
			  WRITE_CBUS_REG_BITS(HHI_VID2_PLL_CNTL, 0x00, 29, 1);//clean reset
			  #endif
			  break;
		case TVMODE_720P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_720P_59HZ:
#endif
		case TVMODE_720P_50HZ:
		case TVMODE_1080I:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_1080I_59HZ:
#endif
		case TVMODE_1080I_50HZ:
        //WRITE_MPEG_REG(HHI_VIID_CLK_DIV, (READ_MPEG_REG(HHI_VIID_CLK_DIV)&(~(0xff)))|0x0); // reg 0x104a
        break;		    
		case TVMODE_1080P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_1080P_59HZ:
#endif
		case TVMODE_1080P_50HZ:
        //WRITE_MPEG_REG(HHI_VIID_CLK_DIV, (READ_MPEG_REG(HHI_VIID_CLK_DIV)&(~(0xff)))|0x1); // reg 0x104a
        break;		    
		default:
			printk(KERN_ERR "unsupport tv mode,video clk is not set!!\n");	
	}
