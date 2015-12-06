#ifdef HAVE_BB10
if (strstr(controller->id, "057E-0306"))
         strlcpy(name_buf, "Wiimote", sizeof(name_buf));
      else
#endif
         if (strstr(controller->id, "0A5C-8502"))
            strlcpy(name_buf, "BlackBerry BT Keyboard", sizeof(name_buf));
#ifdef HAVE_BB10
         else if (strstr(controller->id, "qwerty:bb35"))
            strlcpy(name_buf, "BlackBerry Q10 Keypad", sizeof(name_buf));
