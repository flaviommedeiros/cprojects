#ifdef CONFIG_PCI
if (!strcmp(model, "ds1287") ||
	    !strcmp(model, "m5819") ||
	    !strcmp(model, "m5819p") ||
	    !strcmp(model, "m5823")) {
		ds1287_regs = (unsigned long) regs;
	} else if (!strcmp(model, "bq4802")) {
		bq4802_regs = regs;
	} else
#endif
	if (model[5] == '0' && model[6] == '2') {
		mstk48t02_regs = regs;
	} else if(model[5] == '0' && model[6] == '8') {
		mstk48t08_regs = regs;
		mstk48t02_regs = mstk48t08_regs + MOSTEK_48T08_48T02;
	} else {
		mstk48t59_regs = regs;
		mstk48t02_regs = mstk48t59_regs + MOSTEK_48T59_48T02;
	}
