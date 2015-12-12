switch(g_extern.console.sound.mode)
            {
               case SOUND_MODE_NORMAL:
                  strlcpy(comment, "INFO - [Sound Output] is set to 'Normal'.", sizeof(comment));
                  strlcpy(setting_text, "Normal", sizeof(setting_text));
                  break;
#ifdef HAVE_RSOUND
               case SOUND_MODE_RSOUND:
                  strlcpy(comment, "INFO - [Sound Output] is set to 'RSound'.", sizeof(comment));
                  strlcpy(setting_text, "RSound", sizeof(setting_text));
                  break;
#endif
#ifdef HAVE_HEADSET
               case SOUND_MODE_HEADSET:
                  strlcpy(comment, "INFO - [Sound Output] is set to USB/Bluetooth Headset.", sizeof(comment));
                  strlcpy(setting_text, "USB/Bluetooth Headset", sizeof(setting_text));
                  break;
#endif
               default:
                  break;
            }
