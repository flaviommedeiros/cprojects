switch (hw->mode) {
		case IMG_IR_M_NORMAL:
			img_ir_write_timings(priv, &hw->reg_timings.timings,
					     RC_FILTER_NORMAL);
			break;
		case IMG_IR_M_REPEATING:
			img_ir_write_timings(priv, &hw->reg_timings.rtimings,
					     RC_FILTER_NORMAL);
			break;
#ifdef CONFIG_PM_SLEEP
		case IMG_IR_M_WAKE:
			img_ir_write_timings(priv, &hw->reg_timings.timings,
					     RC_FILTER_WAKEUP);
			break;
#endif
		}
