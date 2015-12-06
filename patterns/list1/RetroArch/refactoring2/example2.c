#ifdef HAVE_MFI
if (!ret)
#endif
            ret = input_joypad_analog(apple->joypad, port,
                  idx, id, binds[port]);
