switch(ot) {
            case OT_BYTE:
                gen_op_mov_TN_reg(OT_BYTE, 1, R_EAX);
                tcg_gen_ext8u_tl(cpu_T[0], cpu_T[0]);
                tcg_gen_ext8u_tl(cpu_T[1], cpu_T[1]);
                /* XXX: use 32 bit mul which could be faster */
                tcg_gen_mul_tl(cpu_T[0], cpu_T[0], cpu_T[1]);
                gen_op_mov_reg_T0(OT_WORD, R_EAX);
                tcg_gen_mov_tl(cpu_cc_dst, cpu_T[0]);
                tcg_gen_andi_tl(cpu_cc_src, cpu_T[0], 0xff00);
                s->cc_op = CC_OP_MULB;
                break;
            case OT_WORD:
                gen_op_mov_TN_reg(OT_WORD, 1, R_EAX);
                tcg_gen_ext16u_tl(cpu_T[0], cpu_T[0]);
                tcg_gen_ext16u_tl(cpu_T[1], cpu_T[1]);
                /* XXX: use 32 bit mul which could be faster */
                tcg_gen_mul_tl(cpu_T[0], cpu_T[0], cpu_T[1]);
                gen_op_mov_reg_T0(OT_WORD, R_EAX);
                tcg_gen_mov_tl(cpu_cc_dst, cpu_T[0]);
                tcg_gen_shri_tl(cpu_T[0], cpu_T[0], 16);
                gen_op_mov_reg_T0(OT_WORD, R_EDX);
                tcg_gen_mov_tl(cpu_cc_src, cpu_T[0]);
                s->cc_op = CC_OP_MULW;
                break;
            default:
            case OT_LONG:
#ifdef TARGET_X86_64
                gen_op_mov_TN_reg(OT_LONG, 1, R_EAX);
                tcg_gen_ext32u_tl(cpu_T[0], cpu_T[0]);
                tcg_gen_ext32u_tl(cpu_T[1], cpu_T[1]);
                tcg_gen_mul_tl(cpu_T[0], cpu_T[0], cpu_T[1]);
                gen_op_mov_reg_T0(OT_LONG, R_EAX);
                tcg_gen_mov_tl(cpu_cc_dst, cpu_T[0]);
                tcg_gen_shri_tl(cpu_T[0], cpu_T[0], 32);
                gen_op_mov_reg_T0(OT_LONG, R_EDX);
                tcg_gen_mov_tl(cpu_cc_src, cpu_T[0]);
#else
                {
                    TCGv_i64 t0, t1;
                    t0 = tcg_temp_new_i64();
                    t1 = tcg_temp_new_i64();
                    gen_op_mov_TN_reg(OT_LONG, 1, R_EAX);
                    tcg_gen_extu_i32_i64(t0, cpu_T[0]);
                    tcg_gen_extu_i32_i64(t1, cpu_T[1]);
                    tcg_gen_mul_i64(t0, t0, t1);
                    tcg_gen_trunc_i64_i32(cpu_T[0], t0);
                    gen_op_mov_reg_T0(OT_LONG, R_EAX);
                    tcg_gen_mov_tl(cpu_cc_dst, cpu_T[0]);
                    tcg_gen_shri_i64(t0, t0, 32);
                    tcg_gen_trunc_i64_i32(cpu_T[0], t0);
                    gen_op_mov_reg_T0(OT_LONG, R_EDX);
                    tcg_gen_mov_tl(cpu_cc_src, cpu_T[0]);
                }
#endif
                s->cc_op = CC_OP_MULL;
                break;
#ifdef TARGET_X86_64
            case OT_QUAD:
                gen_helper_mulq_EAX_T0(cpu_T[0]);
                s->cc_op = CC_OP_MULQ;
                break;
#endif
            }
