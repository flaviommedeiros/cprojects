switch(status_code) {          
        case STATUS_EXPECTED_COMMAND_LETTER:
        printPgmString(PSTR("Expected command letter")); break;
        case STATUS_BAD_NUMBER_FORMAT:
        printPgmString(PSTR("Bad number format")); break;
        case STATUS_INVALID_STATEMENT:
        printPgmString(PSTR("Invalid statement")); break;
        case STATUS_NEGATIVE_VALUE:
        printPgmString(PSTR("Value < 0")); break;
        case STATUS_SETTING_DISABLED:
        printPgmString(PSTR("Setting disabled")); break;
        case STATUS_SETTING_STEP_PULSE_MIN:
        printPgmString(PSTR("Value < 3 usec")); break;
        case STATUS_SETTING_READ_FAIL:
        printPgmString(PSTR("EEPROM read fail. Using defaults")); break;
        case STATUS_IDLE_ERROR:
        printPgmString(PSTR("Not idle")); break;
        case STATUS_ALARM_LOCK:
        printPgmString(PSTR("Alarm lock")); break;
        case STATUS_SOFT_LIMIT_ERROR:
        printPgmString(PSTR("Homing not enabled")); break;
        case STATUS_OVERFLOW:
        printPgmString(PSTR("Line overflow")); break;
        #ifdef MAX_STEP_RATE_HZ
          case STATUS_MAX_STEP_RATE_EXCEEDED: 
          printPgmString(PSTR("Step rate > 30kHz")); break;
        #endif      
        // Common g-code parser errors.
        case STATUS_GCODE_MODAL_GROUP_VIOLATION:
        printPgmString(PSTR("Modal group violation")); break;
        case STATUS_GCODE_UNSUPPORTED_COMMAND:
        printPgmString(PSTR("Unsupported command")); break;
        case STATUS_GCODE_UNDEFINED_FEED_RATE:
        printPgmString(PSTR("Undefined feed rate")); break;
        default:
          // Remaining g-code parser errors with error codes
          printPgmString(PSTR("Invalid gcode ID:"));
          print_uint8_base10(status_code); // Print error code for user reference
      }
