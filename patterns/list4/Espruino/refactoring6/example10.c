if ((m_clock_cb.hfclk_requests > 0)
#if CLOCK_CONFIG_LF_SRC == NRF_CLOCK_LF_SRC_Synth
        || (m_clock_cb.lfclk_requests > 0)
#elif CLOCK_CONFIG_LF_SRC == NRF_CLOCK_LF_SRC_RC
        || (m_clock_cb.calibration_in_progress == true)
#endif
        )
    {
        if ((nrf_clock_hf_src_get() != NRF_CLOCK_HF_SRC_Xtal)
            && (nrf_clock_hf_start_task_status_get() == NRF_CLOCK_START_TASK_NOT_TRIGGERED))
        {
            result = true;

            if (interrupt_enable)
            {
                nrf_clock_int_enable(NRF_CLOCK_INT_HF_STARTED_MASK);
            }
            hfclk_start();
        }
    }
    else
    {
        if ((nrf_clock_hf_src_get() == NRF_CLOCK_HF_SRC_Xtal) 
            || (nrf_clock_hf_start_task_status_get() == NRF_CLOCK_START_TASK_TRIGGERED))
        {
            hfclk_stop();
        }
    }
