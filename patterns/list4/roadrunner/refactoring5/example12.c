#ifdef TCC_ARM_EABI
if(!(align & 7))
                vpush_global_sym(&func_old_type, TOK_memcpy8);
            else if(!(align & 3))
                vpush_global_sym(&func_old_type, TOK_memcpy4);
            else
#endif
            vpush_global_sym(&func_old_type, TOK_memcpy);
