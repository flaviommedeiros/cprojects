switch (m_hci_tx_fsm_state)
    {
        case HCI_TX_STATE_SEND:

            if ((p_event->evt_source == HCI_SER_PHY_EVT) &&
                (p_event->evt.ser_phy_evt.evt_type == HCI_SER_PHY_TX_REQUEST))
            {
                hci_pkt_send();
                hci_timeout_setup(0);
                m_tx_retry_count   = MAX_RETRY_COUNT;
                m_hci_tx_fsm_state = HCI_TX_STATE_WAIT_FOR_FIRST_TX_END;
            }
            else if ((p_event->evt_source == HCI_SLIP_EVT) &&
                     (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                hci_process_orphaned_ack(p_event);
            }

            break;

        case HCI_TX_STATE_WAIT_FOR_FIRST_TX_END:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_SENT))
            {
                hci_timeout_setup(1);
                m_hci_tx_fsm_state = HCI_TX_STATE_WAIT_FOR_ACK;
            }
            else if ((p_event->evt_source == HCI_SLIP_EVT) &&
                     (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                hci_process_orphaned_ack(p_event);
            }
            break;

        case HCI_TX_STATE_WAIT_FOR_ACK_OR_TX_END:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_SENT))
            {
                hci_timeout_setup(1);
                m_hci_tx_fsm_state = HCI_TX_STATE_WAIT_FOR_ACK;
            }
            else if ((p_event->evt_source == HCI_SLIP_EVT) &&
                     (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                if (rx_ack_pkt_valid(p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer))
                {
                    hci_timeout_setup(0);
                    m_hci_tx_fsm_state = HCI_TX_STATE_WAIT_FOR_TX_END;
                }
                hci_release_ack_buffer(p_event);
            }
            break;

        case HCI_TX_STATE_WAIT_FOR_ACK:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                if (rx_ack_pkt_valid(p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer))
                {
                    hci_timeout_setup(0);
                    hci_pkt_sent_upcall();
                    m_hci_tx_fsm_state = HCI_TX_STATE_SEND;
                }
                hci_release_ack_buffer(p_event);
            }
            else if (p_event->evt_source == HCI_TIMER_EVT)
            {
                m_tx_retry_count--;
                // m_tx_retx_counter++; // global retransmissions counter
                if (m_tx_retry_count)
                {
                    hci_pkt_send();
                    DEBUG_HCI_RETX(0);
                    m_hci_tx_fsm_state = HCI_TX_STATE_WAIT_FOR_ACK_OR_TX_END;
                }
                else
                {
                    error_callback();
                    m_hci_tx_fsm_state = HCI_TX_STATE_SEND;
                }
            }
            break;

        case HCI_TX_STATE_WAIT_FOR_TX_END:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_SENT))
            {
                hci_pkt_sent_upcall();
                m_hci_tx_fsm_state = HCI_TX_STATE_SEND;
            }
            else if ((p_event->evt_source == HCI_SLIP_EVT) &&
                     (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                hci_process_orphaned_ack(p_event);
            }

            break;

#ifdef HCI_LINK_CONTROL
        case HCI_TX_STATE_DISABLE:
            /* This case should not happen if HCI is in ACTIVE mode */
            if (m_hci_mode == HCI_MODE_ACTIVE)
            {
                ser_phy_hci_assert(false);
            }
            break;
#endif /* HCI_LINK_CONTROL */

        default:
            ser_phy_hci_assert(false);
            break;
    }
