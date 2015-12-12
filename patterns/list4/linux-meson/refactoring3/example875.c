switch (devpriv->ai_mode) {
	case INT_TYPE_AI1_DMA:
	case INT_TYPE_AI3_DMA:
		return interrupt_pcl818_ai_mode13_dma(irq, d);
	case INT_TYPE_AI1_INT:
	case INT_TYPE_AI3_INT:
		return interrupt_pcl818_ai_mode13_int(irq, d);
	case INT_TYPE_AI1_FIFO:
	case INT_TYPE_AI3_FIFO:
		return interrupt_pcl818_ai_mode13_fifo(irq, d);
#ifdef PCL818_MODE13_AO
	case INT_TYPE_AO1_INT:
	case INT_TYPE_AO3_INT:
		return interrupt_pcl818_ao_mode13_int(irq, d);
#endif
	default:
		break;
	}
