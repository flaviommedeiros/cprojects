switch (private->kbdType) {
#ifdef WSKBD_TYPE_ZAURUS
  case WSKBD_TYPE_ZAURUS:
    /* top row */
    keymap[2] = SDLK_1;
    keymap[3] = SDLK_2;
    keymap[4] = SDLK_3;
    keymap[5] = SDLK_4;
    keymap[6] = SDLK_5;
    keymap[7] = SDLK_6;
    keymap[8] = SDLK_7;
    keymap[9] = SDLK_8;
    keymap[10] = SDLK_9;
    keymap[11] = SDLK_0;
    keymap[14] = SDLK_BACKSPACE;
    
    /* second row */
    keymap[16] = SDLK_q;
    keymap[17] = SDLK_w;
    keymap[18] = SDLK_e;
    keymap[19] = SDLK_r;
    keymap[20] = SDLK_t;
    keymap[21] = SDLK_y;
    keymap[22] = SDLK_u;
    keymap[23] = SDLK_i;
    keymap[24] = SDLK_o;
    keymap[25] = SDLK_p;

    /* third row */
    keymap[15] = SDLK_TAB;
    keymap[30] = SDLK_a;
    keymap[31] = SDLK_s;
    keymap[32] = SDLK_d;
    keymap[33] = SDLK_f;
    keymap[34] = SDLK_g;
    keymap[35] = SDLK_h;
    keymap[36] = SDLK_j;
    keymap[37] = SDLK_k;
    keymap[38] = SDLK_l;

    /* fourth row */
    keymap[42] = SDLK_LSHIFT;
    keymap[44] = SDLK_z;
    keymap[45] = SDLK_x;
    keymap[46] = SDLK_c;
    keymap[47] = SDLK_v;
    keymap[48] = SDLK_b;
    keymap[49] = SDLK_n;
    keymap[50] = SDLK_m;
    keymap[54] = SDLK_RSHIFT;
    keymap[28] = SDLK_RETURN;

    /* fifth row */
    keymap[56] = SDLK_LALT;
    keymap[29] = SDLK_LCTRL;
    /* keymap[56] = ; */
    keymap[0] = SDLK_LSUPER;
    keymap[12] = SDLK_MINUS;
    keymap[57] = SDLK_SPACE;
    keymap[51] = SDLK_COMMA;
    keymap[52] = SDLK_PERIOD;

    /* misc */
    keymap[59] = SDLK_F1;
    keymap[60] = SDLK_F2;
    keymap[61] = SDLK_F3;
    keymap[62] = SDLK_F4;
    keymap[63] = SDLK_F5;
    keymap[1] = SDLK_ESCAPE;
    /* keymap[28] = SDLK_KP_ENTER; */
    keymap[72] = SDLK_UP;
    keymap[75] = SDLK_LEFT;
    keymap[77] = SDLK_RIGHT;
    keymap[80] = SDLK_DOWN;
    break;
#endif /* WSKBD_TYPE_ZAURUS */

  default:
    WSCONS_ReportError("Unable to map keys for keyboard type %u", 
		       private->kbdType);
    break;
  }
