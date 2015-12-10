switch(val) {
    case KBD_CCMD_READ_MODE:
        kbd_queue(s, s->mode, 0);
        break;
    case KBD_CCMD_WRITE_MODE:
    case KBD_CCMD_WRITE_OBUF:
    case KBD_CCMD_WRITE_AUX_OBUF:
    case KBD_CCMD_WRITE_MOUSE:
    case KBD_CCMD_WRITE_OUTPORT:
        s->write_cmd = val;
        break;
    case KBD_CCMD_MOUSE_DISABLE:
        s->mode |= KBD_MODE_DISABLE_MOUSE;
        break;
    case KBD_CCMD_MOUSE_ENABLE:
        s->mode &= ~KBD_MODE_DISABLE_MOUSE;
        break;
    case KBD_CCMD_TEST_MOUSE:
        kbd_queue(s, 0x00, 0);
        break;
    case KBD_CCMD_SELF_TEST:
        s->status |= KBD_STAT_SELFTEST;
        kbd_queue(s, 0x55, 0);
        break;
    case KBD_CCMD_KBD_TEST:
        kbd_queue(s, 0x00, 0);
        break;
    case KBD_CCMD_KBD_DISABLE:
        s->mode |= KBD_MODE_DISABLE_KBD;
        kbd_update_irq(s);
        break;
    case KBD_CCMD_KBD_ENABLE:
        s->mode &= ~KBD_MODE_DISABLE_KBD;
        kbd_update_irq(s);
        break;
    case KBD_CCMD_READ_INPORT:
        kbd_queue(s, 0x00, 0);
        break;
    case KBD_CCMD_READ_OUTPORT:
        /* XXX: check that */
#ifdef TARGET_I386
        val = 0x01 | (ioport_get_a20() << 1);
#else
        val = 0x01;
#endif
        if (s->status & KBD_STAT_OBF)
            val |= 0x10;
        if (s->status & KBD_STAT_MOUSE_OBF)
            val |= 0x20;
        kbd_queue(s, val, 0);
        break;
#ifdef TARGET_I386
    case KBD_CCMD_ENABLE_A20:
        ioport_set_a20(1);
        break;
    case KBD_CCMD_DISABLE_A20:
        ioport_set_a20(0);
        break;
#endif
    case KBD_CCMD_RESET:
        qemu_system_reset_request();
        break;
    case 0xff:
        /* ignore that - I don't know what is its use */
        break;
    default:
        fprintf(stderr, "qemu: unsupported keyboard cmd=0x%02x\n", val);
        break;
    }
