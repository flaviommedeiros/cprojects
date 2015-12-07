if (addr == (addr_t) &dummy->regs.psw.mask &&
#ifdef CONFIG_COMPAT
		    data != PSW_MASK_MERGE(psw_user32_bits, data) &&
#endif
		    data != PSW_MASK_MERGE(psw_user_bits, data))
			/* Invalid psw mask. */
			return -EINVAL;
