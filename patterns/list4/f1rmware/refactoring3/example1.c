switch (menuitem) {
                    case MENU_FREQ:
                        my_set_frequency(frequency - frequency_step);
                        break;
                    case MENU_STEP:
                        if(frequency_step > 1000) frequency_step /= 10;
                        break;
                    case MENU_VOLUME:
                        if(transmitting && txvolume > 0) txvolume--;
                        if(!transmitting && audiovolume > 0) audiovolume--;
                        break;
                    case MENU_LNA:
                        if(lna_enable) lna_enable=false; else lna_enable=true;
                        set_rf_params();
                        break;
                    case MENU_BBLNA:
                        if(lna_gain_db > 0) lna_gain_db-=8;
                        set_rf_params();
                        break;
                    case MENU_BBVGA:
                        if(vga_gain_db > 0) vga_gain_db-=2;
                        set_rf_params();
                        break;
#ifdef TRANSMIT
                    case MENU_BBTXVGA:
                        if(txvga_gain_db > 0) txvga_gain_db--;
                        set_rf_params();
                        break;
                    case MENU_TRANSMIT:
                        transmit(!transmitting);
                        break;
#endif // TRANSMIT
                    default: /*nothing*/ break;
                }
