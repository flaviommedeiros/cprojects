switch (cbIniValue) {
      // secondary none
      case 0:
        phyCbState = PHY_SINGLE_CHANNEL_CENTERED;
        break;
      // secondary LOW
      case 1:
        phyCbState = PHY_DOUBLE_CHANNEL_HIGH_PRIMARY;
        break;
      // secondary HIGH
      case 2:
        phyCbState = PHY_DOUBLE_CHANNEL_LOW_PRIMARY;
        break;
#ifdef WLAN_FEATURE_11AC
      case 3:
        phyCbState = PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_CENTERED; 
        break;
      case 4:
        phyCbState = PHY_QUADRUPLE_CHANNEL_20MHZ_CENTERED_40MHZ_CENTERED;
        break;
      case 5:
        phyCbState = PHY_QUADRUPLE_CHANNEL_20MHZ_CENTERED_40MHZ_CENTERED;
        break; 
      case 6:
        phyCbState = PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW;
        break;
      case 7:
        phyCbState = PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_LOW;
        break; 
      case 8:
        phyCbState = PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH;
        break;
      case 9:
        phyCbState = PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_HIGH;
        break; 
#endif 
      default:
        // If an invalid value is passed, disable CHANNEL BONDING
        phyCbState = PHY_SINGLE_CHANNEL_CENTERED;
        break;
   }
