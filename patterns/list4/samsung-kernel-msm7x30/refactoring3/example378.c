switch (dot11Mode) 
   {
      case (eHDD_DOT11_MODE_abg):
         return eCSR_DOT11_MODE_abg;
      case (eHDD_DOT11_MODE_11b):
         return eCSR_DOT11_MODE_11b;
      case (eHDD_DOT11_MODE_11g):
         return eCSR_DOT11_MODE_11g;
      default:
      case (eHDD_DOT11_MODE_11n):
         return eCSR_DOT11_MODE_11n;
      case (eHDD_DOT11_MODE_11g_ONLY):
         return eCSR_DOT11_MODE_11g_ONLY;
      case (eHDD_DOT11_MODE_11n_ONLY):
         return eCSR_DOT11_MODE_11n_ONLY;
      case (eHDD_DOT11_MODE_11b_ONLY):
         return eCSR_DOT11_MODE_11b_ONLY;
#ifdef WLAN_FEATURE_11AC
      case (eHDD_DOT11_MODE_11ac_ONLY):
         return eCSR_DOT11_MODE_11ac_ONLY;
      case (eHDD_DOT11_MODE_11ac):
         return eCSR_DOT11_MODE_11ac;
#endif
      case (eHDD_DOT11_MODE_AUTO):
         return eCSR_DOT11_MODE_AUTO;
   }
