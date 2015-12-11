#ifdef PSTORAGE_RAW_MODE_ENABLE
if (m_cmd_queue.cmd[m_cmd_queue.rp].storage_addr.module_id == RAW_MODE_APP_ID)
    {
        ntf_cb = m_raw_app_table.cb;
    }
    else
#endif // PSTORAGE_RAW_MODE_ENABLE
    {
        ntf_cb = m_app_table[m_cmd_queue.cmd[m_cmd_queue.rp].storage_addr.module_id].cb;
    }
