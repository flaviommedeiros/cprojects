static const osThreadDef_t * const iso_tsk_def_tbl[ISO_TRANS_MAX_NUM] = {
        osThread(iso_ed_task_1)
#if (ISO_TRANS_MAX_NUM >= 2)
      , osThread(iso_ed_task_2)
#endif
    };
