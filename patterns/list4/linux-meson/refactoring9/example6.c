int hcd_init(
#ifdef LM_INTERFACE
		    struct lm_device *_dev
#elif  defined(PCI_INTERFACE)
		    struct pci_dev *_dev
#endif
    )
{
	struct usb_hcd *hcd = NULL;
	dwc_otg_hcd_t *dwc_otg_hcd = NULL;
#ifdef LM_INTERFACE
	dwc_otg_device_t *otg_dev = lm_get_drvdata(_dev);
#elif  defined(PCI_INTERFACE)
	dwc_otg_device_t *otg_dev = pci_get_drvdata(_dev);
#endif
	int retval = 0;
	int irqno;
	struct pt_regs regs;
	unsigned long flags = IRQF_SHARED | IRQF_DISABLED;
	int cpu;

	DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD INIT\n");
	
#if 0 /* move to dwc_otg_driver_probe*/
	/* Set device flags indicating whether the HCD supports DMA. */
	if (dwc_otg_is_dma_enable(otg_dev->core_if)) {
#ifdef LM_INTERFACE
		_dev->dev.dma_mask = (void *)~0;
		_dev->dev.coherent_dma_mask = ~0;
#elif  defined(PCI_INTERFACE)
		pci_set_dma_mask(_dev, DMA_32BIT_MASK);
		pci_set_consistent_dma_mask(_dev, DMA_32BIT_MASK);
#endif

	} else {
#ifdef LM_INTERFACE
		_dev->dev.dma_mask = (void *)0;
		_dev->dev.coherent_dma_mask = 0;
#elif  defined(PCI_INTERFACE)
		pci_set_dma_mask(_dev, 0);
		pci_set_consistent_dma_mask(_dev, 0);
#endif
	}
#endif
	/*
	 * Allocate memory for the base HCD plus the DWC OTG HCD.
	 * Initialize the base HCD.
	 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,30)
	hcd = usb_create_hcd(&dwc_otg_hc_driver, &_dev->dev, _dev->dev.bus_id);
#else
	hcd = usb_create_hcd(&dwc_otg_hc_driver, &_dev->dev, dev_name(&_dev->dev));
	hcd->has_tt = 1;
//      hcd->uses_new_polling = 1;
//      hcd->poll_rh = 0;
#endif
	if (!hcd) {
		retval = -ENOMEM;
		goto error1;
	}

	hcd->regs = otg_dev->os_dep.base;

	/* Initialize the DWC OTG HCD. */
	dwc_otg_hcd = dwc_otg_hcd_alloc_hcd();
	if (!dwc_otg_hcd) {
		goto error2;
	}
	((struct wrapper_priv_data *)(hcd->hcd_priv))->dwc_otg_hcd =
	    dwc_otg_hcd;
	otg_dev->hcd = dwc_otg_hcd;

	if (dwc_otg_hcd_init(dwc_otg_hcd, otg_dev->core_if)) {
		goto error2;
	}

	if (fiq_enable && dwc_otg_hcd->core_if->use_fiq_flag)
	{
		if (claim_fiq(&fh)) {
			DWC_ERROR("Can't claim FIQ");
			goto error2;
		}

		DWC_WARN("FIQ at 0x%08x", (fiq_fsm_enable ? (int)&dwc_otg_fiq_fsm : (int)&dwc_otg_fiq_nop));
		DWC_WARN("FIQ ASM at 0x%08x length %d", (int)&_dwc_otg_fiq_stub, (int)(&_dwc_otg_fiq_stub_end - &_dwc_otg_fiq_stub));

		memset(&regs,0,sizeof(regs));

		regs.ARM_r8 = (long) dwc_otg_hcd->fiq_state;
		if (fiq_fsm_enable) {
			regs.ARM_r9 = dwc_otg_hcd->core_if->core_params->host_channels;
			//regs.ARM_r10 = dwc_otg_hcd->dma;
			regs.ARM_fp = (long) dwc_otg_fiq_fsm;
			DWC_WARN("FIQ r8=0x%08x r9=0x%08x", (unsigned int)regs.ARM_r8,(unsigned int)regs.ARM_r9);
		} else {
			regs.ARM_fp = (long) dwc_otg_fiq_nop;
		}

		mutex_lock(&fiq_lock);

		for_each_possible_cpu(cpu) {
			void *stack;
			stack = (void *) __get_free_pages(GFP_KERNEL, THREAD_SIZE_ORDER);
			if (WARN_ON(!stack)) {
				retval = -ENOMEM;
				mutex_unlock(&fiq_lock);
				goto error3;
			}
			per_cpu(fiq_stack_cpu, cpu) = stack;
		}

		on_each_cpu(fiq_setup_helper, &regs, true);
		set_fiq_handler((void *) &_dwc_otg_fiq_stub, &_dwc_otg_fiq_stub_end - &_dwc_otg_fiq_stub);

		mutex_unlock(&fiq_lock);

//		__show_regs(&regs);

		//Set the mphi periph to  the required registers
		//dwc_otg_hcd->fiq_state->mphi_regs.base    = otg_dev->os_dep.mphi_base;
		//dwc_otg_hcd->fiq_state->mphi_regs.ctrl    = otg_dev->os_dep.mphi_base + 0x4c;
		//dwc_otg_hcd->fiq_state->mphi_regs.outdda  = otg_dev->os_dep.mphi_base + 0x28;
		//dwc_otg_hcd->fiq_state->mphi_regs.outddb  = otg_dev->os_dep.mphi_base + 0x2c;
		//dwc_otg_hcd->fiq_state->mphi_regs.intstat = otg_dev->os_dep.mphi_base + 0x50;
		dwc_otg_hcd->fiq_state->dwc_regs_base = otg_dev->os_dep.base;
		//DWC_WARN("MPHI regs_base at 0x%08x", (int)dwc_otg_hcd->fiq_state->mphi_regs.base);
		//Enable mphi peripheral
		//writel((1<<31),dwc_otg_hcd->fiq_state->mphi_regs.ctrl);
#ifdef DEBUG
		//if (readl(dwc_otg_hcd->fiq_state->mphi_regs.ctrl) & 0x80000000)
		//	DWC_WARN("MPHI periph has been enabled");
		//else
		//	DWC_WARN("MPHI periph has NOT been enabled");
#endif
		//clear Timer D register
		aml_clr_reg32_mask(P_ISA_TIMER_MUX, ((3<<6)|(1<<15)|(1<<19)));
		aml_set_reg32_mask(P_ISA_TIMER_MUX,	((0<<6) | (0<<15) | (1<<19)));
		printk("enable fiq %d\n",_dev->irq);
		set_fiq_init(_dev->irq,(long)dwc_otg_hcd);

		if (irq_set_affinity(_dev->irq, cpumask_of(3))) {
			pr_warning("unable to set irq affinity (irq=%d, cpu=%u)\n",
					 _dev->irq, 3);
		}

		local_fiq_enable();		

	}


	otg_dev->hcd->otg_dev = otg_dev;
	hcd->self.otg_port = dwc_otg_hcd_otg_port(dwc_otg_hcd);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,33) //don't support for LM(with 2.6.20.1 kernel)
