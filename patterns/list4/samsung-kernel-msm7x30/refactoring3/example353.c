switch (set_value)
           {
              case  0: //Full Power
              {
                 struct statsContext context;
                 eHalStatus status;

                 init_completion(&context.completion);

                 context.pAdapter = pAdapter;
                 context.magic = POWER_CONTEXT_MAGIC;

                 status = sme_RequestFullPower(WLAN_HDD_GET_HAL_CTX(pAdapter),
                              iw_power_callback_fn, &context,
                              eSME_FULL_PWR_NEEDED_BY_HDD);
                 if(eHAL_STATUS_PMC_PENDING == status)
                 {
                    int lrc = wait_for_completion_interruptible_timeout(
                                  &context.completion,
                                  msecs_to_jiffies(WLAN_WAIT_TIME_POWER));
                    context.magic = 0;
                    if (lrc <= 0)
                    {
                       hddLog(VOS_TRACE_LEVEL_ERROR,"%s: SME %s while "
                                 "requesting fullpower ",
                                 __FUNCTION__, (0 == lrc) ?
                                 "timeout" : "interrupt");
                       /* there is a race condition such that the callback
                          function could be executing at the same time we are. of
                          primary concern is if the callback function had already
                          verified the "magic" but hasn't yet set the completion
                          variable. Since the completion variable is on our
                          stack, we'll delay just a bit to make sure the data is
                          still valid if that is the case */
                       msleep(50);
                       /* we'll now returned a cached value below */
                    }
                 }
                 hddLog(LOGE, "iwpriv Full Power completed\n");
                 break;
              }
              case  1: //Enable BMPS
                 sme_EnablePowerSave(hHal, ePMC_BEACON_MODE_POWER_SAVE);
                 break;
              case  2: //Disable BMPS
                 sme_DisablePowerSave(hHal, ePMC_BEACON_MODE_POWER_SAVE);
                 break;
              case  3: //Request Bmps
              {
                 struct statsContext context;
                 eHalStatus status;

                 init_completion(&context.completion);

                 context.pAdapter = pAdapter;
                 context.magic = POWER_CONTEXT_MAGIC;

                 status = sme_RequestBmps(WLAN_HDD_GET_HAL_CTX(pAdapter),
                           iw_power_callback_fn, &context);
                 if(eHAL_STATUS_PMC_PENDING == status)
                 {
                    int lrc = wait_for_completion_interruptible_timeout(
                                  &context.completion,
                                  msecs_to_jiffies(WLAN_WAIT_TIME_POWER));
                    context.magic = 0;
                    if (lrc <= 0)
                    {
                       hddLog(VOS_TRACE_LEVEL_ERROR,"%s: SME %s while "
                                "requesting BMPS",
                                 __FUNCTION__, (0 == lrc) ? "timeout" :
                                 "interrupt");
                       /* there is a race condition such that the callback
                          function could be executing at the same time we are. of
                          primary concern is if the callback function had already
                          verified the "magic" but hasn't yet set the completion
                          variable. Since the completion variable is on our
                          stack, we'll delay just a bit to make sure the data is
                          still valid if that is the case */
                       msleep(50);
                       /* we'll now returned a cached value below */
                    }
                 }
                 hddLog(LOGE, "iwpriv Request BMPS completed\n");
                 break;
              }
              case  4: //Enable IMPS
                 sme_EnablePowerSave(hHal, ePMC_IDLE_MODE_POWER_SAVE);
                 break;
              case  5: //Disable IMPS
                 sme_DisablePowerSave(hHal, ePMC_IDLE_MODE_POWER_SAVE);
                 break;
              case  6: //Enable Standby
                 sme_EnablePowerSave(hHal, ePMC_STANDBY_MODE_POWER_SAVE);
                 break;
              case  7: //Disable Standby
                 sme_DisablePowerSave(hHal, ePMC_STANDBY_MODE_POWER_SAVE);
                 break;
              case  8: //Request Standby
#ifdef CONFIG_HAS_EARLYSUSPEND
#ifdef FEATURE_WLAN_NON_INTEGRATED_SOC
                 (void)hdd_enter_standby(pAdapter->pHddCtx);
#endif
#endif
                 break;
              case  9: //Start Auto Bmps Timer
                 sme_StartAutoBmpsTimer(hHal);
                 break;
              case  10://Stop Auto BMPS Timer
                 sme_StopAutoBmpsTimer(hHal);
                 break;
#ifdef CONFIG_HAS_EARLYSUSPEND
              case  11://suspend to standby
#ifdef CONFIG_HAS_EARLYSUSPEND
                 nEnableSuspendOld = (WLAN_HDD_GET_CTX(pAdapter))->cfg_ini->nEnableSuspend;
                 (WLAN_HDD_GET_CTX(pAdapter))->cfg_ini->nEnableSuspend = 1;
#ifdef FEATURE_WLAN_NON_INTEGRATED_SOC
                 hdd_suspend_wlan(NULL);
#endif
                 (WLAN_HDD_GET_CTX(pAdapter))->cfg_ini->nEnableSuspend = nEnableSuspendOld;
#endif
                 break;
              case  12://suspend to deep sleep
#ifdef CONFIG_HAS_EARLYSUSPEND
                 nEnableSuspendOld = (WLAN_HDD_GET_CTX(pAdapter))->cfg_ini->nEnableSuspend;
                 (WLAN_HDD_GET_CTX(pAdapter))->cfg_ini->nEnableSuspend = 2;
#ifdef FEATURE_WLAN_NON_INTEGRATED_SOC
                 hdd_suspend_wlan(NULL);
#endif
                 (WLAN_HDD_GET_CTX(pAdapter))->cfg_ini->nEnableSuspend = nEnableSuspendOld;
#endif
                 break;
              case  13://resume from suspend
#ifdef CONFIG_HAS_EARLYSUSPEND
#ifdef FEATURE_WLAN_NON_INTEGRATED_SOC
                 hdd_resume_wlan(NULL);
#endif
#endif
                 break;
#endif
              case  14://reset wlan (power down/power up)
                 vos_chipReset(NULL, VOS_FALSE, NULL, NULL, VOS_CHIP_RESET_UNKNOWN_EXCEPTION);
                 break;
              default:
                 hddLog(LOGE, "Invalid arg  %d in WE_SET_POWER IOCTL\n", set_value);
                 ret = -EINVAL;
                 break;
           }
