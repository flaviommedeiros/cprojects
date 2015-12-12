if(
      config.net.setup & NS_DHCP &&
#if defined(__s390__) || defined(__s390x__)
      config.hwp.layer2 != LAYER2_NO &&
#endif
      !config.ifcfg.manual->ptp
    ) {
      sprintf(buf, "Automatic configuration via %s?", "DHCP");
      rc = dia_yesno(buf, YES);
    }
    else {
      rc = NO;
    }
