#ifndef MODE32
if (VECTORACCESS (temp)
					    || ADDREXCEPT (temp)) {
						INTERNALABORT (temp);
						(void) ARMul_LoadByte (state,
								       temp);
						(void) ARMul_LoadByte (state,
								       temp);
					}
					else
#endif
						DEST = ARMul_SwapByte (state,
								       temp,
								       state->
								       Reg
								       [RHSReg]);
