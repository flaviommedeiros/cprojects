switch(node->unode.opr.type) {
                    case OPR_SET:           commit_set(node); break;
                    case OPR_PLUS_EQ:       commit_plus_eq(node); break;
                    case OPR_SUB_EQ:        commit_sub_eq(node); break;
                    case OPR_MUL_EQ:        commit_mul_eq(node); break;
                    case OPR_DIV_EQ:        commit_div_eq(node); break;
                    case OPR_IF:            commit_if(node); break;
                    case OPR_WHILE:         commit_while(node); break;
                    case OPR_BLOCK:         commit_block(node); break;
                    case OPR_FUNC_INTRO:    commit_function_intro(node); break;
                    case OPR_FUNC_OUTRO:    commit_function_outro(node); break;
                    case OPR_CALL:          commit_call(node); break;
                    case OPR_EXT_CALL:      commit_ext_call(node); break;
                    case OPR_EQU:           commit_equ(node); break;
                    case OPR_LOW:           commit_low(node); break;
                    case OPR_NOT:           commit_not(node); break;
                    case OPR_AFFECT_LIST:   commit_affect_list(node); break;
                    case OPR_FOREACH:       commit_foreach(node); break;
                    case OPR_VAR_LIST:      commit_var_list(node); break;
#ifdef VERBOSE
                    case EMPTY_NODE:        printf("NOP\n"); break;
#endif
                }
