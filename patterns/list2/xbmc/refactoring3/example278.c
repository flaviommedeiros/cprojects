switch (read_32bitLE(0x18,streamFile)) {
        case 0:
            coding = coding_PSX;
            break;
        case 1:
            coding = coding_XBOX;
            break;
        case 2:
            coding = coding_NGC_DTK;
            if (channel_count != 2) goto fail;
            break;
        case 3:
            coding = coding_PCM16BE;
            break;
        case 4:
            coding = coding_PCM16LE;
            break;
        case 5:
            coding = coding_PCM8;
            break;
        case 6:
            coding = coding_SDX2;
            break;
        case 7:
            coding = coding_DVI_IMA;
            break;
#ifdef VGM_USE_MPEG
        case 8:
            /* we say MPEG-1 L3 here, but later find out exactly which */
            coding = coding_MPEG1_L3;
            break;
#endif
        case 9:
            coding = coding_IMA;
            break;
        case 10:
            coding = coding_AICA;
            break;
        case 11:
            coding = coding_MSADPCM;
            break;
        case 12:
            coding = coding_NGC_DSP;
            break;
        case 13:
            coding = coding_PCM8_U_int;
            break;
        case 14:
            coding = coding_PSX_badflags;
            break;
        default:
            goto fail;
    }
