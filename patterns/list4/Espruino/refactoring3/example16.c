switch (m_hci_rx_fsm_state)
    {
        case HCI_RX_STATE_RECEIVE:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                /* type and crc and check sum are validated by slip handler */
                uint8_t rx_seq_number = packet_seq_nmbr_extract(
                    p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);

                if (packet_ack_get() == rx_seq_number)
                {
                    hci_mem_request(p_event);
                    m_hci_rx_fsm_state = HCI_RX_STATE_WAIT_FOR_MEM;
                }
                else
                {
                    // m_rx_drop_counter++;
                    m_hci_rx_fsm_state = HCI_RX_STATE_WAIT_FOR_SLIP_NACK_END;
                    (void) ser_phy_hci_slip_rx_buf_free(m_p_rx_packet); // and drop a packet
                    ack_transmit();                                     // send NACK with valid ACK
                }
            }
            break;

        case HCI_RX_STATE_WAIT_FOR_MEM:

            if ((p_event->evt_source == HCI_SER_PHY_EVT) &&
                (p_event->evt.ser_phy_evt.evt_type == HCI_SER_PHY_RX_BUF_GRANTED))
            {
                if (m_p_rx_buffer)
                {
                    memcpy(m_p_rx_buffer,
                           m_p_rx_packet + PKT_HDR_SIZE,
                           m_rx_packet_length - PKT_HDR_SIZE - PKT_CRC_SIZE);
                    (void) ser_phy_hci_slip_rx_buf_free(m_p_rx_packet);
                }
                m_hci_rx_fsm_state = HCI_RX_STATE_WAIT_FOR_SLIP_ACK_END;
                hci_inc_ack(); // SEQ was valid for good packet, we will send incremented SEQ as ACK
                ack_transmit();
            }

            break;

        case HCI_RX_STATE_WAIT_FOR_SLIP_ACK_END:

            if ((p_event->evt_source == HCI_SLIP_EVT) &&
                (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_ACK_SENT))
            {

                if (m_p_rx_buffer)
                {
                    packet_received_callback(m_p_rx_buffer,
                                             m_rx_packet_length - PKT_HDR_SIZE - PKT_CRC_SIZE);
                }
                else
                {
                    packet_dropped_callback();
                }
                m_hci_rx_fsm_state = HCI_RX_STATE_RECEIVE;
            }
            else if ((p_event->evt_source == HCI_SLIP_EVT) &&
                    (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_PKT_RECEIVED))
            {
                (void) ser_phy_hci_slip_rx_buf_free(p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);
            }
            break;

        case HCI_RX_STATE_WAIT_FOR_SLIP_NACK_END:
            if ((p_event->evt_source == HCI_SLIP_EVT) &&
               (p_event->evt.ser_phy_slip_evt.evt_type == SER_PHY_HCI_SLIP_EVT_ACK_SENT))
            {
               m_hci_rx_fsm_state = HCI_RX_STATE_RECEIVE;
            }
            else
            {
               (void) ser_phy_hci_slip_rx_buf_free(p_event->evt.ser_phy_slip_evt.evt_params.received_pkt.p_buffer);
            }
            break;


#ifdef HCI_LINK_CONTROL
        case HCI_RX_STATE_DISABLE:
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
