if (__put_user(to_user_ptr(ka->sa.sa_handler), &sc->handler)
	    || __put_user(oldset->sig[0], &sc->oldmask)
#ifdef CONFIG_PPC64
	    || __put_user((oldset->sig[0] >> 32), &sc->_unused[3])
#else
	    || __put_user(oldset->sig[1], &sc->_unused[3])
#endif
	    || __put_user(to_user_ptr(&frame->mctx), &sc->regs)
	    || __put_user(sig, &sc->signal))
		goto badframe;
