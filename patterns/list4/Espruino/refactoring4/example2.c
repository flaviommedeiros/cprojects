#ifndef HCI_LINK_CONTROL
if (m_rx_fsm_idle_flag && m_hci_global_enable_flag && rx_queue_length)
#else
    if (m_rx_fsm_idle_flag && m_hci_global_enable_flag && rx_queue_length && (m_hci_mode == HCI_MODE_ACTIVE))
#endif /* HCI_LINK_CONTROL */
    {
        rx_exec_flag       = true;  // FSM should be activated
        m_rx_fsm_idle_flag = false; // FSM will be busy from now on till the queue is exhausted
    }
