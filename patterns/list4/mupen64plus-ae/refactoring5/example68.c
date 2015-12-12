#ifdef NEW_DYNAREC
if (r4300emu == CORE_DYNAREC)
        {
            invalidate_cached_code_new_dynarec(address, size);
        }
        else
#endif
        {
            invalidate_cached_code_hacktarux(address, size);
        }
