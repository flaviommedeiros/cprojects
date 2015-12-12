switch (c) {
        case 'h':
        case '?':
            print("\nCommands for Bluetooth(WT12/iWRAP):\n");
            print("r: reset. software reset by watchdog\n");
            print("i: insomniac. prevent KB from sleeping\n");
            print("c: iwrap_call. CALL for BT connection.\n");
#ifdef PROTOCOL_VUSB
            print("u: USB mode. switch to USB.\n");
            print("w: BT mode. switch to Bluetooth.\n");
#endif
            print("k: kill first connection.\n");
            print("Del: unpair first pairing.\n");
            print("\n");
            return 0;
        case 'r':
            print("reset\n");
            WD_AVR_RESET();
            return 1;
        case 'i':
            insomniac = !insomniac;
            if (insomniac)
                print("insomniac\n");
            else
                print("not insomniac\n");
            return 1;
        case 'c':
            print("iwrap_call()\n");
            iwrap_call();
            return 1;
#ifdef PROTOCOL_VUSB
        case 'u':
            print("USB mode\n");
            init_vusb();
            change_driver(vusb_driver());
            //iwrap_kill();
            //iwrap_sleep();
            // disable suart receive interrut(PC5/PCINT13)
            PCMSK1 &= ~(0b00100000);
            PCICR  &= ~(0b00000010);
            return 1;
        case 'w':
            print("iWRAP mode\n");
            change_driver(iwrap_driver());
            disable_vusb();
            // enable suart receive interrut(PC5/PCINT13)
            PCMSK1 |= 0b00100000;
            PCICR  |= 0b00000010;
            return 1;
#endif
        case 'k':
            print("kill\n");
            iwrap_kill();
            return 1;
        case 0x7F:  // DELETE
            print("unpair\n");
            iwrap_unpair();
            return 1;
    }
