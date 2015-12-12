switch (request) {
#ifdef CONFIG_USB_OTG
	case REQUEST_HNP_SUSPEND:
		/* disable Root hub auto suspend. As hardware is configured
		 * for peripheral mode, mark hardware is not available.
		 */
		if (PHY_TYPE(pdata->phy_info) == USB_PHY_INTEGRATED) {
			pm_runtime_disable(&udev->dev);
			/* Mark root hub as disconnected. This would
			 * protect suspend/resume via sysfs.
			 */
			udev->state = USB_STATE_NOTATTACHED;
			clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
			hcd->state = HC_STATE_HALT;
			pm_runtime_put_noidle(dev);
			pm_runtime_suspend(dev);
		}
		break;
	case REQUEST_HNP_RESUME:
		if (PHY_TYPE(pdata->phy_info) == USB_PHY_INTEGRATED) {
			pm_runtime_get_noresume(dev);
			pm_runtime_resume(dev);
			disable_irq(hcd->irq);
			ehci_msm_reset(hcd);
			ehci_msm_run(hcd);
			set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
			pm_runtime_enable(&udev->dev);
			udev->state = USB_STATE_CONFIGURED;
			enable_irq(hcd->irq);
		}
		break;
#endif
	case REQUEST_RESUME:
		usb_hcd_resume_root_hub(hcd);
		break;
	case REQUEST_START:
		if (mhcd->running)
			break;
		pm_runtime_get_noresume(dev);
		pm_runtime_resume(dev);
		wake_lock(&mhcd->wlock);
		msm_xusb_pm_qos_update(mhcd, 1);
		msm_xusb_enable_clks(mhcd);
		if (PHY_TYPE(pdata->phy_info) == USB_PHY_INTEGRATED)
			if (otg->set_clk)
				otg->set_clk(mhcd->xceiv, 1);
		if (pdata->vbus_power)
			pdata->vbus_power(pdata->phy_info, 1);
		if (pdata->config_gpio)
			pdata->config_gpio(1);
		usb_add_hcd(hcd, hcd->irq, IRQF_SHARED);
		mhcd->running = 1;
		if (PHY_TYPE(pdata->phy_info) == USB_PHY_INTEGRATED)
			if (otg->set_clk)
				otg->set_clk(mhcd->xceiv, 0);
		break;
	case REQUEST_STOP:
		if (!mhcd->running)
			break;
		mhcd->running = 0;
		/* come out of lpm before deregistration */
		if (PHY_TYPE(pdata->phy_info) == USB_PHY_SERIAL_PMIC) {
			usb_lpm_exit(hcd);
			if (cancel_work_sync(&(mhcd->lpm_exit_work)))
				usb_lpm_exit_w(&mhcd->lpm_exit_work);
		}
		usb_remove_hcd(hcd);
		if (pdata->config_gpio)
			pdata->config_gpio(0);
		if (pdata->vbus_power)
			pdata->vbus_power(pdata->phy_info, 0);
		msm_xusb_disable_clks(mhcd);
		wake_lock_timeout(&mhcd->wlock, HZ/2);
		msm_xusb_pm_qos_update(mhcd, 0);
		pm_runtime_put_noidle(dev);
		pm_runtime_suspend(dev);
		break;
	}
