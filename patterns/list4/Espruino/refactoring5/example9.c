#ifdef PSTORAGE_RAW_MODE_ENABLE
if (p_elem->storage_addr.module_id == RAW_MODE_APP_ID)
    {
        ntf_cb = m_raw_app_table.cb;
    }
    else
#endif // PSTORAGE_RAW_MODE_ENABLE
    {
        ntf_cb = m_app_table[p_elem->storage_addr.module_id].cb;
    }
