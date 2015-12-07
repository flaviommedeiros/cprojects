#ifdef RLD_TRANS_DEBUGx
if (1 || log_level >= LOG_MONITOR2)
#else
    if (log_level >= LOG_MONITOR2)
#endif
    {
        pr_info("++ start_xmt[%d]: state %x start %x full %d free %d required %d stopped %x\n",
                channum, ch->state, ch->ch_start_tx, ch->tx_full,
                ch->txd_free, ch->txd_required, sd_queue_stopped (ch->user));
    }
