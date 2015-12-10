#ifdef PSPIRKEYB
if (irkbd_ready) {
            unsigned char buffer[255];
        int i, length, count;
        SIrKeybScanCodeData *scanData;

            if(pspIrKeybReadinput(buffer, &length) >= 0) {
                if((length % sizeof(SIrKeybScanCodeData)) == 0){
                    count = length / sizeof(SIrKeybScanCodeData);
                    for( i=0; i < count; i++ ) {
                unsigned char raw, pressed;
                        scanData=(SIrKeybScanCodeData*) buffer+i;
                        raw = scanData->raw;
                        pressed = scanData->pressed;
                sym.scancode = raw;
                sym.sym = keymap[raw];
                /* not tested */
                /* SDL_PrivateKeyboard(pressed?SDL_PRESSED:SDL_RELEASED, &sym); */
                SDL_SendKeyboardKey((keys & keymap_psp[i].id) ?
                                    SDL_PRESSED : SDL_RELEASED, (Uint32)(keymap[raw]), SDL_GetScancodeFromKey(keymap[raw]);

                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    return;
}

void PSP_InitOSKeymap(_THIS)
{
#ifdef PSPIRKEYB
    int i;
    for (i=0; i<SDL_TABLESIZE(keymap); ++i)
        keymap[i] = SDLK_UNKNOWN;

    keymap[KEY_ESC] = SDLK_ESCAPE;

    keymap[KEY_F1] = SDLK_F1;
    keymap[KEY_F2] = SDLK_F2;
    keymap[KEY_F3] = SDLK_F3;
    keymap[KEY_F4] = SDLK_F4;
    keymap[KEY_F5] = SDLK_F5;
    keymap[KEY_F6] = SDLK_F6;
    keymap[KEY_F7] = SDLK_F7;
    keymap[KEY_F8] = SDLK_F8;
    keymap[KEY_F9] = SDLK_F9;
    keymap[KEY_F10] = SDLK_F10;
    keymap[KEY_F11] = SDLK_F11;
    keymap[KEY_F12] = SDLK_F12;
    keymap[KEY_F13] = SDLK_PRINT;
    keymap[KEY_F14] = SDLK_PAUSE;

    keymap[KEY_GRAVE] = SDLK_BACKQUOTE;
    keymap[KEY_1] = SDLK_1;
    keymap[KEY_2] = SDLK_2;
    keymap[KEY_3] = SDLK_3;
    keymap[KEY_4] = SDLK_4;
    keymap[KEY_5] = SDLK_5;
    keymap[KEY_6] = SDLK_6;
    keymap[KEY_7] = SDLK_7;
    keymap[KEY_8] = SDLK_8;
    keymap[KEY_9] = SDLK_9;
    keymap[KEY_0] = SDLK_0;
    keymap[KEY_MINUS] = SDLK_MINUS;
    keymap[KEY_EQUAL] = SDLK_EQUALS;
    keymap[KEY_BACKSPACE] = SDLK_BACKSPACE;

    keymap[KEY_TAB] = SDLK_TAB;
    keymap[KEY_Q] = SDLK_q;
    keymap[KEY_W] = SDLK_w;
    keymap[KEY_E] = SDLK_e;
    keymap[KEY_R] = SDLK_r;
    keymap[KEY_T] = SDLK_t;
    keymap[KEY_Y] = SDLK_y;
    keymap[KEY_U] = SDLK_u;
    keymap[KEY_I] = SDLK_i;
    keymap[KEY_O] = SDLK_o;
    keymap[KEY_P] = SDLK_p;
    keymap[KEY_LEFTBRACE] = SDLK_LEFTBRACKET;
    keymap[KEY_RIGHTBRACE] = SDLK_RIGHTBRACKET;
    keymap[KEY_ENTER] = SDLK_RETURN;

    keymap[KEY_CAPSLOCK] = SDLK_CAPSLOCK;
    keymap[KEY_A] = SDLK_a;
    keymap[KEY_S] = SDLK_s;
    keymap[KEY_D] = SDLK_d;
    keymap[KEY_F] = SDLK_f;
    keymap[KEY_G] = SDLK_g;
    keymap[KEY_H] = SDLK_h;
    keymap[KEY_J] = SDLK_j;
    keymap[KEY_K] = SDLK_k;
    keymap[KEY_L] = SDLK_l;
    keymap[KEY_SEMICOLON] = SDLK_SEMICOLON;
    keymap[KEY_APOSTROPHE] = SDLK_QUOTE;
    keymap[KEY_BACKSLASH] = SDLK_BACKSLASH;

    keymap[KEY_Z] = SDLK_z;
    keymap[KEY_X] = SDLK_x;
    keymap[KEY_C] = SDLK_c;
    keymap[KEY_V] = SDLK_v;
    keymap[KEY_B] = SDLK_b;
    keymap[KEY_N] = SDLK_n;
    keymap[KEY_M] = SDLK_m;
    keymap[KEY_COMMA] = SDLK_COMMA;
    keymap[KEY_DOT] = SDLK_PERIOD;
    keymap[KEY_SLASH] = SDLK_SLASH;

    keymap[KEY_SPACE] = SDLK_SPACE;

    keymap[KEY_UP] = SDLK_UP;
    keymap[KEY_DOWN] = SDLK_DOWN;
    keymap[KEY_LEFT] = SDLK_LEFT;
    keymap[KEY_RIGHT] = SDLK_RIGHT;

    keymap[KEY_HOME] = SDLK_HOME;
    keymap[KEY_END] = SDLK_END;
    keymap[KEY_INSERT] = SDLK_INSERT;
    keymap[KEY_DELETE] = SDLK_DELETE;

    keymap[KEY_NUMLOCK] = SDLK_NUMLOCK;
    keymap[KEY_LEFTMETA] = SDLK_LSUPER;

    keymap[KEY_KPSLASH] = SDLK_KP_DIVIDE;
    keymap[KEY_KPASTERISK] = SDLK_KP_MULTIPLY;
    keymap[KEY_KPMINUS] = SDLK_KP_MINUS;
    keymap[KEY_KPPLUS] = SDLK_KP_PLUS;
    keymap[KEY_KPDOT] = SDLK_KP_PERIOD;
    keymap[KEY_KPEQUAL] = SDLK_KP_EQUALS;

    keymap[KEY_LEFTCTRL] = SDLK_LCTRL;
    keymap[KEY_RIGHTCTRL] = SDLK_RCTRL;
    keymap[KEY_LEFTALT] = SDLK_LALT;
    keymap[KEY_RIGHTALT] = SDLK_RALT;
    keymap[KEY_LEFTSHIFT] = SDLK_LSHIFT;
    keymap[KEY_RIGHTSHIFT] = SDLK_RSHIFT;
#endif
}

void PSP_EventInit(_THIS)
{
#ifdef PSPIRKEYB
    int outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    int ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    if (ret == PSP_IRKBD_RESULT_OK) {
            pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } else {
        irkbd_ready = 0;
    }
#endif
    /* Start thread to read data */
    if((event_sem =  SDL_CreateSemaphore(1)) == NULL) {
        SDL_SetError("Can't create input semaphore\n");
        return;
    }
    running = 1;
    if((thread = SDL_CreateThread(EventUpdate, "PSPInputThread",NULL)) == NULL) {
        SDL_SetError("Can't create input thread\n");
        return;
    }
}

void PSP_EventQuit(_THIS)
{
    running = 0;
    SDL_WaitThread(thread, NULL);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    if (irkbd_ready) {
            pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}
