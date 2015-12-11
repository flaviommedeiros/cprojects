#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
if((ep->num == 1)&&(pdev->cfg.coreID == USB_OTG_HS_CORE_ID))
  {
    USB_OTG_MODIFY_REG32(&pdev->regs.DREGS->DEACHMSK, 0, daintmsk.d32);
  }
  else
#endif   
    USB_OTG_MODIFY_REG32(&pdev->regs.DREGS->DAINTMSK, 0, daintmsk.d32);
