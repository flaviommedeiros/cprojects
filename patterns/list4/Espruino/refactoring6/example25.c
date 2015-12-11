if ((jsiStatus & JSIS_ALLOW_DEEP_SLEEP) &&  // from setDeepSleep
#ifdef STM32F1
      (timeUntilWake > (jshGetTimeForSecond()*3/2)) &&  // if there's less time that this then we can't go to sleep because we can't be sure we'll wake in time
#else
      (timeUntilWake > (jshGetTimeForSecond()*16*2/jshRTCPrescaler)) &&  // if there's less time that this then we can't go to sleep because we can't be sure we'll wake in time
#endif
      !jstUtilTimerIsRunning() && // if the utility timer is running (eg. digitalPulse, Waveform output, etc) then that would stop
      !jshHasTransmitData() && // if we're transmitting, we don't want USART/etc to get slowed down
#ifdef USB
      !jshIsUSBSERIALConnected() &&
      jshLastWokenByUSB+jshGetTimeForSecond()<jshGetRTCSystemTime() && // if woken by USB, stay awake long enough for the PC to make a connection
#endif
      ticksSinceStart>RTC_INITIALISE_TICKS && // Don't sleep until RTC has initialised
      true
      ) {
    jsiSetSleep(JSI_SLEEP_DEEP);
    // deep sleep!
    jshADCInitialised = 0;
    ADC_Cmd(ADC1, DISABLE); // ADC off
#ifdef ADC2
    ADC_Cmd(ADC2, DISABLE); // ADC off
#endif
#ifdef ADC3
    ADC_Cmd(ADC3, DISABLE); // ADC off
#endif
#ifdef ADC4
    ADC_Cmd(ADC4, DISABLE); // ADC off
#endif
#ifdef USB
    jshSetUSBPower(false);
#endif // USB

    /* Add EXTI for Serial port */
    //jshPinWatch(JSH_PORTA_OFFSET+10, true);
    /* add exti for USB */
#ifdef USB
#ifdef STM32F1
    // USB has 15k pull-down resistors (and STM32 has 40k pull up)
    Pin usbPin = JSH_PORTA_OFFSET+11;
    jshPinSetState(usbPin, JSHPINSTATE_GPIO_IN_PULLUP);
    Pin oldWatch = watchedPins[pinInfo[usbPin].pin];
    jshPinWatch(usbPin, true);
#endif
#ifdef USB_VSENSE_PIN
    // USB_VSENSE_PIN is connected to USB 5v (and pulled down by a 100k resistor)
    // ... so wake up if it goes high
    Pin oldWatch = watchedPins[pinInfo[USB_VSENSE_PIN].pin];
    jshPinWatch(USB_VSENSE_PIN, true);
#endif
#endif // USB

    if (timeUntilWake!=JSSYSTIME_MAX) { // set alarm
      unsigned int ticks = (unsigned int)(timeUntilWake/jshGetTimeForSecond()); // ensure we round down and leave a little time

#ifdef STM32F1
      /* If we're going asleep for more than a few seconds,
       * add one second to the sleep time so that when we
       * wake up, we execute our timer immediately (even if it is a bit late)
       * and don't waste power in shallow sleep. This is documented in setInterval */
      if (ticks>3) ticks++; // sleep longer than we need

      RTC_SetAlarm(RTC_GetCounter() + ticks);
      RTC_ITConfig(RTC_IT_ALR, ENABLE);
      //RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
      RTC_WaitForLastTask();
#else // If available, just use the WakeUp counter
      if (ticks < ((65536*16) / jshRTCPrescaler)) {
        // if the delay is small enough, clock the WakeUp counter faster so we can sleep more accurately
        RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);
        ticks = (unsigned int)((timeUntilWake*jshRTCPrescaler) / (jshGetTimeForSecond()*16));
      } else { // wakeup in seconds
        RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
        if (ticks > 65535) ticks = 65535;
      }
      RTC_SetWakeUpCounter(ticks - 1); // 0 based
      RTC_ITConfig(RTC_IT_WUT, ENABLE);
      RTC_WakeUpCmd(ENABLE);
      RTC_ClearFlag(RTC_FLAG_WUTF);
#endif
    }
    // set flag in case there happens to be a SysTick
    hasSystemSlept = true;
    // -----------------------------------------------
#ifdef STM32F4
    /* FLASH Deep Power Down Mode enabled */
    PWR_FlashPowerDownCmd(ENABLE);
#endif
    /* Request to enter STOP mode with regulator in low power mode*/
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
    // -----------------------------------------------
    if (timeUntilWake!=JSSYSTIME_MAX) { // disable alarm
#ifdef STM32F1
      RTC_ITConfig(RTC_IT_ALR, DISABLE);
      //RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
#else
      RTC_ITConfig(RTC_IT_WUT, DISABLE);
      RTC_WakeUpCmd(DISABLE);
#endif
    }
#ifdef USB
    bool wokenByUSB = false;
#ifdef STM32F1
    wokenByUSB = jshPinGetValue(usbPin)==0;
    // remove watches on pins
    jshPinWatch(usbPin, false);
    if (oldWatch!=PIN_UNDEFINED) jshPinWatch(oldWatch, true);
    jshPinSetState(usbPin, JSHPINSTATE_GPIO_IN);
#endif
#ifdef USB_VSENSE_PIN
    // remove watch and restore old watch if there was one
    // setting that we've woken lets the board stay awake
    // until a USB connection can be established
    if (jshPinGetValue(USB_VSENSE_PIN)) wokenByUSB=true;
    jshPinWatch(USB_VSENSE_PIN, false);
    if (oldWatch!=PIN_UNDEFINED) jshPinWatch(oldWatch, true);
#endif
#endif
    // recover oscillator
    RCC_HSEConfig(RCC_HSE_ON);
    if( RCC_WaitForHSEStartUp() == SUCCESS) {
      RCC_PLLCmd(ENABLE);
      while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
      while(RCC_GetSYSCLKSource() != 0x08);
    }
    RTC_WaitForSynchro(); // make sure any RTC reads will be done
#ifdef USB
    jshSetUSBPower(true);
    if (wokenByUSB)
      jshLastWokenByUSB = jshGetRTCSystemTime();
#endif
    jsiSetSleep(JSI_SLEEP_AWAKE);
  } else
#endif
  {
    JsSysTime sysTickTime;
#ifdef USE_RTC
    sysTickTime = averageSysTickTime*5/4;
#else
    sysTickTime = SYSTICK_RANGE*5/4;
#endif
    if (timeUntilWake < sysTickTime) {
      jstSetWakeUp(timeUntilWake);
    } else {
      // we're going to wake on a System Tick timer anyway, so don't bother
    }

    jsiSetSleep(JSI_SLEEP_ASLEEP);
    __WFI(); // Wait for Interrupt
    jsiSetSleep(JSI_SLEEP_AWAKE);

    /* We may have woken up before the wakeup event. If so
    then make sure we clear the event */
    jstClearWakeUp();
    return true;
  }
