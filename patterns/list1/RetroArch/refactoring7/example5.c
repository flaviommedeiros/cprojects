return cocoa_input_is_pressed(apple, port, binds[port], id) ||
            input_joypad_pressed(apple->joypad, port, binds[port], id)
#ifdef HAVE_MFI
           || input_joypad_pressed(apple->sec_joypad, port, binds[port], id)
#endif
           ;
