switch (gcs_index) {
#ifdef GCS_NUMBER_1
    case 0 :
      sprintf(buf, "AT+CMGS=\"%s\"", GCS_NUMBER_1);
      Send(buf);
      break;
#endif
#ifdef GCS_NUMBER_2
    case 1 :
      sprintf(buf, "AT+CMGS=\"%s\"", GCS_NUMBER_2);
      Send(buf);
      break;
#endif
    default :
      gcs_index = 0;
      break;
  }
