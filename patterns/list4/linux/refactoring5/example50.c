#ifdef CONFIG_PCI_MSI
if (priv->flags & TSI721_USING_MSIX)
		err = tsi721_request_msix(mport);
	else
#endif
		err = request_irq(priv->pdev->irq, tsi721_irqhandler,
			  (priv->flags & TSI721_USING_MSI) ? 0 : IRQF_SHARED,
			  DRV_NAME, (void *)mport);
