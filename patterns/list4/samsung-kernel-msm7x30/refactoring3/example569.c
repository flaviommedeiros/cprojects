switch (lcd->bl) {
#ifdef MAPPING_TBL_AUTO_BRIGHTNESS
			case GAMMA_20CD ... GAMMA_100CD: /* 20cd ~ 100cd */
				setting_table_write(SEQ_ELVSS_set[0]);
				break;
			case GAMMA_110CD ... GAMMA_160CD: /* 110cd ~ 160cd */
				setting_table_write(SEQ_ELVSS_set[1]);
				break;
			case GAMMA_170CD ... GAMMA_200CD: /* 170cd ~ 200cd */
				setting_table_write(SEQ_ELVSS_set[2]);
				break;
			case GAMMA_210CD ... GAMMA_300CD: /* 210cd ~ 300cd */
				setting_table_write(SEQ_ELVSS_set[3]);
				break;
			default:
				break;
#else
			case 0 ... 7: /* 20cd ~ 100cd */
				setting_table_write(SEQ_ELVSS_set[0]);
				break;
			case 8 ... 13: /* 110cd ~ 160cd */
				setting_table_write(SEQ_ELVSS_set[1]);
				break;
			case 14 ... 17: /* 170cd ~ 200cd */
				setting_table_write(SEQ_ELVSS_set[2]);
				break;
			case 18 ... 27: /* 210cd ~ 300cd */
				setting_table_write(SEQ_ELVSS_set[3]);
				break;
			default:
				break;
#endif
		}
