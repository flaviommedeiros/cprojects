switch (cmd) {
	case TIOCLINUX:
		ret = tioclinux(tty, arg);
		break;
	case KIOCSOUND:
		if (!perm)
			goto eperm;
		/* FIXME: This is an old broken API but we need to keep it
		   supported and somehow separate the historic advertised
		   tick rate from any real one */
		if (arg)
			arg = CLOCK_TICK_RATE / arg;
		kd_mksound(arg, 0);
		break;

	case KDMKTONE:
		if (!perm)
			goto eperm;
	{
		unsigned int ticks, count;
		
		/*
		 * Generate the tone for the appropriate number of ticks.
		 * If the time is zero, turn off sound ourselves.
		 */
		ticks = HZ * ((arg >> 16) & 0xffff) / 1000;
		count = ticks ? (arg & 0xffff) : 0;
		/* FIXME: This is an old broken API but we need to keep it
		   supported and somehow separate the historic advertised
		   tick rate from any real one */
		if (count)
			count = CLOCK_TICK_RATE / count;
		kd_mksound(count, ticks);
		break;
	}

	case KDGKBTYPE:
		/*
		 * this is naive.
		 */
		ucval = KB_101;
		goto setchar;

		/*
		 * These cannot be implemented on any machine that implements
		 * ioperm() in user level (such as Alpha PCs) or not at all.
		 *
		 * XXX: you should never use these, just call ioperm directly..
		 */
#ifdef CONFIG_X86
	case KDADDIO:
	case KDDELIO:
		/*
		 * KDADDIO and KDDELIO may be able to add ports beyond what
		 * we reject here, but to be safe...
		 */
		if (arg < GPFIRST || arg > GPLAST) {
			ret = -EINVAL;
			break;
		}
		ret = sys_ioperm(arg, 1, (cmd == KDADDIO)) ? -ENXIO : 0;
		break;

	case KDENABIO:
	case KDDISABIO:
		ret = sys_ioperm(GPFIRST, GPNUM,
				  (cmd == KDENABIO)) ? -ENXIO : 0;
		break;
#endif

	/* Linux m68k/i386 interface for setting the keyboard delay/repeat rate */
		
	case KDKBDREP:
	{
		struct kbd_repeat kbrep;
		
		if (!capable(CAP_SYS_TTY_CONFIG))
			goto eperm;

		if (copy_from_user(&kbrep, up, sizeof(struct kbd_repeat))) {
			ret =  -EFAULT;
			break;
		}
		ret = kbd_rate(&kbrep);
		if (ret)
			break;
		if (copy_to_user(up, &kbrep, sizeof(struct kbd_repeat)))
			ret = -EFAULT;
		break;
	}

	case KDSETMODE:
		/*
		 * currently, setting the mode from KD_TEXT to KD_GRAPHICS
		 * doesn't do a whole lot. i'm not sure if it should do any
		 * restoration of modes or what...
		 *
		 * XXX It should at least call into the driver, fbdev's definitely
		 * need to restore their engine state. --BenH
		 */
		if (!perm)
			goto eperm;
		switch (arg) {
		case KD_GRAPHICS:
			break;
		case KD_TEXT0:
		case KD_TEXT1:
			arg = KD_TEXT;
		case KD_TEXT:
			break;
		default:
			ret = -EINVAL;
			goto out;
		}
		if (vc->vc_mode == (unsigned char) arg)
			break;
		vc->vc_mode = (unsigned char) arg;
		if (console != fg_console)
			break;
		/*
		 * explicitly blank/unblank the screen if switching modes
		 */
		acquire_console_sem();
		if (arg == KD_TEXT)
			do_unblank_screen(1);
		else
			do_blank_screen(1);
		release_console_sem();
		break;

	case KDGETMODE:
		ucval = vc->vc_mode;
		goto setint;

	case KDMAPDISP:
	case KDUNMAPDISP:
		/*
		 * these work like a combination of mmap and KDENABIO.
		 * this could be easily finished.
		 */
		ret = -EINVAL;
		break;

	case KDSKBMODE:
		if (!perm)
			goto eperm;
		switch(arg) {
		  case K_RAW:
			kbd->kbdmode = VC_RAW;
			break;
		  case K_MEDIUMRAW:
			kbd->kbdmode = VC_MEDIUMRAW;
			break;
		  case K_XLATE:
			kbd->kbdmode = VC_XLATE;
			compute_shiftstate();
			break;
		  case K_UNICODE:
			kbd->kbdmode = VC_UNICODE;
			compute_shiftstate();
			break;
		  default:
			ret = -EINVAL;
			goto out;
		}
		tty_ldisc_flush(tty);
		break;

	case KDGKBMODE:
		ucval = ((kbd->kbdmode == VC_RAW) ? K_RAW :
				 (kbd->kbdmode == VC_MEDIUMRAW) ? K_MEDIUMRAW :
				 (kbd->kbdmode == VC_UNICODE) ? K_UNICODE :
				 K_XLATE);
		goto setint;

	/* this could be folded into KDSKBMODE, but for compatibility
	   reasons it is not so easy to fold KDGKBMETA into KDGKBMODE */
	case KDSKBMETA:
		switch(arg) {
		  case K_METABIT:
			clr_vc_kbd_mode(kbd, VC_META);
			break;
		  case K_ESCPREFIX:
			set_vc_kbd_mode(kbd, VC_META);
			break;
		  default:
			ret = -EINVAL;
		}
		break;

	case KDGKBMETA:
		ucval = (vc_kbd_mode(kbd, VC_META) ? K_ESCPREFIX : K_METABIT);
	setint:
		ret = put_user(ucval, (int __user *)arg);
		break;

	case KDGETKEYCODE:
	case KDSETKEYCODE:
		if(!capable(CAP_SYS_TTY_CONFIG))
			perm = 0;
		ret = do_kbkeycode_ioctl(cmd, up, perm);
		break;

	case KDGKBENT:
	case KDSKBENT:
		ret = do_kdsk_ioctl(cmd, up, perm, kbd);
		break;

	case KDGKBSENT:
	case KDSKBSENT:
		ret = do_kdgkb_ioctl(cmd, up, perm);
		break;

	case KDGKBDIACR:
	{
		struct kbdiacrs __user *a = up;
		struct kbdiacr diacr;
		int i;

		if (put_user(accent_table_size, &a->kb_cnt)) {
			ret = -EFAULT;
			break;
		}
		for (i = 0; i < accent_table_size; i++) {
			diacr.diacr = conv_uni_to_8bit(accent_table[i].diacr);
			diacr.base = conv_uni_to_8bit(accent_table[i].base);
			diacr.result = conv_uni_to_8bit(accent_table[i].result);
			if (copy_to_user(a->kbdiacr + i, &diacr, sizeof(struct kbdiacr))) {
				ret = -EFAULT;
				break;
			}
		}
		break;
	}
	case KDGKBDIACRUC:
	{
		struct kbdiacrsuc __user *a = up;

		if (put_user(accent_table_size, &a->kb_cnt))
			ret = -EFAULT;
		else if (copy_to_user(a->kbdiacruc, accent_table,
				accent_table_size*sizeof(struct kbdiacruc)))
			ret = -EFAULT;
		break;
	}

	case KDSKBDIACR:
	{
		struct kbdiacrs __user *a = up;
		struct kbdiacr diacr;
		unsigned int ct;
		int i;

		if (!perm)
			goto eperm;
		if (get_user(ct,&a->kb_cnt)) {
			ret = -EFAULT;
			break;
		}
		if (ct >= MAX_DIACR) {
			ret = -EINVAL;
			break;
		}
		accent_table_size = ct;
		for (i = 0; i < ct; i++) {
			if (copy_from_user(&diacr, a->kbdiacr + i, sizeof(struct kbdiacr))) {
				ret = -EFAULT;
				break;
			}
			accent_table[i].diacr = conv_8bit_to_uni(diacr.diacr);
			accent_table[i].base = conv_8bit_to_uni(diacr.base);
			accent_table[i].result = conv_8bit_to_uni(diacr.result);
		}
		break;
	}

	case KDSKBDIACRUC:
	{
		struct kbdiacrsuc __user *a = up;
		unsigned int ct;

		if (!perm)
			goto eperm;
		if (get_user(ct,&a->kb_cnt)) {
			ret = -EFAULT;
			break;
		}
		if (ct >= MAX_DIACR) {
			ret = -EINVAL;
			break;
		}
		accent_table_size = ct;
		if (copy_from_user(accent_table, a->kbdiacruc, ct*sizeof(struct kbdiacruc)))
			ret = -EFAULT;
		break;
	}

	/* the ioctls below read/set the flags usually shown in the leds */
	/* don't use them - they will go away without warning */
	case KDGKBLED:
		ucval = kbd->ledflagstate | (kbd->default_ledflagstate << 4);
		goto setchar;

	case KDSKBLED:
		if (!perm)
			goto eperm;
		if (arg & ~0x77) {
			ret = -EINVAL;
			break;
		}
		kbd->ledflagstate = (arg & 7);
		kbd->default_ledflagstate = ((arg >> 4) & 7);
		set_leds();
		break;

	/* the ioctls below only set the lights, not the functions */
	/* for those, see KDGKBLED and KDSKBLED above */
	case KDGETLED:
		ucval = getledstate();
	setchar:
		ret = put_user(ucval, (char __user *)arg);
		break;

	case KDSETLED:
		if (!perm)
			goto eperm;
		setledstate(kbd, arg);
		break;

	/*
	 * A process can indicate its willingness to accept signals
	 * generated by pressing an appropriate key combination.
	 * Thus, one can have a daemon that e.g. spawns a new console
	 * upon a keypress and then changes to it.
	 * See also the kbrequest field of inittab(5).
	 */
	case KDSIGACCEPT:
	{
		if (!perm || !capable(CAP_KILL))
			goto eperm;
		if (!valid_signal(arg) || arg < 1 || arg == SIGKILL)
			ret = -EINVAL;
		else {
			spin_lock_irq(&vt_spawn_con.lock);
			put_pid(vt_spawn_con.pid);
			vt_spawn_con.pid = get_pid(task_pid(current));
			vt_spawn_con.sig = arg;
			spin_unlock_irq(&vt_spawn_con.lock);
		}
		break;
	}

	case VT_SETMODE:
	{
		struct vt_mode tmp;

		if (!perm)
			goto eperm;
		if (copy_from_user(&tmp, up, sizeof(struct vt_mode))) {
			ret = -EFAULT;
			goto out;
		}
		if (tmp.mode != VT_AUTO && tmp.mode != VT_PROCESS) {
			ret = -EINVAL;
			goto out;
		}
		acquire_console_sem();
		vc->vt_mode = tmp;
		/* the frsig is ignored, so we set it to 0 */
		vc->vt_mode.frsig = 0;
		put_pid(vc->vt_pid);
		vc->vt_pid = get_pid(task_pid(current));
		/* no switch is required -- saw@shade.msu.ru */
		vc->vt_newvt = -1;
		release_console_sem();
		break;
	}

	case VT_GETMODE:
	{
		struct vt_mode tmp;
		int rc;

		acquire_console_sem();
		memcpy(&tmp, &vc->vt_mode, sizeof(struct vt_mode));
		release_console_sem();

		rc = copy_to_user(up, &tmp, sizeof(struct vt_mode));
		if (rc)
			ret = -EFAULT;
		break;
	}

	/*
	 * Returns global vt state. Note that VT 0 is always open, since
	 * it's an alias for the current VT, and people can't use it here.
	 * We cannot return state for more than 16 VTs, since v_state is short.
	 */
	case VT_GETSTATE:
	{
		struct vt_stat __user *vtstat = up;
		unsigned short state, mask;

		if (put_user(fg_console + 1, &vtstat->v_active))
			ret = -EFAULT;
		else {
			state = 1;	/* /dev/tty0 is always open */
			for (i = 0, mask = 2; i < MAX_NR_CONSOLES && mask;
							++i, mask <<= 1)
				if (VT_IS_IN_USE(i))
					state |= mask;
			ret = put_user(state, &vtstat->v_state);
		}
		break;
	}

	/*
	 * Returns the first available (non-opened) console.
	 */
	case VT_OPENQRY:
		for (i = 0; i < MAX_NR_CONSOLES; ++i)
			if (! VT_IS_IN_USE(i))
				break;
		ucval = i < MAX_NR_CONSOLES ? (i+1) : -1;
		goto setint;		 

	/*
	 * ioctl(fd, VT_ACTIVATE, num) will cause us to switch to vt # num,
	 * with num >= 1 (switches to vt 0, our console, are not allowed, just
	 * to preserve sanity).
	 */
	case VT_ACTIVATE:
		if (!perm)
			goto eperm;
		if (arg == 0 || arg > MAX_NR_CONSOLES)
			ret =  -ENXIO;
		else {
			arg--;
			acquire_console_sem();
			ret = vc_allocate(arg);
			release_console_sem();
			if (ret)
				break;
			set_console(arg);
		}
		break;

	case VT_SETACTIVATE:
	{
		struct vt_setactivate vsa;

		if (!perm)
			goto eperm;

		if (copy_from_user(&vsa, (struct vt_setactivate __user *)arg,
					sizeof(struct vt_setactivate))) {
			ret = -EFAULT;
			goto out;
		}
		if (vsa.console == 0 || vsa.console > MAX_NR_CONSOLES)
			ret = -ENXIO;
		else {
			vsa.console--;
			acquire_console_sem();
			ret = vc_allocate(vsa.console);
			if (ret == 0) {
				struct vc_data *nvc;
				/* This is safe providing we don't drop the
				   console sem between vc_allocate and
				   finishing referencing nvc */
				nvc = vc_cons[vsa.console].d;
				nvc->vt_mode = vsa.mode;
				nvc->vt_mode.frsig = 0;
				put_pid(nvc->vt_pid);
				nvc->vt_pid = get_pid(task_pid(current));
			}
			release_console_sem();
			if (ret)
				break;
			/* Commence switch and lock */
			set_console(arg);
		}
	}

	/*
	 * wait until the specified VT has been activated
	 */
	case VT_WAITACTIVE:
		if (!perm)
			goto eperm;
		if (arg == 0 || arg > MAX_NR_CONSOLES)
			ret = -ENXIO;
		else
			ret = vt_waitactive(arg);
		break;

	/*
	 * If a vt is under process control, the kernel will not switch to it
	 * immediately, but postpone the operation until the process calls this
	 * ioctl, allowing the switch to complete.
	 *
	 * According to the X sources this is the behavior:
	 *	0:	pending switch-from not OK
	 *	1:	pending switch-from OK
	 *	2:	completed switch-to OK
	 */
	case VT_RELDISP:
		if (!perm)
			goto eperm;

		if (vc->vt_mode.mode != VT_PROCESS) {
			ret = -EINVAL;
			break;
		}
		/*
		 * Switching-from response
		 */
		acquire_console_sem();
		if (vc->vt_newvt >= 0) {
			if (arg == 0)
				/*
				 * Switch disallowed, so forget we were trying
				 * to do it.
				 */
				vc->vt_newvt = -1;

			else {
				/*
				 * The current vt has been released, so
				 * complete the switch.
				 */
				int newvt;
				newvt = vc->vt_newvt;
				vc->vt_newvt = -1;
				ret = vc_allocate(newvt);
				if (ret) {
					release_console_sem();
					break;
				}
				/*
				 * When we actually do the console switch,
				 * make sure we are atomic with respect to
				 * other console switches..
				 */
				complete_change_console(vc_cons[newvt].d);
			}
		} else {
			/*
			 * Switched-to response
			 */
			/*
			 * If it's just an ACK, ignore it
			 */
			if (arg != VT_ACKACQ)
				ret = -EINVAL;
		}
		release_console_sem();
		break;

	 /*
	  * Disallocate memory associated to VT (but leave VT1)
	  */
	 case VT_DISALLOCATE:
		if (arg > MAX_NR_CONSOLES) {
			ret = -ENXIO;
			break;
		}
		if (arg == 0) {
		    /* deallocate all unused consoles, but leave 0 */
			acquire_console_sem();
			for (i=1; i<MAX_NR_CONSOLES; i++)
				if (! VT_BUSY(i))
					vc_deallocate(i);
			release_console_sem();
		} else {
			/* deallocate a single console, if possible */
			arg--;
			if (VT_BUSY(arg))
				ret = -EBUSY;
			else if (arg) {			      /* leave 0 */
				acquire_console_sem();
				vc_deallocate(arg);
				release_console_sem();
			}
		}
		break;

	case VT_RESIZE:
	{
		struct vt_sizes __user *vtsizes = up;
		struct vc_data *vc;

		ushort ll,cc;
		if (!perm)
			goto eperm;
		if (get_user(ll, &vtsizes->v_rows) ||
		    get_user(cc, &vtsizes->v_cols))
			ret = -EFAULT;
		else {
			acquire_console_sem();
			for (i = 0; i < MAX_NR_CONSOLES; i++) {
				vc = vc_cons[i].d;

				if (vc) {
					vc->vc_resize_user = 1;
					vc_resize(vc_cons[i].d, cc, ll);
				}
			}
			release_console_sem();
		}
		break;
	}

	case VT_RESIZEX:
	{
		struct vt_consize __user *vtconsize = up;
		ushort ll,cc,vlin,clin,vcol,ccol;
		if (!perm)
			goto eperm;
		if (!access_ok(VERIFY_READ, vtconsize,
				sizeof(struct vt_consize))) {
			ret = -EFAULT;
			break;
		}
		/* FIXME: Should check the copies properly */
		__get_user(ll, &vtconsize->v_rows);
		__get_user(cc, &vtconsize->v_cols);
		__get_user(vlin, &vtconsize->v_vlin);
		__get_user(clin, &vtconsize->v_clin);
		__get_user(vcol, &vtconsize->v_vcol);
		__get_user(ccol, &vtconsize->v_ccol);
		vlin = vlin ? vlin : vc->vc_scan_lines;
		if (clin) {
			if (ll) {
				if (ll != vlin/clin) {
					/* Parameters don't add up */
					ret = -EINVAL;
					break;
				}
			} else 
				ll = vlin/clin;
		}
		if (vcol && ccol) {
			if (cc) {
				if (cc != vcol/ccol) {
					ret = -EINVAL;
					break;
				}
			} else
				cc = vcol/ccol;
		}

		if (clin > 32) {
			ret =  -EINVAL;
			break;
		}
		    
		for (i = 0; i < MAX_NR_CONSOLES; i++) {
			if (!vc_cons[i].d)
				continue;
			acquire_console_sem();
			if (vlin)
				vc_cons[i].d->vc_scan_lines = vlin;
			if (clin)
				vc_cons[i].d->vc_font.height = clin;
			vc_cons[i].d->vc_resize_user = 1;
			vc_resize(vc_cons[i].d, cc, ll);
			release_console_sem();
		}
		break;
	}

	case PIO_FONT: {
		if (!perm)
			goto eperm;
		op.op = KD_FONT_OP_SET;
		op.flags = KD_FONT_FLAG_OLD | KD_FONT_FLAG_DONT_RECALC;	/* Compatibility */
		op.width = 8;
		op.height = 0;
		op.charcount = 256;
		op.data = up;
		ret = con_font_op(vc_cons[fg_console].d, &op);
		break;
	}

	case GIO_FONT: {
		op.op = KD_FONT_OP_GET;
		op.flags = KD_FONT_FLAG_OLD;
		op.width = 8;
		op.height = 32;
		op.charcount = 256;
		op.data = up;
		ret = con_font_op(vc_cons[fg_console].d, &op);
		break;
	}

	case PIO_CMAP:
                if (!perm)
			ret = -EPERM;
		else
	                ret = con_set_cmap(up);
		break;

	case GIO_CMAP:
                ret = con_get_cmap(up);
		break;

	case PIO_FONTX:
	case GIO_FONTX:
		ret = do_fontx_ioctl(cmd, up, perm, &op);
		break;

	case PIO_FONTRESET:
	{
		if (!perm)
			goto eperm;

#ifdef BROKEN_GRAPHICS_PROGRAMS
		/* With BROKEN_GRAPHICS_PROGRAMS defined, the default
		   font is not saved. */
		ret = -ENOSYS;
		break;
#else
		{
		op.op = KD_FONT_OP_SET_DEFAULT;
		op.data = NULL;
		ret = con_font_op(vc_cons[fg_console].d, &op);
		if (ret)
			break;
		con_set_default_unimap(vc_cons[fg_console].d);
		break;
		}
#endif
	}

	case KDFONTOP: {
		if (copy_from_user(&op, up, sizeof(op))) {
			ret = -EFAULT;
			break;
		}
		if (!perm && op.op != KD_FONT_OP_GET)
			goto eperm;
		ret = con_font_op(vc, &op);
		if (ret)
			break;
		if (copy_to_user(up, &op, sizeof(op)))
			ret = -EFAULT;
		break;
	}

	case PIO_SCRNMAP:
		if (!perm)
			ret = -EPERM;
		else
			ret = con_set_trans_old(up);
		break;

	case GIO_SCRNMAP:
		ret = con_get_trans_old(up);
		break;

	case PIO_UNISCRNMAP:
		if (!perm)
			ret = -EPERM;
		else
			ret = con_set_trans_new(up);
		break;

	case GIO_UNISCRNMAP:
		ret = con_get_trans_new(up);
		break;

	case PIO_UNIMAPCLR:
	      { struct unimapinit ui;
		if (!perm)
			goto eperm;
		ret = copy_from_user(&ui, up, sizeof(struct unimapinit));
		if (!ret)
			con_clear_unimap(vc, &ui);
		break;
	      }

	case PIO_UNIMAP:
	case GIO_UNIMAP:
		ret = do_unimap_ioctl(cmd, up, perm, vc);
		break;

	case VT_LOCKSWITCH:
		if (!capable(CAP_SYS_TTY_CONFIG))
			goto eperm;
		vt_dont_switch = 1;
		break;
	case VT_UNLOCKSWITCH:
		if (!capable(CAP_SYS_TTY_CONFIG))
			goto eperm;
		vt_dont_switch = 0;
		break;
	case VT_GETHIFONTMASK:
		ret = put_user(vc->vc_hi_font_mask,
					(unsigned short __user *)arg);
		break;
	case VT_WAITEVENT:
		ret = vt_event_wait_ioctl((struct vt_event __user *)arg);
		break;
	default:
		ret = -ENOIOCTLCMD;
	}
