#ifndef MODE32
if (base == 15)
		/* Now forbidden, but ...  */
		base = ECC | ER15INT | R15PC | EMODE;
	else
#endif
		base = state->Reg[base];
