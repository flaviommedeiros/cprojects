switch(clk){
        case 2016:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x8a46c023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6001042a);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4001042a);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
        case 2970:
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
				aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84cf8); // lower div_frac to get clk*0.999
			else
				aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84e00);
#else
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84e00);
#endif
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
        case 2160:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x69c84000);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0x8a46c023);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0123b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x12385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x6001042d);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x4001042d);
            WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
        case 1980:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c88800);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0xca49b022);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0023b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x600c0452);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x400c0452);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);
			WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
        case 1575:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c885be);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0xca49b022);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0023b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x600c0444);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x400c0444);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);
			WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
        case 1485:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c88e00);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0xca49b022);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0023b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x600c043d);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x400c043d);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);
			WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;
        case 1350:
            aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c88400);
            aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0xca49b022);
            aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0023b100);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x600c0438);
            aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x400c0438);
            aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);
			WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
            break;

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
       case 1260:
           aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c88800);
           aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0xca49b022);
           aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0023b100);
           aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
           aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x600c0434);
           aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x400c0434);
           aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);
		WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
           break;
       case 1080:
           aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c88000);
           aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0xca49b022);
           aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0023b100);
           aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
           aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x600c042d);
           aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x400c042d);
           aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);
		WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
           break;
       case 1008:
           aml_write_reg32(P_HHI_VID_PLL_CNTL2, 0x59c88000);
           aml_write_reg32(P_HHI_VID_PLL_CNTL3, 0xca49b022);
           aml_write_reg32(P_HHI_VID_PLL_CNTL4, 0x0023b100);
           aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00012385);
           aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x600c042a);
           aml_write_reg32(P_HHI_VID_PLL_CNTL,  0x400c042a);
           aml_write_reg32(P_HHI_VID_PLL_CNTL5, 0x00016385);
		WAIT_FOR_PLL_LOCKED(P_HHI_VID_PLL_CNTL);
           break;

        default:
            printk("error hpll clk: %d\n", clk);
            break;
    }
