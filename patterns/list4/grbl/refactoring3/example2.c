switch(int_value) {
              case 3: gc_block.modal.spindle = SPINDLE_ENABLE_CW; break;
              #ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
                case 4: gc_block.modal.spindle = SPINDLE_ENABLE_CCW; break;
              #endif
              case 5: gc_block.modal.spindle = SPINDLE_DISABLE; break;
            }
