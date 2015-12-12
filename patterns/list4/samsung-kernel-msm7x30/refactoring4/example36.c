#if (LINUX_VERSION_CODE < KERNEL_VERSION( 2,6,33 ))
if (pDev->udev->auto_pm == 0)
#else
   if ((powerEvent.event & PM_EVENT_AUTO) == 0)
#endif
   {
      DBG( "device suspended to power level %d\n", 
           powerEvent.event );
      QSetDownReason( pQCDev, DRIVER_SUSPENDED );
   }
   else
   {
      DBG( "device autosuspend\n" );
   }
