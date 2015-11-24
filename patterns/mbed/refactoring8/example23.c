status_code dac_chan_write_buffer_wait(
    struct dac_module *const module_inst,
    enum dac_channel channel,
    uint16_t *buffer,
    uint32_t length)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);

    Dac *const dac_module = module_inst->hw;

    while (dac_is_syncing(module_inst)) {
        /* Wait until the synchronization is complete */
    }

    /* Zero length request */
    if (length == 0) {
        /* No data to be converted */
        return STATUS_OK;
    }

#if DAC_CALLBACK_MODE == true
    /* Check if busy */
    if (module_inst->job_status[channel] == STATUS_BUSY) {
        return STATUS_BUSY;
    }
#endif

    /* Only support event triggered conversion */
    if (module_inst->start_on_event[channel] == false) {
        return STATUS_ERR_UNSUPPORTED_DEV;
    }

    /* Blocks while buffer is being transferred */
    while (length--) {
        /* Convert one data */
        dac_chan_write(module_inst, channel, buffer[length]);

        /* Wait until Transmit is complete or timeout */
        for (uint32_t i = 0; i <= DAC_TIMEOUT; i++) {
            if(channel == DAC_CHANNEL_0) {
                if (dac_module->INTFLAG.reg & DAC_INTFLAG_EMPTY0) {
                    break;
                } else if (i == DAC_TIMEOUT) {
                    return STATUS_ERR_TIMEOUT;
                }
            } else if(channel == DAC_CHANNEL_1) {
                if (dac_module->INTFLAG.reg & DAC_INTFLAG_EMPTY1) {
                    break;
                } else if (i == DAC_TIMEOUT) {
                    return STATUS_ERR_TIMEOUT;
                }
            }
        }
    }

    return STATUS_OK;
}
