switch (buf[0]) {
		case 'b':	//write basic config
			t[0] = 1024;
			t[1] = 768;
			t[2] = 1344;
			t[3] = 806;
			ret = sscanf(buf, "basic %d %d %d %d", &t[0], &t[1], &t[2], &t[3]);
			pDev->pConf->lcd_basic.h_active = t[0];
			pDev->pConf->lcd_basic.v_active = t[1];
			pDev->pConf->lcd_basic.h_period = t[2];
			pDev->pConf->lcd_basic.v_period = t[3];
			printk("h_active=%d, v_active=%d, h_period=%d, v_period=%d\n", t[0], t[1], t[2], t[3]);
			break;
		case 't':
			if (buf[1] == 'y') {//type
				t[0] = 1;
				t[1] = 6;
				ret = sscanf(buf, "type %d %d", &t[0], &t[1]);
				pDev->pConf->lcd_basic.lcd_type = t[0];
				pDev->pConf->lcd_basic.lcd_bits = t[1];
				printk("lcd_type: %s, lcd_bits: %d\n", lcd_type_table[t[0]], t[1]);
			}
			else if (buf[1] == 'e') {//test
				t[0] = 0;
				ret = sscanf(buf, "test %d", &t[0]);
				if (pDev->pConf->lcd_misc_ctrl.lcd_status == 0)
					printk("lcd is already OFF, can't display test pattern\n");
				else
					pDev->pConf->lcd_misc_ctrl.lcd_test(t[0]);
			}
			else if (buf[1] == 't') {//ttl
				t[0] = 0;
				t[1] = 0;
				ret = sscanf(buf, "ttl %d %d", &t[0], &t[1]);
				pDev->pConf->lcd_control.ttl_config->rb_swap = t[0];
				pDev->pConf->lcd_control.ttl_config->bit_swap = t[1];
				printk("ttl rb_swap: %s, bit_swap: %s\n", ((t[0] == 0) ? "disable" : "enable"), ((t[1] == 0) ? "disable" : "enable"));
			}
			break;
		case 'c':
			t[0] = 40000000;
			t[1] = 0;
			t[2] = 0;
			ret = sscanf(buf, "clock %d %d %d", &t[0], &t[1], &t[2]);
			pDev->pConf->lcd_timing.lcd_clk = t[0];
			pDev->pConf->lcd_timing.clk_ctrl = ((pDev->pConf->lcd_timing.clk_ctrl & ~((1 << CLK_CTRL_AUTO) | (0xf << CLK_CTRL_SS))) | ((1 << CLK_CTRL_AUTO) | (t[1] << CLK_CTRL_SS)));
			pDev->pConf->lcd_timing.pol_ctrl = ((pDev->pConf->lcd_timing.pol_ctrl & ~(1 << POL_CTRL_CLK)) | (t[2] << POL_CTRL_CLK));
			printk("lcd_clk=%dHz, ss_level=%d, clk_pol=%s\n", t[0], t[1], ((t[2] == 0) ? "negative" : "positive"));
			break;
		case 's'://sync
			t[0] = 10;
			t[1] = 60;
			t[2] = 0;
			t[3] = 3;
			t[4] = 20;
			t[5] = 0;
			ret = sscanf(buf, "sync %d %d %d %d %d %d", &t[0], &t[1], &t[2], &t[3], &t[4], &t[5]);
			pDev->pConf->lcd_timing.hsync_width = t[0];
			pDev->pConf->lcd_timing.hsync_bp = t[1];
			pDev->pConf->lcd_timing.vsync_width = t[3];
			pDev->pConf->lcd_timing.vsync_bp = t[4];
			pDev->pConf->lcd_timing.pol_ctrl = ((pDev->pConf->lcd_timing.pol_ctrl & ~((1 << POL_CTRL_HS) | (1 << POL_CTRL_VS))) | ((t[2] << POL_CTRL_HS) | (t[5] << POL_CTRL_VS)));
			printk("hs_width=%d, hs_bp=%d, hs_pol=%s, vs_width=%d, vs_bp=%d, vs_pol=%s\n", t[0], t[1], ((t[2] == 0) ? "negative" : "positive"), t[3], t[4], ((t[5] == 0) ? "negative" : "positive"));
			break;
		case 'v':
			if (buf[2] == 'l') { //valid
				t[0] = 0;
				t[1] = 0;
				t[2] = 1;
				ret = sscanf(buf, "valid %d %d", &t[0], &t[1]);
				pDev->pConf->lcd_timing.hvsync_valid = t[0];
				pDev->pConf->lcd_timing.de_valid = t[1];
				printk("hvsync: %s, de: %s\n", ((t[0] == 0) ? "disable" : "enable"), ((t[1] == 0) ? "disable" : "enable"));
			}
			else if (buf[2] == 'd') { //vadj
				t[0] = 0x0;
				t[1] = 0x80;
				t[2] = 0x100;
				ret = sscanf(buf, "vadj %d %d %d", &t[0], &t[1], &t[2]);
				pDev->pConf->lcd_effect.vadj_brightness = t[0];
				pDev->pConf->lcd_effect.vadj_contrast = t[1];
				pDev->pConf->lcd_effect.vadj_saturation = t[2];
				printk("video adjust: brightness=0x%x, contrast=0x%x, stauration=0x%x\n", t[0], t[1], t[2]);
			}
			break;
		case 'o':
			t[0] = 1;
			t[1] = 0;
			t[2] = 1;
			t[3] = 0;
			ret = sscanf(buf, "offset %d %d %d %d", &t[0], &t[1], &t[2], &t[3]);
			pDev->pConf->lcd_timing.h_offset = ((t[0] << 31) | ((t[1] & 0xffff) << 0));
			pDev->pConf->lcd_timing.v_offset = ((t[2] << 31) | ((t[3] & 0xffff) << 0));
			printk("h_offset = %s%u, v_offset = %s%u\n", (t[0] ? "+" : "-"), (t[1] & 0xffff), (t[2] ? "+" : "-"), (t[3] & 0xffff));
			break;
		case 'l':	//write lvds config		//lvds_repack, pn_swap
			t[0] = 1;
			t[1] = 1;
			t[2] = 0;
			ret = sscanf(buf, "lvds %d %d %d", &t[0], &t[1], &t[2]);
			pDev->pConf->lcd_control.lvds_config->lvds_vswing = t[0];
			pDev->pConf->lcd_control.lvds_config->lvds_repack = t[1];
			pDev->pConf->lcd_control.lvds_config->pn_swap = t[2];
			printk("vswing_level: %u, lvds_repack: %s, rb_swap: %s\n", t[0], ((t[1] == 1) ? "VESA mode" : "JEIDA mode"), ((t[2] == 0) ? "disable" : "enable"));
			break;
#ifdef CONFIG_LCD_IF_MIPI_VALID
		case 'm':	//write mipi config
			if (buf[1] == 'd') {
				t[0] = 0;
				t[1] = 4;
				t[2] = 0;
				ret = sscanf(buf, "mdsi %d %d %d", &t[0],&t[1],&t[2]);
				pDev->pConf->lcd_control.mipi_config->lane_num = (unsigned char)(t[0]);
				pDev->pConf->lcd_control.mipi_config->bit_rate_max = t[1]*1000;
				pDev->pConf->lcd_control.mipi_config->factor_numerator = t[2];
				pDev->pConf->lcd_control.mipi_config->factor_denominator=10;
				printk("dsi lane_num = %d, bit_rate max=%dMHz, factor=%d\n",t[0], t[1], pDev->pConf->lcd_control.mipi_config->factor_numerator);
			}
			else if (buf[1] == 'c') {
				t[0] = 1;
				t[1] = 0;
				t[2] = 0;
				t[3] = 0;
				ret = sscanf(buf, "mctl %d %d %d %d", &t[0],&t[1],&t[2],&t[3]);
				pDev->pConf->lcd_control.mipi_config->operation_mode = ((t[0] << BIT_OPERATION_MODE_INIT) | (t[1] << BIT_OPERATION_MODE_DISP));
				pDev->pConf->lcd_control.mipi_config->transfer_ctrl = ((t[2] << BIT_TRANS_CTRL_CLK) | (t[3] << BIT_TRANS_CTRL_SWITCH));
				printk("dsi operation mode init=%s(%d), display=%s(%d), lp_clk_auto_stop=%d, transfer_switch=%d\n",(t[0]? "command" : "video"), t[0], (t[1] ? "command" : "video"), t[1], t[2], t[3]);
			}
			break;
#endif
		case 'd':
			if (buf[2] == 't') {
				t[0] = 0;
				t[1] = 0x600;
				ret = sscanf(buf, "dither %d %x", &t[0], &t[1]);
				pDev->pConf->lcd_effect.dith_user = t[0];
				pDev->pConf->lcd_effect.dith_cntl_addr = t[1];
				printk("dither user_ctrl: %s, 0x%x\n", ((t[0] == 0) ? "disable" : "enable"), t[1]);
			}
			else {
				printk("power off lcd.\n");
				_disable_backlight();
				pDev->pConf->lcd_power_ctrl.power_ctrl(OFF);
			}
			break;
		case 'w':	//update display config
			if (pDev->pConf->lcd_basic.lcd_type == LCD_DIGITAL_MINILVDS) {
				printk("Don't support miniLVDS yet. Will reset to original lcd config.\n");
				reset_lcd_config(pDev->pConf);
			}
			else {
				_lcd_module_disable();
				mdelay(200);
				lcd_config_init(pDev->pConf);
				_init_vout();
				_lcd_module_enable();
			}
			break;
		case 'r':	
			if (buf[2] == 'a') { //read lcd config
				read_current_lcd_config(pDev->pConf);
			}
			else if (buf[2] == 's') { //reset lcd config
				reset_lcd_config(pDev->pConf);
			}
			break;
		case 'e':
			if (buf[1] == 'n') {
				printk("power on lcd.\n");
				_lcd_module_disable();
				mdelay(200);
				_lcd_module_enable();
				_enable_backlight();
			}
#ifdef CONFIG_LCD_IF_EDP_VALID
			else if (buf[1] == 'd') {
				t[0] = 1;
				t[1] = 4;
				t[2] = 0;
				ret = sscanf(buf, "edp %u %u %u", &t[0], &t[1], &t[2]);
				pDev->pConf->lcd_control.edp_config->link_rate = ((t[0] == 0) ? 0 : 1);
				switch (t[1]) {
					case 1:
					case 2:
						pDev->pConf->lcd_control.edp_config->lane_count = t[1];
						break;
					default:
						pDev->pConf->lcd_control.edp_config->lane_count = 4;
						break;
				}
				pDev->pConf->lcd_control.edp_config->vswing = t[2];
				printk("set edp link_rate = %s, lane_count = %u, vswing_level = %u\n", ((pDev->pConf->lcd_control.edp_config->link_rate == 0) ? "1.62G":"2.7G"), pDev->pConf->lcd_control.edp_config->lane_count, pDev->pConf->lcd_control.edp_config->vswing);
			}
			else if (buf[1] == 'c') {
				t[0] = 0;
				t[1] = 1;
				ret = sscanf(buf, "ectl %u %u", &t[0], &t[1]);
				pDev->pConf->lcd_control.edp_config->edid_timing_used = ((t[0] == 0) ? 0 : 1);
				pDev->pConf->lcd_control.edp_config->sync_clock_mode = ((t[1] == 0) ? 0 : 1);
				printk("set edp edid_timing_used = %u, sync_clock_mode = %u\n", pDev->pConf->lcd_control.edp_config->edid_timing_used, pDev->pConf->lcd_control.edp_config->sync_clock_mode);
				pDev->pConf->lcd_misc_ctrl.edp_edid_load();
			}
#endif
			else {
				printk("wrong format of lcd debug command.\n");
			}
			break;
		default:
			printk("wrong format of lcd debug command.\n");
	}
