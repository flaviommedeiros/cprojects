#ifdef INCLUDE_TCP_SEG_SUPPORT
if ((pDevice->TaskToOffload & LM_TASK_OFFLOAD_TCP_SEGMENTATION) &&
            ((pDevice->ChipRevId == T3_CHIP_ID_5705_A1) ||
            (pDevice->ChipRevId == T3_CHIP_ID_5705_A2)))
        {
            pDevice->DmaReadFifoSize = DMA_READ_MODE_FIFO_SIZE_128;
        }
        else
#endif
        {
            if (!(pDevice->PciState & T3_PCI_STATE_HIGH_BUS_SPEED) &&
                !(pDevice->Flags & BCM5788_FLAG) &&
                !(pDevice->Flags & PCI_EXPRESS_FLAG))
            {
                pDevice->DmaReadFifoSize = DMA_READ_MODE_FIFO_LONG_BURST;
                if (pDevice->ChipRevId == T3_CHIP_ID_5705_A1)
                {
                    pDevice->Flags |= RX_BD_LIMIT_64_FLAG;
                }
                pDevice->Flags |= DMA_WR_MODE_RX_ACCELERATE_FLAG;
            }
	    else if (pDevice->Flags & PCI_EXPRESS_FLAG)
            {
                pDevice->DmaReadFifoSize = DMA_READ_MODE_FIFO_LONG_BURST;
            }
        }
