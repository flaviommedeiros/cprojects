if ((tpe->flags & GTP_ENTRY_FLAGS_IS_KRETPROBE)
		    && (tpe->step || tpe->type != gtp_entry_kprobe
#ifdef CONFIG_X86
		    || gtp_have_step)) {
#else
		    )
