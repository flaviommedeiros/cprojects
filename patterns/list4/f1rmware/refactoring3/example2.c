switch (menuitem) {
                    case MENU_FREQ:
                        my_set_frequency(frequency + frequency_step);
                        break;
                    case MENU_STEP:
                        if(frequency_step < 100000000) frequency_step *= 10;
                        break;
                    case MENU_VOLUME:
                        if(transmitting && txvolume < 16) txvolume++;
                        if(!transmitting && audiovolume < 80) audiovolume++;
                        break;
                    case MENU_EXIT:
                        goto stop;
                    case MENU_LNA:
                        if(lna_enable) lna_enable=false; else lna_enable=true;
                        set_rf_params();
                        break;
                    case MENU_BBLNA:
                        if(lna_gain_db < 40) lna_gain_db+=8;
                        set_rf_params();
                        break;
                    case MENU_BBVGA:
                        if(vga_gain_db < 62) vga_gain_db+=2;
                        set_rf_params();
                        break;
#ifdef TRANSMIT
                    case MENU_BBTXVGA:
                        if(txvga_gain_db < 47) txvga_gain_db++;
                        set_rf_params();
                        break;
                    case MENU_TRANSMIT:
                        // transmit as long as key is being held
                        transmit(!transmitting);
                        status();
                        getInputWaitRelease();
                        transmit(!transmitting);
                        break;
#endif // TRANSMIT
                    default: /*nothing*/ break;
                }
