switch (phyCbState) {
      // secondary none
      case PHY_SINGLE_CHANNEL_CENTERED:
        cbIniValue = 0;
        break;
      // secondary LOW
      case PHY_DOUBLE_CHANNEL_HIGH_PRIMARY:
        cbIniValue = 1;
        break;
      // secondary HIGH
      case PHY_DOUBLE_CHANNEL_LOW_PRIMARY:
        cbIniValue = 2;
        break;
#ifdef WLAN_FEATURE_11AC
      case PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_CENTERED:
        cbIniValue = 3;
        break;
      case PHY_QUADRUPLE_CHANNEL_20MHZ_CENTERED_40MHZ_CENTERED:
        cbIniValue = 4;
        break;
      case PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_CENTERED:
        cbIniValue = 5;
        break;
      case PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW:
        cbIniValue = 6;
        break;
      case PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_LOW:
        cbIniValue = 7;
        break;
      case PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH:
        cbIniValue = 8;
        break;
      case PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_HIGH:
        cbIniValue = 9;
        break;
#endif
      default:
        // return some invalid value
        cbIniValue = 10;
        break;
   }
