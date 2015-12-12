#if 1
if (pVBInfo->IF_DEF_LVDS) { /* For XG21 LVDS */
		xgifb_reg_or(pVBInfo->P3d4, 0x32, LCDSense);
		/* LVDS on chip */
		xgifb_reg_and_or(pVBInfo->P3d4, 0x38, ~0xE0, 0xC0);
	} else {
#endif
		/* Enable GPIOA/B read  */
		xgifb_reg_and_or(pVBInfo->P3d4, 0x4A, ~0x03, 0x03);
		Temp = xgifb_reg_get(pVBInfo->P3d4, 0x48) & 0xC0;
		if (Temp == 0xC0) { /* DVI & DVO GPIOA/B pull high */
			XGINew_SenseLCD(HwDeviceExtension, pVBInfo);
			xgifb_reg_or(pVBInfo->P3d4, 0x32, LCDSense);
			/* Enable read GPIOF */
			xgifb_reg_and_or(pVBInfo->P3d4, 0x4A, ~0x20, 0x20);
			Temp = xgifb_reg_get(pVBInfo->P3d4, 0x48) & 0x04;
			if (!Temp)
				xgifb_reg_and_or(pVBInfo->P3d4,
						 0x38,
						 ~0xE0,
						 0x80); /* TMDS on chip */
			else
				xgifb_reg_and_or(pVBInfo->P3d4,
						 0x38,
						 ~0xE0,
						 0xA0); /* Only DVO on chip */
			/* Disable read GPIOF */
			xgifb_reg_and(pVBInfo->P3d4, 0x4A, ~0x20);
		}
#if 1
	}