//	hcd->self.otg_version = dwc_otg_get_otg_version(otg_dev->core_if);
	/* Don't support SG list at this point */
	hcd->self.sg_tablesize = 0;
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
	/* Do not to do HNP polling if not capable */
//	if (otg_dev->core_if->otg_ver)
//		hcd->self.is_hnp_cap = dwc_otg_get_hnpcapable(otg_dev->core_if);
#endif
	if (fiq_enable && dwc_otg_hcd->core_if->use_fiq_flag) {
		irqno = MESON_USB_FIQ_BRIDGE;
	} else {
		irqno = _dev->irq;
		flags |= IRQ_TYPE_LEVEL_HIGH;
	}
	/*
	 * Finish generic HCD initialization and start the HCD. This function
	 * allocates the DMA buffer pool, registers the USB bus, requests the
	 * IRQ line, and calls hcd_start method.
	 */
	retval = usb_add_hcd(hcd, irqno, flags);
	if (retval < 0) {
		goto error3;
	}

	dwc_otg_hcd_set_priv_data(dwc_otg_hcd, hcd);
	return 0;

error3:
	mutex_lock(&fiq_lock);
	for_each_possible_cpu(cpu) {
		__free_pages(per_cpu(fiq_stack_cpu, cpu), THREAD_SIZE_ORDER);
		per_cpu(fiq_stack_cpu, cpu) = NULL;
	}
	mutex_unlock(&fiq_lock);
error2:
	usb_put_hcd(hcd);
error1:
	return retval;
}
