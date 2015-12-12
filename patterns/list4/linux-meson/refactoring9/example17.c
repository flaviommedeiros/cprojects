static int dwc_otg_driver_probe(
#ifdef LM_INTERFACE
				       struct lm_device *_dev
#elif defined(PCI_INTERFACE)
				       struct pci_dev *_dev,
				       const struct pci_device_id *id
#endif
    )
{
	int retval = 0;
	int port_index = 0;
	int port_type = USB_PORT_TYPE_OTG;
	int id_mode = USB_PHY_ID_MODE_HW;
	int port_speed = USB_PORT_SPEED_DEFAULT;
	int port_config = 0;
	int dma_config = USB_DMA_BURST_DEFAULT;
	int gpio_work_mask =1;
	int gpio_vbus_power_pin = -1;
	unsigned int phy_reg_addr = 0;
	unsigned int ctrl_reg_addr = 0;
	const char *s_clock_name = NULL;
	const char *gpio_name = NULL;
	const void *prop;
	struct clk * clock;
	dwc_otg_device_t *dwc_otg_device;
	struct dwc_otg_driver_module_params *pcore_para;

	dev_dbg(&_dev->dev, "dwc_otg_driver_probe(%p)\n", _dev);

#ifdef LM_INTERFACE
//	dev_dbg(&_dev->dev, "start=0x%08x\n", (unsigned)_dev->resource.start);
#elif defined(PCI_INTERFACE)
	if (!id) {
		DWC_ERROR("Invalid pci_device_id %p", id);
		return -EINVAL;
	}

	if (!_dev || (pci_enable_device(_dev) < 0)) {
		DWC_ERROR("Invalid pci_device %p", _dev);
		return -ENODEV;
	}
	dev_dbg(&_dev->dev, "start=0x%08x\n", (unsigned)pci_resource_start(_dev,0));
	/* other stuff needed as well? */

#endif

#ifdef LM_INTERFACE
	if (_dev->dev.of_node) {
		const struct of_device_id *match;
		struct device_node	*of_node = _dev->dev.of_node;
		match = of_lm_match_node(dwc_otg_dt_match, of_node);
		if(match){
			s_clock_name = of_get_property(of_node, "clock-src", NULL);
			prop = of_get_property(of_node, "port-id", NULL);
			if(prop)
				port_index = of_read_ulong(prop,1);
			prop = of_get_property(of_node, "port-type", NULL);
			if(prop)
				port_type = of_read_ulong(prop,1);
			prop = of_get_property(of_node, "port-speed", NULL);
			if(prop)
				port_speed = of_read_ulong(prop,1);
			prop = of_get_property(of_node, "port-config", NULL);
			if(prop)
				port_config = of_read_ulong(prop,1);
			prop = of_get_property(of_node, "port-dma", NULL);
			if(prop)
				dma_config = of_read_ulong(prop,1);
			prop = of_get_property(of_node, "port-id-mode", NULL);
			if(prop)
				id_mode = of_read_ulong(prop,1);

			gpio_name = of_get_property(of_node, "gpio-vbus-power", NULL);
			if(gpio_name)
			{
				gpio_vbus_power_pin= amlogic_gpio_name_map_num(gpio_name);
				amlogic_gpio_request(gpio_vbus_power_pin,VBUS_POWER_GPIO_OWNER);
				
				prop = of_get_property(of_node, "gpio-work-mask", NULL);
				if(prop)
					gpio_work_mask = of_read_ulong(prop,1);	
			}
			ctrl_reg_addr = (unsigned long)usb_platform_data.ctrl_regaddr[port_index];
			phy_reg_addr = (unsigned long)usb_platform_data.phy_regaddr[port_index];
			_dev->irq = usb_platform_data.irq_no[port_index];
printk("%s: type: %d, speed: %d, config: %d, dma: %d, id: %d, phy: %x, ctrl: %x\n",
	s_clock_name,port_type,port_speed,port_config,dma_config,id_mode,phy_reg_addr,ctrl_reg_addr);

		}
	}
#endif

	dwc_otg_device = DWC_ALLOC(sizeof(dwc_otg_device_t));

	if (!dwc_otg_device) {
		dev_err(&_dev->dev, "kmalloc of dwc_otg_device failed\n");
		return -ENOMEM;
	}

	memset(dwc_otg_device, 0, sizeof(*dwc_otg_device));
	dwc_otg_device->os_dep.reg_offset = 0xFFFFFFFF;

	/*
	 * Map the DWC_otg Core memory into virtual address space.
	 */
#ifdef LM_INTERFACE

	clock = clk_get_sys(s_clock_name, NULL);
	if(clk_enable(clock)){
		dev_err(&_dev->dev, "Set dwc_otg PHY clock %s failed!\n",s_clock_name);
		return -ENODEV;
	}
	/*if(set_usb_phy_clk(_dev,1)){
		dev_err(&_dev->dev, "Set dwc_otg PHY clock failed!\n");
		return -ENODEV;
	}*/

	dwc_otg_device->os_dep.base = (void*)ctrl_reg_addr;
	//dwc_otg_device->os_dep.base = (void*)_dev->resource.start;
	//ioremap(_dev->resource.start, SZ_256K);

	if (!dwc_otg_device->os_dep.base) {
		dev_err(&_dev->dev, "ioremap() failed\n");
		DWC_FREE(dwc_otg_device);
		return -ENOMEM;
	}
	dev_dbg(&_dev->dev, "base=0x%08x\n",
		(unsigned)dwc_otg_device->os_dep.base);
#elif defined(PCI_INTERFACE)
	_dev->current_state = PCI_D0;
	_dev->dev.power.power_state = PMSG_ON;

	if (!_dev->irq) {
		DWC_ERROR("Found HC with no IRQ. Check BIOS/PCI %s setup!",
			  pci_name(_dev));
		iounmap(dwc_otg_device->os_dep.base);
		DWC_FREE(dwc_otg_device);
		return -ENODEV;
	}

	dwc_otg_device->os_dep.rsrc_start = pci_resource_start(_dev, 0);
	dwc_otg_device->os_dep.rsrc_len = pci_resource_len(_dev, 0);
	DWC_DEBUGPL(DBG_ANY, "PCI resource: start=%08x, len=%08x\n",
		    (unsigned)dwc_otg_device->os_dep.rsrc_start,
		    (unsigned)dwc_otg_device->os_dep.rsrc_len);
	if (!request_mem_region
	    (dwc_otg_device->os_dep.rsrc_start, dwc_otg_device->os_dep.rsrc_len,
	     "dwc_otg")) {
		dev_dbg(&_dev->dev, "error requesting memory\n");
		iounmap(dwc_otg_device->os_dep.base);
		DWC_FREE(dwc_otg_device);
		return -EFAULT;
	}

	dwc_otg_device->os_dep.base =
	    ioremap_nocache(dwc_otg_device->os_dep.rsrc_start,
			    dwc_otg_device->os_dep.rsrc_len);
	if (dwc_otg_device->os_dep.base == NULL) {
		dev_dbg(&_dev->dev, "error mapping memory\n");
		release_mem_region(dwc_otg_device->os_dep.rsrc_start,
				   dwc_otg_device->os_dep.rsrc_len);
		iounmap(dwc_otg_device->os_dep.base);
		DWC_FREE(dwc_otg_device);
		return -EFAULT;
	}
	dev_dbg(&_dev->dev, "base=0x%p (before adjust) \n",
		dwc_otg_device->os_dep.base);
	dwc_otg_device->os_dep.base = (char *)dwc_otg_device->os_dep.base;
	dev_dbg(&_dev->dev, "base=0x%p (after adjust) \n",
		dwc_otg_device->os_dep.base);
	dev_dbg(&_dev->dev, "%s: mapped PA 0x%x to VA 0x%p\n", __func__,
		(unsigned)dwc_otg_device->os_dep.rsrc_start,
		dwc_otg_device->os_dep.base);

	pci_set_master(_dev);
	pci_set_drvdata(_dev, dwc_otg_device);
#endif

	/*
	 * Initialize driver data to point to the global DWC_otg
	 * Device structure.
	 */
#ifdef LM_INTERFACE
	lm_set_drvdata(_dev, dwc_otg_device);
	dwc_otg_device->os_dep.lmdev = _dev;
	dwc_otg_device->gen_dev = &_dev->dev;
#elif defined(PCI_INTERFACE)
	pci_set_drvdata(_dev, dwc_otg_device);
	dwc_otg_device->os_dep.pcidev = _dev;
	dwc_otg_device->gen_dev = &_dev->dev;
#endif
	dwc_otg_device->dev_name = dev_name(dwc_otg_device->gen_dev);

	pcore_para = &dwc_otg_module_params;

	dev_dbg(&_dev->dev, "dwc_otg_device=0x%p\n", dwc_otg_device);

	dwc_otg_device->core_if = dwc_otg_cil_init(dwc_otg_device->os_dep.base);
	if (!dwc_otg_device->core_if) {
		dev_err(&_dev->dev, "CIL initialization failed!\n");
		retval = -ENOMEM;
		goto fail;
	}

	//dwc_otg_device->core_if->usb_peri_reg = (usb_peri_reg_t *)_dev->param.usb.phy_tune_reg;
	dwc_otg_device->core_if->usb_peri_reg = (usb_peri_reg_t *)phy_reg_addr;
	/*
	 * Attempt to ensure this device is really a DWC_otg Controller.
	 * Read and verify the SNPSID register contents. The value should be
	 * 0x45F42XXX, which corresponds to "OT2", as in "OTG version 2.XX".
	 */

	if ((dwc_otg_get_gsnpsid(dwc_otg_device->core_if) & 0xFFFFF000) !=
	    0x4F542000) {
		dev_err(&_dev->dev, "Bad value for SNPSID: 0x%08x\n",
			dwc_otg_get_gsnpsid(dwc_otg_device->core_if));
		retval = -EINVAL;
		goto fail;
	}

	dev_dbg(&_dev->dev,"DMA config: %s\n",dma_config_name[dma_config]);
	if (dma_config == USB_DMA_DISABLE) {
		pcore_para->dma_enable = 0;
		_dev->dev.coherent_dma_mask = 0;
		_dev->dev.dma_mask = 0;
	} else {
		_dev->dev.dma_mask = &_dev->dma_mask_room;
		_dev->dev.coherent_dma_mask = *_dev->dev.dma_mask;
		//printk("_lmdev->dev.dma_mask %p (%llX)\n",_lmdev->dev.dma_mask,*_lmdev->dev.dma_mask);
		switch (dma_config) {
		case USB_DMA_BURST_INCR:
			pcore_para->dma_burst_size =
			    DWC_GAHBCFG_INT_DMA_BURST_INCR;
			break;
		case USB_DMA_BURST_INCR4:
			pcore_para->dma_burst_size =
			    DWC_GAHBCFG_INT_DMA_BURST_INCR4;
			break;
		case USB_DMA_BURST_INCR8:
			pcore_para->dma_burst_size =
			    DWC_GAHBCFG_INT_DMA_BURST_INCR8;
			break;
		case USB_DMA_BURST_INCR16:
			pcore_para->dma_burst_size =
			    DWC_GAHBCFG_INT_DMA_BURST_INCR16;
			break;
		case USB_DMA_BURST_SINGLE:
			pcore_para->dma_burst_size =
			    DWC_GAHBCFG_INT_DMA_BURST_SINGLE;
			break;
		default:
			pcore_para->dma_burst_size =
			    DWC_GAHBCFG_INT_DMA_BURST_INCR4;
			break;
		}
	}

	/*
	 * Validate parameter values.
	 */
	if (set_parameters(dwc_otg_device->core_if)) {
		retval = -EINVAL;
		goto fail;
	}

	/*
	 * Create Device Attributes in sysfs
	 */
	dwc_otg_attr_create(_dev);

	/*
	 * Disable the global interrupt until all the interrupt
	 * handlers are installed.
	 */
	dwc_otg_disable_global_interrupts(dwc_otg_device->core_if);

	/*
	 * Install the interrupt handler for the common interrupts before
	 * enabling common interrupts in core_init below.
	 */
	DWC_DEBUGPL(DBG_CIL, "registering (common) handler for irq%d\n",
		    _dev->irq);
	retval = request_irq(_dev->irq, dwc_otg_common_irq,
			     IRQF_SHARED | IRQF_DISABLED | IRQ_LEVEL, "dwc_otg",
			     dwc_otg_device);
	if (retval) {
		DWC_ERROR("request of irq%d failed\n", _dev->irq);
		retval = -EBUSY;
		goto fail;
	} else {
		dwc_otg_device->common_irq_installed = 1;
	}

#ifdef LM_INTERFACE
//	set_irq_type(_dev->irq, IRQT_LOW);
#endif

	switch(port_type){
	case USB_PORT_TYPE_OTG:
		id_mode = FORCE_ID_CLEAR;
		break;
	case USB_PORT_TYPE_HOST:
		id_mode = FORCE_ID_HOST;
		break;
	case USB_PORT_TYPE_SLAVE:
		id_mode = FORCE_ID_SLAVE;
		break;
	default:
		id_mode = FORCE_ID_ERROR;
		break;
	}
	dwc_otg_set_force_id(dwc_otg_device->core_if,id_mode);

	/*
	 * Initialize the DWC_otg core.
	 */
	dwc_otg_core_init(dwc_otg_device->core_if);

	/*
	 *   Set VBus Power CallBack
	 */
	dwc_otg_device->core_if->vbus_power_pin = gpio_vbus_power_pin;
	dwc_otg_device->core_if->vbus_power_pin_work_mask= gpio_work_mask;

	if (port_type == USB_PORT_TYPE_HOST) {
		/*
		 * Initialize the HCD
		 */
		printk("Working on port type = HOST\n");
		if (!dwc_otg_is_host_mode(dwc_otg_device->core_if)) {
			printk
			    ("Chip mode not match! -- Want HOST mode but not.  --\n");
			goto fail;
		}
		retval = hcd_init(_dev);
		if (retval != 0) {
			DWC_ERROR("hcd_init failed\n");
			dwc_otg_device->hcd = NULL;
			goto fail;
		}
	} else if (port_type == USB_PORT_TYPE_SLAVE) {
		/*
		 * Initialize the PCD
		 */
		printk("Working on port type = SLAVE\n");
		if (!dwc_otg_is_device_mode(dwc_otg_device->core_if)) {
			DWC_ERROR
			    ("Chip mode not match! -- Want Device mode but not.  --\n");
			goto fail;
		}
		//dwc_otg_device->core_if->charger_detect_cb = _dev->param.usb.charger_detect_cb;
		retval = pcd_init(_dev);
		if (retval != 0) {
			DWC_ERROR("pcd_init failed\n");
			dwc_otg_device->pcd = NULL;
			goto fail;
		}
	}

	else if (port_type == USB_PORT_TYPE_OTG) {
		printk("Working on port type = OTG\n");
		printk("Current port type: %s\n",
			dwc_otg_is_host_mode(dwc_otg_device->core_if)?"HOST":"SLAVE");

		retval = hcd_init(_dev);
		if (retval != 0) {
			DWC_ERROR("hcd_init failed(in otg mode)\n");
			dwc_otg_device->hcd = NULL;
			goto fail;
		}
		//dwc_otg_device->core_if->charger_detect_cb = _dev->param.usb.charger_detect_cb;
		retval = pcd_init(_dev);
		if (retval != 0) {
			DWC_ERROR("pcd_init failed(in otg mode)\n");
			dwc_otg_device->pcd = NULL;
			goto fail;
		}
		if(!dwc_otg_get_param_adp_enable(dwc_otg_device->core_if)){
			DWC_PRINTF("using timer detect id change, %p\n",dwc_otg_device->core_if);
			dwc_otg_device->id_change_timer = DWC_TIMER_ALLOC("ID change timer",
				dwc_otg_id_change_timer_handler,dwc_otg_device);
			DWC_TIMER_SCHEDULE(dwc_otg_device->id_change_timer, 0);
		}
	}

	else {
		DWC_ERROR("can't config as right mode\n");
		goto fail;
	}

	dwc_otg_save_global_regs(dwc_otg_device->core_if);

	/*
	 * Enable the global interrupt after all the interrupt
	 * handlers are installed if there is no ADP support else
	 * perform initial actions required for Internal ADP logic.
	 */

	if(port_type == USB_PORT_TYPE_OTG){
		if (!dwc_otg_get_param_adp_enable(dwc_otg_device->core_if))
			dwc_otg_enable_global_interrupts(dwc_otg_device->core_if);
		else
			dwc_otg_adp_start(dwc_otg_device->core_if,
								dwc_otg_is_host_mode(dwc_otg_device->core_if));
	}else{
		dwc_otg_enable_global_interrupts(dwc_otg_device->core_if);
	}
#ifdef CONFIG_HAS_EARLYSUSPEND
        dwc_otg_device->usb_early_suspend.level = EARLY_SUSPEND_LEVEL_DISABLE_FB;
        dwc_otg_device->usb_early_suspend.suspend = usb_early_suspend;
        dwc_otg_device->usb_early_suspend.resume = usb_early_resume;
        dwc_otg_device->usb_early_suspend.param = dwc_otg_device;
        register_early_suspend(&dwc_otg_device->usb_early_suspend);
#endif
	return 0;

fail:
	dwc_otg_driver_remove(_dev);
	return retval;
}
