if (
//#if ! (defined GCS_NUMBER_1 || defined GCS_NUMBER_2 || defined SAFETY_NUMBER_1 || defined SAFETY_NUMBER_2)
    true
//#else
//      false
//#endif
#ifdef GCS_NUMBER_1
    || strncmp((char *)GCS_NUMBER_1, origin, strlen(GCS_NUMBER_1)) == 0
#endif
#ifdef GCS_NUMBER_2
    || strncmp((char *)GCS_NUMBER_2, origin, strlen(GCS_NUMBER_2)) == 0
#endif
#ifdef SAFETY_NUMBER_1
    || strncmp((char *)SAFETY_NUMBER_1, origin, strlen(SAFETY_NUMBER_1)) == 0
#endif
#ifdef SAFETY_NUMBER_2
    || strncmp((char *)SAFETY_NUMBER_2, origin, strlen(SAFETY_NUMBER_2)) == 0
#endif
  ) {
    // Decoding the message ...

    // Search for the instruction
    switch (gsm_buf[0]) {
      case 'B' : {
        uint8_t block_index = atoi(gsm_buf + 1);
        if (block_index > 0) { /* Warning: no way to go to the first block */
          nav_goto_block(block_index);
        }
        break;
      }
      case 'S' : {
        uint8_t var_index = atoi(gsm_buf + 1);
        if (var_index > 0) {
          float value = atof(indexn(gsm_buf, ' ', MAXLEN_SMS_CONTENT) + 1);
          DlSetting(var_index, value);
        }
      }

      default:
        // Report an error ???
        break;
    }
  }
