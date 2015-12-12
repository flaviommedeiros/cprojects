switch (devpriv->int816_mode) {
#ifdef unused
		case INT_TYPE_AI1_DMA_RTC:
		case INT_TYPE_AI3_DMA_RTC:
			set_rtc_irq_bit(0);	/*  stop RTC */
			del_timer(&devpriv->rtc_irq_timer);
#endif
		case INT_TYPE_AI1_DMA:
		case INT_TYPE_AI3_DMA:
			disable_dma(devpriv->dma);
		case INT_TYPE_AI1_INT:
		case INT_TYPE_AI3_INT:
			outb(inb(dev->iobase + PCL816_CONTROL) & 0x73,
			     dev->iobase + PCL816_CONTROL);	/* Stop A/D */
			udelay(1);
			outb(0, dev->iobase + PCL816_CONTROL);	/* Stop A/D */

			/* Stop pacer */
			outb(0xb0, dev->iobase + PCL816_CTRCTL);
			outb(0x70, dev->iobase + PCL816_CTRCTL);
			outb(0, dev->iobase + PCL816_AD_LO);
			inb(dev->iobase + PCL816_AD_LO);
			inb(dev->iobase + PCL816_AD_HI);

			/* clear INT request */
			outb(0, dev->iobase + PCL816_CLRINT);

			/* Stop A/D */
			outb(0, dev->iobase + PCL816_CONTROL);
			devpriv->irq_blocked = 0;
			devpriv->irq_was_now_closed = devpriv->int816_mode;
			devpriv->int816_mode = 0;
			devpriv->last_int_sub = s;
/* s->busy = 0; */
			break;
		}
