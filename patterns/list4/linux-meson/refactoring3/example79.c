switch(clk){
        case 2971:      // only for 4k mode
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case 2976:		// only for 4k mode with clock*0.999
#endif
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x0000043d);
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
            if( clk == 2976 )
                aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69d84d04); // lower div_frac to get clk*0.999
            else
                aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69d84e00);
#else
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69d84e00);
#endif
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0xca46c023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x4123b100);
            aml_set_reg32_bits(P_HHI_VID2_PLL_CNTL2, 1, 16, 1);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6000043d);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4000043d);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            h_delay();
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);   // optimise HPLL VCO 2.97GHz performance

            break;
        case 2970:      // for 1080p/i 720p mode
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case 2975:		// FOR 1080P/i 720p mode with clock*0.999
#endif
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x8a46c023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x4123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6000043d);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4000043d);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            h_delay();
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);   // optimise HPLL VCO 2.97GHz performance
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
			if( clk == 2975 )
				aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84d04); // lower div_frac to get clk*0.999
			else
				aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84e00);
#else
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84e00);
#endif
            break;
        case 2160:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x8a46c023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6001042d);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4001042d);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case 2161:/*for N200/M200 480p59hz*/
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84f48);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x8a46c023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6001042c);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4001042c);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
			break;
#endif
        case 1008:
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6000042a);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4000042a);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
        case 1080:
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6000042d);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4000042d);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case 1081:/*for N200/M200 480p59hz*/
			aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8cf48);
			aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6000042c);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4000042c);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
#endif
        case 1296:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c88000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0xca49b022);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0023b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x600c0436);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x400c0436);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);
			WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
        case 1600:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8c000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x8a7ad023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x4023d100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12286);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x60000442);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x40000442);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8c506);
            break;
        case 2380:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c80000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x0a563823);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x60010431);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x40010431);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8c994);
            break;
        case 2058:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c80000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x0a563823);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6001042a);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4001042a);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8cdf4);
            break;
        case 2600:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c80000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x0a563823);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x60010436);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x40010436);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8c294);
            break;
        case 2844:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x8a46c023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x4123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6000043b);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4000043b);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            h_delay();
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84418);
            break;
        case 1710:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8c000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x8a7ad023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x4023d100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12286);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x60000447);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x40000447);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8c3ac);
            break;
        case 1716:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8c000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x4023d100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x8a7ad023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12286);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x60000447);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x40000447);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8c7f8);
            break;
        case 2130:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c80000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x0a563823);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6001042c);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4001042c);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8c74f);
            break;
        case 2925:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c80000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x0a563823);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6001043c);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4001043c);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8cfb4);
            break;
        case 1936:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c80000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x0a563823);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x60010428);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x40010428);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c8c568);
            break;
        case 2016:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x8a46c023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6001042a);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4001042a);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
        default:
            printk("error hpll clk: %d\n", clk);
            break;
    }
