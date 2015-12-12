void dwc_otg_attr_create(
#ifdef LM_INTERFACE
				struct lm_device *dev
#elif  defined(PCI_INTERFACE)
				struct pci_dev *dev
#endif
    )
{
	int error;

	error = device_create_file(&dev->dev, &dev_attr_regoffset);
	error = device_create_file(&dev->dev, &dev_attr_regvalue);
	error = device_create_file(&dev->dev, &dev_attr_mode);
	error = device_create_file(&dev->dev, &dev_attr_hnpcapable);
	error = device_create_file(&dev->dev, &dev_attr_srpcapable);
	error = device_create_file(&dev->dev, &dev_attr_hsic_connect);
	error = device_create_file(&dev->dev, &dev_attr_inv_sel_hsic);
	error = device_create_file(&dev->dev, &dev_attr_hnp);
	error = device_create_file(&dev->dev, &dev_attr_srp);
	error = device_create_file(&dev->dev, &dev_attr_buspower);
	error = device_create_file(&dev->dev, &dev_attr_bussuspend);
	error = device_create_file(&dev->dev, &dev_attr_mode_ch_tim_en);
	error = device_create_file(&dev->dev, &dev_attr_fr_interval);
	error = device_create_file(&dev->dev, &dev_attr_busconnected);
	error = device_create_file(&dev->dev, &dev_attr_gotgctl);
	error = device_create_file(&dev->dev, &dev_attr_gusbcfg);
	error = device_create_file(&dev->dev, &dev_attr_grxfsiz);
	error = device_create_file(&dev->dev, &dev_attr_gnptxfsiz);
	error = device_create_file(&dev->dev, &dev_attr_gpvndctl);
	error = device_create_file(&dev->dev, &dev_attr_ggpio);
	error = device_create_file(&dev->dev, &dev_attr_guid);
	error = device_create_file(&dev->dev, &dev_attr_gsnpsid);
	error = device_create_file(&dev->dev, &dev_attr_devspeed);
	error = device_create_file(&dev->dev, &dev_attr_enumspeed);
	error = device_create_file(&dev->dev, &dev_attr_hptxfsiz);
	error = device_create_file(&dev->dev, &dev_attr_hprt0);
	error = device_create_file(&dev->dev, &dev_attr_remote_wakeup);
	error = device_create_file(&dev->dev, &dev_attr_rem_wakeup_pwrdn);
	error = device_create_file(&dev->dev, &dev_attr_disconnect_us);
	error = device_create_file(&dev->dev, &dev_attr_regdump);
	error = device_create_file(&dev->dev, &dev_attr_spramdump);
	error = device_create_file(&dev->dev, &dev_attr_hcddump);
	error = device_create_file(&dev->dev, &dev_attr_hcd_frrem);
	error = device_create_file(&dev->dev, &dev_attr_rd_reg_test);
	error = device_create_file(&dev->dev, &dev_attr_wr_reg_test);
#ifdef CONFIG_USB_DWC_OTG_LPM
	error = device_create_file(&dev->dev, &dev_attr_lpm_response);
	error = device_create_file(&dev->dev, &dev_attr_sleep_status);
#endif
	error = device_create_file(&dev->dev, &dev_attr_peri_iddq);
	error = device_create_file(&dev->dev, &dev_attr_peri_otg_disable);
	error = device_create_file(&dev->dev, &dev_attr_peri_power);
	error = device_create_file(&dev->dev, &dev_attr_peri_sleepm);


}
