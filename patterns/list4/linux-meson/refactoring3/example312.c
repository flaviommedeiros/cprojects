switch (cmd) {
        /*
         * Return current driver state.  Since we keep this up
         * To date internally, just copy this out to the user.
         */
    case LMCIOCGINFO: /*fold01*/
	if (copy_to_user(ifr->ifr_data, &sc->ictl, sizeof(lmc_ctl_t)))
		ret = -EFAULT;
	else
		ret = 0;
        break;

    case LMCIOCSINFO: /*fold01*/
        if (!capable(CAP_NET_ADMIN)) {
            ret = -EPERM;
            break;
        }

        if(dev->flags & IFF_UP){
            ret = -EBUSY;
            break;
        }

	if (copy_from_user(&ctl, ifr->ifr_data, sizeof(lmc_ctl_t))) {
		ret = -EFAULT;
		break;
	}

	spin_lock_irqsave(&sc->lmc_lock, flags);
        sc->lmc_media->set_status (sc, &ctl);

        if(ctl.crc_length != sc->ictl.crc_length) {
            sc->lmc_media->set_crc_length(sc, ctl.crc_length);
	    if (sc->ictl.crc_length == LMC_CTL_CRC_LENGTH_16)
		sc->TxDescriptControlInit |=  LMC_TDES_ADD_CRC_DISABLE;
	    else
		sc->TxDescriptControlInit &= ~LMC_TDES_ADD_CRC_DISABLE;
        }
	spin_unlock_irqrestore(&sc->lmc_lock, flags);

        ret = 0;
        break;

    case LMCIOCIFTYPE: /*fold01*/
        {
	    u16 old_type = sc->if_type;
	    u16	new_type;

	    if (!capable(CAP_NET_ADMIN)) {
		ret = -EPERM;
		break;
	    }

	    if (copy_from_user(&new_type, ifr->ifr_data, sizeof(u16))) {
		ret = -EFAULT;
		break;
	    }

            
	    if (new_type == old_type)
	    {
		ret = 0 ;
		break;				/* no change */
            }
            
	    spin_lock_irqsave(&sc->lmc_lock, flags);
            lmc_proto_close(sc);

            sc->if_type = new_type;
            lmc_proto_attach(sc);
	    ret = lmc_proto_open(sc);
	    spin_unlock_irqrestore(&sc->lmc_lock, flags);
	    break;
	}

    case LMCIOCGETXINFO: /*fold01*/
	spin_lock_irqsave(&sc->lmc_lock, flags);
        sc->lmc_xinfo.Magic0 = 0xBEEFCAFE;

        sc->lmc_xinfo.PciCardType = sc->lmc_cardtype;
        sc->lmc_xinfo.PciSlotNumber = 0;
        sc->lmc_xinfo.DriverMajorVersion = DRIVER_MAJOR_VERSION;
        sc->lmc_xinfo.DriverMinorVersion = DRIVER_MINOR_VERSION;
        sc->lmc_xinfo.DriverSubVersion = DRIVER_SUB_VERSION;
        sc->lmc_xinfo.XilinxRevisionNumber =
            lmc_mii_readreg (sc, 0, 3) & 0xf;
        sc->lmc_xinfo.MaxFrameSize = LMC_PKT_BUF_SZ;
        sc->lmc_xinfo.link_status = sc->lmc_media->get_link_status (sc);
        sc->lmc_xinfo.mii_reg16 = lmc_mii_readreg (sc, 0, 16);
	spin_unlock_irqrestore(&sc->lmc_lock, flags);

        sc->lmc_xinfo.Magic1 = 0xDEADBEEF;

        if (copy_to_user(ifr->ifr_data, &sc->lmc_xinfo,
			 sizeof(struct lmc_xinfo)))
		ret = -EFAULT;
	else
		ret = 0;

        break;

    case LMCIOCGETLMCSTATS:
	    spin_lock_irqsave(&sc->lmc_lock, flags);
	    if (sc->lmc_cardtype == LMC_CARDTYPE_T1) {
		    lmc_mii_writereg(sc, 0, 17, T1FRAMER_FERR_LSB);
		    sc->extra_stats.framingBitErrorCount +=
			    lmc_mii_readreg(sc, 0, 18) & 0xff;
		    lmc_mii_writereg(sc, 0, 17, T1FRAMER_FERR_MSB);
		    sc->extra_stats.framingBitErrorCount +=
			    (lmc_mii_readreg(sc, 0, 18) & 0xff) << 8;
		    lmc_mii_writereg(sc, 0, 17, T1FRAMER_LCV_LSB);
		    sc->extra_stats.lineCodeViolationCount +=
			    lmc_mii_readreg(sc, 0, 18) & 0xff;
		    lmc_mii_writereg(sc, 0, 17, T1FRAMER_LCV_MSB);
		    sc->extra_stats.lineCodeViolationCount +=
			    (lmc_mii_readreg(sc, 0, 18) & 0xff) << 8;
		    lmc_mii_writereg(sc, 0, 17, T1FRAMER_AERR);
		    regVal = lmc_mii_readreg(sc, 0, 18) & 0xff;

		    sc->extra_stats.lossOfFrameCount +=
			    (regVal & T1FRAMER_LOF_MASK) >> 4;
		    sc->extra_stats.changeOfFrameAlignmentCount +=
			    (regVal & T1FRAMER_COFA_MASK) >> 2;
		    sc->extra_stats.severelyErroredFrameCount +=
			    regVal & T1FRAMER_SEF_MASK;
	    }
	    spin_unlock_irqrestore(&sc->lmc_lock, flags);
	    if (copy_to_user(ifr->ifr_data, &sc->lmc_device->stats,
			     sizeof(sc->lmc_device->stats)) ||
		copy_to_user(ifr->ifr_data + sizeof(sc->lmc_device->stats),
			     &sc->extra_stats, sizeof(sc->extra_stats)))
		    ret = -EFAULT;
	    else
		    ret = 0;
	    break;

    case LMCIOCCLEARLMCSTATS:
	    if (!capable(CAP_NET_ADMIN)) {
		    ret = -EPERM;
		    break;
	    }

	    spin_lock_irqsave(&sc->lmc_lock, flags);
	    memset(&sc->lmc_device->stats, 0, sizeof(sc->lmc_device->stats));
	    memset(&sc->extra_stats, 0, sizeof(sc->extra_stats));
	    sc->extra_stats.check = STATCHECK;
	    sc->extra_stats.version_size = (DRIVER_VERSION << 16) +
		    sizeof(sc->lmc_device->stats) + sizeof(sc->extra_stats);
	    sc->extra_stats.lmc_cardtype = sc->lmc_cardtype;
	    spin_unlock_irqrestore(&sc->lmc_lock, flags);
	    ret = 0;
	    break;

    case LMCIOCSETCIRCUIT: /*fold01*/
        if (!capable(CAP_NET_ADMIN)){
            ret = -EPERM;
            break;
        }

        if(dev->flags & IFF_UP){
            ret = -EBUSY;
            break;
        }

	if (copy_from_user(&ctl, ifr->ifr_data, sizeof(lmc_ctl_t))) {
		ret = -EFAULT;
		break;
	}
	spin_lock_irqsave(&sc->lmc_lock, flags);
        sc->lmc_media->set_circuit_type(sc, ctl.circuit_type);
        sc->ictl.circuit_type = ctl.circuit_type;
	spin_unlock_irqrestore(&sc->lmc_lock, flags);
        ret = 0;

        break;

    case LMCIOCRESET: /*fold01*/
        if (!capable(CAP_NET_ADMIN)){
            ret = -EPERM;
            break;
        }

	spin_lock_irqsave(&sc->lmc_lock, flags);
        /* Reset driver and bring back to current state */
        printk (" REG16 before reset +%04x\n", lmc_mii_readreg (sc, 0, 16));
        lmc_running_reset (dev);
        printk (" REG16 after reset +%04x\n", lmc_mii_readreg (sc, 0, 16));

        LMC_EVENT_LOG(LMC_EVENT_FORCEDRESET, LMC_CSR_READ (sc, csr_status), lmc_mii_readreg (sc, 0, 16));
	spin_unlock_irqrestore(&sc->lmc_lock, flags);

        ret = 0;
        break;

#ifdef DEBUG
    case LMCIOCDUMPEVENTLOG:
	if (copy_to_user(ifr->ifr_data, &lmcEventLogIndex, sizeof(u32))) {
		ret = -EFAULT;
		break;
	}
	if (copy_to_user(ifr->ifr_data + sizeof(u32), lmcEventLogBuf,
			 sizeof(lmcEventLogBuf)))
		ret = -EFAULT;
	else
		ret = 0;

        break;
#endif /* end ifdef _DBG_EVENTLOG */
    case LMCIOCT1CONTROL: /*fold01*/
        if (sc->lmc_cardtype != LMC_CARDTYPE_T1){
            ret = -EOPNOTSUPP;
            break;
        }
        break;
    case LMCIOCXILINX: /*fold01*/
        {
            struct lmc_xilinx_control xc; /*fold02*/

            if (!capable(CAP_NET_ADMIN)){
                ret = -EPERM;
                break;
            }

            /*
             * Stop the xwitter whlie we restart the hardware
             */
            netif_stop_queue(dev);

	    if (copy_from_user(&xc, ifr->ifr_data, sizeof(struct lmc_xilinx_control))) {
		ret = -EFAULT;
		break;
	    }
            switch(xc.command){
            case lmc_xilinx_reset: /*fold02*/
                {
                    u16 mii;
		    spin_lock_irqsave(&sc->lmc_lock, flags);
                    mii = lmc_mii_readreg (sc, 0, 16);

                    /*
                     * Make all of them 0 and make input
                     */
                    lmc_gpio_mkinput(sc, 0xff);

                    /*
                     * make the reset output
                     */
                    lmc_gpio_mkoutput(sc, LMC_GEP_RESET);

                    /*
                     * RESET low to force configuration.  This also forces
                     * the transmitter clock to be internal, but we expect to reset
                     * that later anyway.
                     */

                    sc->lmc_gpio &= ~LMC_GEP_RESET;
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);


                    /*
                     * hold for more than 10 microseconds
                     */
                    udelay(50);

                    sc->lmc_gpio |= LMC_GEP_RESET;
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);


                    /*
                     * stop driving Xilinx-related signals
                     */
                    lmc_gpio_mkinput(sc, 0xff);

                    /* Reset the frammer hardware */
                    sc->lmc_media->set_link_status (sc, 1);
                    sc->lmc_media->set_status (sc, NULL);
//                    lmc_softreset(sc);

                    {
                        int i;
                        for(i = 0; i < 5; i++){
                            lmc_led_on(sc, LMC_DS3_LED0);
                            mdelay(100);
                            lmc_led_off(sc, LMC_DS3_LED0);
                            lmc_led_on(sc, LMC_DS3_LED1);
                            mdelay(100);
                            lmc_led_off(sc, LMC_DS3_LED1);
                            lmc_led_on(sc, LMC_DS3_LED3);
                            mdelay(100);
                            lmc_led_off(sc, LMC_DS3_LED3);
                            lmc_led_on(sc, LMC_DS3_LED2);
                            mdelay(100);
                            lmc_led_off(sc, LMC_DS3_LED2);
                        }
                    }
		    spin_unlock_irqrestore(&sc->lmc_lock, flags);
                    
                    

                    ret = 0x0;

                }

                break;
            case lmc_xilinx_load_prom: /*fold02*/
                {
                    u16 mii;
                    int timeout = 500000;
		    spin_lock_irqsave(&sc->lmc_lock, flags);
                    mii = lmc_mii_readreg (sc, 0, 16);

                    /*
                     * Make all of them 0 and make input
                     */
                    lmc_gpio_mkinput(sc, 0xff);

                    /*
                     * make the reset output
                     */
                    lmc_gpio_mkoutput(sc,  LMC_GEP_DP | LMC_GEP_RESET);

                    /*
                     * RESET low to force configuration.  This also forces
                     * the transmitter clock to be internal, but we expect to reset
                     * that later anyway.
                     */

                    sc->lmc_gpio &= ~(LMC_GEP_RESET | LMC_GEP_DP);
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);


                    /*
                     * hold for more than 10 microseconds
                     */
                    udelay(50);

                    sc->lmc_gpio |= LMC_GEP_DP | LMC_GEP_RESET;
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);

                    /*
                     * busy wait for the chip to reset
                     */
                    while( (LMC_CSR_READ(sc, csr_gp) & LMC_GEP_INIT) == 0 &&
                           (timeout-- > 0))
                        cpu_relax();


                    /*
                     * stop driving Xilinx-related signals
                     */
                    lmc_gpio_mkinput(sc, 0xff);
		    spin_unlock_irqrestore(&sc->lmc_lock, flags);

                    ret = 0x0;
                    

                    break;

                }

            case lmc_xilinx_load: /*fold02*/
                {
                    char *data;
                    int pos;
                    int timeout = 500000;

                    if (!xc.data) {
                            ret = -EINVAL;
                            break;
                    }

                    data = kmalloc(xc.len, GFP_KERNEL);
                    if (!data) {
                            ret = -ENOMEM;
                            break;
                    }
                    
                    if(copy_from_user(data, xc.data, xc.len))
                    {
                    	kfree(data);
                    	ret = -ENOMEM;
                    	break;
                    }

                    printk("%s: Starting load of data Len: %d at 0x%p == 0x%p\n", dev->name, xc.len, xc.data, data);

		    spin_lock_irqsave(&sc->lmc_lock, flags);
                    lmc_gpio_mkinput(sc, 0xff);

                    /*
                     * Clear the Xilinx and start prgramming from the DEC
                     */

                    /*
                     * Set ouput as:
                     * Reset: 0 (active)
                     * DP:    0 (active)
                     * Mode:  1
                     *
                     */
                    sc->lmc_gpio = 0x00;
                    sc->lmc_gpio &= ~LMC_GEP_DP;
                    sc->lmc_gpio &= ~LMC_GEP_RESET;
                    sc->lmc_gpio |=  LMC_GEP_MODE;
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);

                    lmc_gpio_mkoutput(sc, LMC_GEP_MODE | LMC_GEP_DP | LMC_GEP_RESET);

                    /*
                     * Wait at least 10 us 20 to be safe
                     */
                    udelay(50);

                    /*
                     * Clear reset and activate programming lines
                     * Reset: Input
                     * DP:    Input
                     * Clock: Output
                     * Data:  Output
                     * Mode:  Output
                     */
                    lmc_gpio_mkinput(sc, LMC_GEP_DP | LMC_GEP_RESET);

                    /*
                     * Set LOAD, DATA, Clock to 1
                     */
                    sc->lmc_gpio = 0x00;
                    sc->lmc_gpio |= LMC_GEP_MODE;
                    sc->lmc_gpio |= LMC_GEP_DATA;
                    sc->lmc_gpio |= LMC_GEP_CLK;
                    LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);
                    
                    lmc_gpio_mkoutput(sc, LMC_GEP_DATA | LMC_GEP_CLK | LMC_GEP_MODE );

                    /*
                     * busy wait for the chip to reset
                     */
                    while( (LMC_CSR_READ(sc, csr_gp) & LMC_GEP_INIT) == 0 &&
                           (timeout-- > 0))
                        cpu_relax();

                    printk(KERN_DEBUG "%s: Waited %d for the Xilinx to clear it's memory\n", dev->name, 500000-timeout);

                    for(pos = 0; pos < xc.len; pos++){
                        switch(data[pos]){
                        case 0:
                            sc->lmc_gpio &= ~LMC_GEP_DATA; /* Data is 0 */
                            break;
                        case 1:
                            sc->lmc_gpio |= LMC_GEP_DATA; /* Data is 1 */
                            break;
                        default:
                            printk(KERN_WARNING "%s Bad data in xilinx programming data at %d, got %d wanted 0 or 1\n", dev->name, pos, data[pos]);
                            sc->lmc_gpio |= LMC_GEP_DATA; /* Assume it's 1 */
                        }
                        sc->lmc_gpio &= ~LMC_GEP_CLK; /* Clock to zero */
                        sc->lmc_gpio |= LMC_GEP_MODE;
                        LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);
                        udelay(1);
                        
                        sc->lmc_gpio |= LMC_GEP_CLK; /* Put the clack back to one */
                        sc->lmc_gpio |= LMC_GEP_MODE;
                        LMC_CSR_WRITE(sc, csr_gp, sc->lmc_gpio);
                        udelay(1);
                    }
                    if((LMC_CSR_READ(sc, csr_gp) & LMC_GEP_INIT) == 0){
                        printk(KERN_WARNING "%s: Reprogramming FAILED. Needs to be reprogrammed. (corrupted data)\n", dev->name);
                    }
                    else if((LMC_CSR_READ(sc, csr_gp) & LMC_GEP_DP) == 0){
                        printk(KERN_WARNING "%s: Reprogramming FAILED. Needs to be reprogrammed. (done)\n", dev->name);
                    }
                    else {
                        printk(KERN_DEBUG "%s: Done reprogramming Xilinx, %d bits, good luck!\n", dev->name, pos);
                    }

                    lmc_gpio_mkinput(sc, 0xff);
                    
                    sc->lmc_miireg16 |= LMC_MII16_FIFO_RESET;
                    lmc_mii_writereg(sc, 0, 16, sc->lmc_miireg16);

                    sc->lmc_miireg16 &= ~LMC_MII16_FIFO_RESET;
                    lmc_mii_writereg(sc, 0, 16, sc->lmc_miireg16);
		    spin_unlock_irqrestore(&sc->lmc_lock, flags);

                    kfree(data);
                    
                    ret = 0;
                    
                    break;
                }
            default: /*fold02*/
                ret = -EBADE;
                break;
            }

            netif_wake_queue(dev);
            sc->lmc_txfull = 0;

        }
        break;
    default: /*fold01*/
        /* If we don't know what to do, give the protocol a shot. */
        ret = lmc_proto_ioctl (sc, ifr, cmd);
        break;
    }
