#ifdef USB_OTG_GLPMCFG_LPMEN
if(hpcd->LPM_State == LPM_L1)
      {
        hpcd->LPM_State = LPM_L0;
        HAL_PCDEx_LPM_Callback(hpcd, PCD_LPM_L0_ACTIVE);
      }
      else
#endif /* USB_OTG_GLPMCFG_LPMEN */
      {
        HAL_PCD_ResumeCallback(hpcd);
      }
