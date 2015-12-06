#if defined(USE_DEVICE_MODE)
if (pyb_usb_storage_medium == PYB_USB_STORAGE_MEDIUM_SDCARD)
            #endif
            {
                // use SD card as current directory
                f_chdrive("/sd");
            }
