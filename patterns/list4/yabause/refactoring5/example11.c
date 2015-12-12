#ifndef Q68_DISABLE_ADDRESS_ERROR
if (state->ea_addr & 1) {
                state->exception = EX_ADDRESS_ERROR;
                state->fault_addr = state->ea_addr;
                state->fault_status = FAULT_STATUS_IN_DATA
                                    | FAULT_STATUS_RW_WRITE;
                return;
            } else
#endif
            if (size == SIZE_W) {
                WRITE16(state, state->ea_addr, data);
            } else {
                WRITE32(state, state->ea_addr, data);
            }
