long long
do_state_transition(long long actions,
                    enum crmd_fsa_state cur_state,
                    enum crmd_fsa_state next_state, fsa_data_t * msg_data)
{
    int level = LOG_INFO;
    long long tmp = actions;
    gboolean clear_recovery_bit = TRUE;

    enum crmd_fsa_cause cause = msg_data->fsa_cause;
    enum crmd_fsa_input current_input = msg_data->fsa_input;

    const char *state_from = fsa_state2string(cur_state);
    const char *state_to = fsa_state2string(next_state);
    const char *input = fsa_input2string(current_input);

    CRM_LOG_ASSERT(cur_state != next_state);

    do_dot_log(DOT_PREFIX "\t%s -> %s [ label=%s cause=%s origin=%s ]",
               state_from, state_to, input, fsa_cause2string(cause), msg_data->origin);

    if (cur_state == S_IDLE || next_state == S_IDLE) {
        level = LOG_NOTICE;
    } else if (cur_state == S_NOT_DC || next_state == S_NOT_DC) {
        level = LOG_NOTICE;
    } else if (cur_state == S_ELECTION) {
        level = LOG_NOTICE;
    } else if (cur_state == S_STARTING) {
        level = LOG_NOTICE;
    } else if (next_state == S_RECOVERY) {
        level = LOG_WARNING;
    }

    do_crm_log(level, "State transition %s -> %s [ input=%s cause=%s origin=%s ]",
               state_from, state_to, input, fsa_cause2string(cause), msg_data->origin);

    /* the last two clauses might cause trouble later */
    if (next_state != S_ELECTION && cur_state != S_RELEASE_DC) {
        election_timeout_stop(fsa_election);
/* 	} else { */
/* 		crm_timer_start(election_timeout); */
    }
#if 0
    if ((fsa_input_register & R_SHUTDOWN)) {
        set_bit(tmp, A_DC_TIMER_STOP);
    }
#endif
    if (next_state == S_INTEGRATION) {
        set_bit(tmp, A_INTEGRATE_TIMER_START);
    } else {
        set_bit(tmp, A_INTEGRATE_TIMER_STOP);
    }

    if (next_state == S_FINALIZE_JOIN) {
        set_bit(tmp, A_FINALIZE_TIMER_START);
    } else {
        set_bit(tmp, A_FINALIZE_TIMER_STOP);
    }

    if (next_state != S_PENDING) {
        set_bit(tmp, A_DC_TIMER_STOP);
    }
    if (next_state != S_ELECTION) {
        highest_born_on = 0;
    }
    if (next_state != S_IDLE) {
        crm_timer_stop(recheck_timer);
    }

    if (cur_state == S_FINALIZE_JOIN && next_state == S_POLICY_ENGINE) {
        populate_cib_nodes(node_update_quick|node_update_all, __FUNCTION__);
    }

    switch (next_state) {
        case S_PENDING:
            fsa_cib_conn->cmds->set_slave(fsa_cib_conn, cib_scope_local);
            /* fall through */
        case S_ELECTION:
            crm_trace("Resetting our DC to NULL on transition to %s", fsa_state2string(next_state));
            update_dc(NULL);
            break;
        case S_NOT_DC:
            election_trigger->counter = 0;
            purge_stonith_cleanup();

            if (is_set(fsa_input_register, R_SHUTDOWN)) {
                crm_info("(Re)Issuing shutdown request now" " that we have a new DC");
                set_bit(tmp, A_SHUTDOWN_REQ);
            }
            CRM_LOG_ASSERT(fsa_our_dc != NULL);
            if (fsa_our_dc == NULL) {
                crm_err("Reached S_NOT_DC without a DC" " being recorded");
            }
            break;
        case S_RECOVERY:
            clear_recovery_bit = FALSE;
            break;

        case S_FINALIZE_JOIN:
            CRM_LOG_ASSERT(AM_I_DC);
            if (cause == C_TIMER_POPPED) {
                crm_warn("Progressed to state %s after %s",
                         fsa_state2string(next_state), fsa_cause2string(cause));
            }
            if (crmd_join_phase_count(crm_join_welcomed) > 0) {
                crm_warn("%u cluster nodes failed to respond"
                         " to the join offer.", crmd_join_phase_count(crm_join_welcomed));
                crmd_join_phase_log(LOG_NOTICE);

            } else {
                crm_debug("All %d cluster nodes responded to the join offer.",
                          crmd_join_phase_count(crm_join_integrated));
            }
            break;

        case S_POLICY_ENGINE:
            election_trigger->counter = 0;
            CRM_LOG_ASSERT(AM_I_DC);
            if (cause == C_TIMER_POPPED) {
                crm_info("Progressed to state %s after %s",
                         fsa_state2string(next_state), fsa_cause2string(cause));
            }

            if (crmd_join_phase_count(crm_join_finalized) > 0) {
                crm_err("%u cluster nodes failed to confirm their join.",
                        crmd_join_phase_count(crm_join_finalized));
                crmd_join_phase_log(LOG_NOTICE);

            } else if (crmd_join_phase_count(crm_join_confirmed)
                       == crm_active_peers()) {
                crm_debug("All %u cluster nodes are"
                          " eligible to run resources.", crm_active_peers());

            } else if (crmd_join_phase_count(crm_join_confirmed) > crm_active_peers()) {
                crm_err("We have more confirmed nodes than our membership does: %d vs. %d",
                        crmd_join_phase_count(crm_join_confirmed), crm_active_peers());
                register_fsa_input(C_FSA_INTERNAL, I_ELECTION, NULL);

            } else if (saved_ccm_membership_id != crm_peer_seq) {
                crm_info("Membership changed: %llu -> %llu - join restart",
                         saved_ccm_membership_id, crm_peer_seq);
                register_fsa_input_before(C_FSA_INTERNAL, I_NODE_JOIN, NULL);

            } else {
                crm_warn("Only %u of %u cluster "
                         "nodes are eligible to run resources - continue %d",
                         crmd_join_phase_count(crm_join_confirmed),
                         crm_active_peers(), crmd_join_phase_count(crm_join_welcomed));
            }
/* 			initialize_join(FALSE); */
            break;

        case S_STOPPING:
        case S_TERMINATE:
            /* possibly redundant */
            set_bit(fsa_input_register, R_SHUTDOWN);
            break;

        case S_IDLE:
            CRM_LOG_ASSERT(AM_I_DC);
            dump_rsc_info();
            if (is_set(fsa_input_register, R_SHUTDOWN)) {
                crm_info("(Re)Issuing shutdown request now" " that we are the DC");
                set_bit(tmp, A_SHUTDOWN_REQ);
            }
            if (recheck_timer->period_ms > 0) {
                crm_debug("Starting %s", get_timer_desc(recheck_timer));
                crm_timer_start(recheck_timer);
            }
            break;

        default:
            break;
    }

    if (clear_recovery_bit && next_state != S_PENDING) {
        tmp &= ~A_RECOVER;
    } else if (clear_recovery_bit == FALSE) {
        tmp |= A_RECOVER;
    }

    if (tmp != actions) {
        /* fsa_dump_actions(actions ^ tmp, "New actions"); */
        actions = tmp;
    }

    return actions;
}
