#ifndef HCI_LINK_CONTROL
if (m_tx_fsm_idle_flag && m_hci_global_enable_flag && tx_queue_length)
#else
    if (m_tx_fsm_idle_flag && m_hci_global_enable_flag && tx_queue_length && (m_hci_mode == HCI_MODE_ACTIVE))
#endif /* HCI_LINK_CONTROL */
    {
        tx_exec_flag       = true;  // FSM should be activated
        m_tx_fsm_idle_flag = false; // FSM will be busy from now on till the queue is exhausted
    }
