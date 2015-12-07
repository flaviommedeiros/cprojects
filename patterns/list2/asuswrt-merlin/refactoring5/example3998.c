#ifndef MODE32
if (VECTORACCESS (temp) || ADDREXCEPT (temp))
		    {
		      INTERNALABORT (temp);
		      (void) ARMul_LoadWordN (state, temp);
		      (void) ARMul_LoadWordN (state, temp);
		    }
		  else
#endif
		    dest = ARMul_SwapWord (state, temp, state->Reg[RHSReg]);
