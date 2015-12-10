switch (avctx->channels) {
    case 1: mode = MODE_1;       sce = 1; cpe = 0; break;
    case 2: mode = MODE_2;       sce = 0; cpe = 1; break;
    case 3: mode = MODE_1_2;     sce = 1; cpe = 1; break;
    case 4: mode = MODE_1_2_1;   sce = 2; cpe = 1; break;
    case 5: mode = MODE_1_2_2;   sce = 1; cpe = 2; break;
    case 6: mode = MODE_1_2_2_1; sce = 2; cpe = 2; break;
/* The version macro is introduced the same time as the 7.1 support, so this
   should suffice. */
#ifdef AACENCODER_LIB_VL0
    case 8:
        sce = 2;
        cpe = 3;
        if (avctx->channel_layout == AV_CH_LAYOUT_7POINT1) {
            mode = MODE_7_1_REAR_SURROUND;
        } else {
            // MODE_1_2_2_2_1 and MODE_7_1_FRONT_CENTER use the same channel layout
            mode = MODE_7_1_FRONT_CENTER;
        }
        break;
#endif
    default:
        av_log(avctx, AV_LOG_ERROR,
               "Unsupported number of channels %d\n", avctx->channels);
        goto error;
    }
