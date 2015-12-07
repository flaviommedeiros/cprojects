if (
#ifdef MVM_USE_OVERFLOW_SERIALIZATION_INDEX
                            !(col->flags & MVM_CF_SERIALZATION_INDEX_ALLOCATED) &&
#endif
                            col->sc_forward_u.sc.sc_idx == 0
                            && col->sc_forward_u.sc.idx == MVM_DIRECT_SC_IDX_SENTINEL) {
                            /* We marked it dead last time, kill it. */
                            MVM_6model_stable_gc_free(tc, (MVMSTable *)col);
                        }
                        else {
#ifdef MVM_USE_OVERFLOW_SERIALIZATION_INDEX
                            if (col->flags & MVM_CF_SERIALZATION_INDEX_ALLOCATED) {
                                /* Whatever happens next, we can free this
                                   memory immediately, because no-one will be
                                   serializing a dead STable. */
                                assert(!(col->sc_forward_u.sci->sc_idx == 0
                                         && col->sc_forward_u.sci->idx
                                         == MVM_DIRECT_SC_IDX_SENTINEL));
                                MVM_free(col->sc_forward_u.sci);
                                col->flags &= ~MVM_CF_SERIALZATION_INDEX_ALLOCATED;
                            }
#endif
                            if (global_destruction) {
                                /* We're in global destruction, so enqueue to the end
                                 * like we do in the nursery */
                                MVM_gc_collect_enqueue_stable_for_deletion(tc, (MVMSTable *)col);
                            } else {
                                /* There will definitely be another gc run, so mark it as "died last time". */
                                col->sc_forward_u.sc.sc_idx = 0;
                                col->sc_forward_u.sc.idx = MVM_DIRECT_SC_IDX_SENTINEL;
                            }
                            /* Skip the freelist updating. */
                            cur_ptr += obj_size;
                            continue;
                        }
