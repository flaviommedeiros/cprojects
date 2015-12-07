#ifdef MODE32
if (state->Bank > 0)
    {
      state->Cpsr = state->Spsr[state->Bank];
      ARMul_CPSRAltered (state);
    }
