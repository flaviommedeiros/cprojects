static tile_bundle_bits rewrite_load_store_unaligned(
	struct single_step_state *state,
	tile_bundle_bits bundle,
	struct pt_regs *regs,
	enum mem_op mem_op,
	int size, int sign_ext)
{
	unsigned char __user *addr;
	int val_reg, addr_reg, err, val;

	/* Get address and value registers */
	if (bundle & TILEPRO_BUNDLE_Y_ENCODING_MASK) {
		addr_reg = get_SrcA_Y2(bundle);
		val_reg = get_SrcBDest_Y2(bundle);
	} else if (mem_op == MEMOP_LOAD || mem_op == MEMOP_LOAD_POSTINCR) {
		addr_reg = get_SrcA_X1(bundle);
		val_reg  = get_Dest_X1(bundle);
	} else {
		addr_reg = get_SrcA_X1(bundle);
		val_reg  = get_SrcB_X1(bundle);
	}

	/*
	 * If registers are not GPRs, don't try to handle it.
	 *
	 * FIXME: we could handle non-GPR loads by getting the real value
	 * from memory, writing it to the single step buffer, using a
	 * temp_reg to hold a pointer to that memory, then executing that
	 * instruction and resetting temp_reg.  For non-GPR stores, it's a
	 * little trickier; we could use the single step buffer for that
	 * too, but we'd have to add some more state bits so that we could
	 * call back in here to copy that value to the real target.  For
	 * now, we just handle the simple case.
	 */
	if ((val_reg >= PTREGS_NR_GPRS &&
	     (val_reg != TREG_ZERO ||
	      mem_op == MEMOP_LOAD ||
	      mem_op == MEMOP_LOAD_POSTINCR)) ||
	    addr_reg >= PTREGS_NR_GPRS)
		return bundle;

	/* If it's aligned, don't handle it specially */
	addr = (void __user *)regs->regs[addr_reg];
	if (((unsigned long)addr % size) == 0)
		return bundle;

	/*
	 * Return SIGBUS with the unaligned address, if requested.
	 * Note that we return SIGBUS even for completely invalid addresses
	 * as long as they are in fact unaligned; this matches what the
	 * tilepro hardware would be doing, if it could provide us with the
	 * actual bad address in an SPR, which it doesn't.
	 */
	if (unaligned_fixup == 0) {
		siginfo_t info = {
			.si_signo = SIGBUS,
			.si_code = BUS_ADRALN,
			.si_addr = addr
		};
		trace_unhandled_signal("unaligned trap", regs,
				       (unsigned long)addr, SIGBUS);
		force_sig_info(info.si_signo, &info, current);
		return (tilepro_bundle_bits) 0;
	}

#ifndef __LITTLE_ENDIAN
# error We assume little-endian representation with copy_xx_user size 2 here
#endif
	/* Handle unaligned load/store */
	if (mem_op == MEMOP_LOAD || mem_op == MEMOP_LOAD_POSTINCR) {
		unsigned short val_16;
		switch (size) {
		case 2:
			err = copy_from_user(&val_16, addr, sizeof(val_16));
			val = sign_ext ? ((short)val_16) : val_16;
			break;
		case 4:
			err = copy_from_user(&val, addr, sizeof(val));
			break;
		default:
			BUG();
		}
		if (err == 0) {
			state->update_reg = val_reg;
			state->update_value = val;
			state->update = 1;
		}
	} else {
		val = (val_reg == TREG_ZERO) ? 0 : regs->regs[val_reg];
		err = copy_to_user(addr, &val, size);
	}

	if (err) {
		siginfo_t info = {
			.si_signo = SIGSEGV,
			.si_code = SEGV_MAPERR,
			.si_addr = addr
		};
		trace_unhandled_signal("segfault", regs,
				       (unsigned long)addr, SIGSEGV);
		force_sig_info(info.si_signo, &info, current);
		return (tile_bundle_bits) 0;
	}

	if (unaligned_printk || unaligned_fixup_count == 0) {
		pr_info("Process %d/%s: PC %#lx: Fixup of"
			" unaligned %s at %#lx.\n",
			current->pid, current->comm, regs->pc,
			(mem_op == MEMOP_LOAD ||
			 mem_op == MEMOP_LOAD_POSTINCR) ?
			"load" : "store",
			(unsigned long)addr);
		if (!unaligned_printk) {
#define P pr_info
P("\n");
P("Unaligned fixups in the kernel will slow your application considerably.\n");
P("To find them, write a \"1\" to /proc/sys/tile/unaligned_fixup/printk,\n");
P("which requests the kernel show all unaligned fixups, or write a \"0\"\n");
P("to /proc/sys/tile/unaligned_fixup/enabled, in which case each unaligned\n");
P("access will become a SIGBUS you can debug. No further warnings will be\n");
P("shown so as to avoid additional slowdown, but you can track the number\n");
P("of fixups performed via /proc/sys/tile/unaligned_fixup/count.\n");
P("Use the tile-addr2line command (see \"info addr2line\") to decode PCs.\n");
P("\n");
#undef P
		}
	}
	++unaligned_fixup_count;

	if (bundle & TILEPRO_BUNDLE_Y_ENCODING_MASK) {
		/* Convert the Y2 instruction to a prefetch. */
		bundle &= ~(create_SrcBDest_Y2(-1) |
			    create_Opcode_Y2(-1));
		bundle |= (create_SrcBDest_Y2(TREG_ZERO) |
			   create_Opcode_Y2(LW_OPCODE_Y2));
	/* Replace the load postincr with an addi */
	} else if (mem_op == MEMOP_LOAD_POSTINCR) {
		bundle = addi_X1(bundle, addr_reg, addr_reg,
				 get_Imm8_X1(bundle));
	/* Replace the store postincr with an addi */
	} else if (mem_op == MEMOP_STORE_POSTINCR) {
		bundle = addi_X1(bundle, addr_reg, addr_reg,
				 get_Dest_Imm8_X1(bundle));
	} else {
		/* Convert the X1 instruction to a nop. */
		bundle &= ~(create_Opcode_X1(-1) |
			    create_UnShOpcodeExtension_X1(-1) |
			    create_UnOpcodeExtension_X1(-1));
		bundle |= (create_Opcode_X1(SHUN_0_OPCODE_X1) |
			   create_UnShOpcodeExtension_X1(
				   UN_0_SHUN_0_OPCODE_X1) |
			   create_UnOpcodeExtension_X1(
				   NOP_UN_0_SHUN_0_OPCODE_X1));
	}

	return bundle;
}
