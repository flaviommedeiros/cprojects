static api_hook_t ah[] = {
    { "hardware/tree", ACCESS_ADMIN,     api_idnode_tree, api_input_hw_tree }, 
#if ENABLE_SATIP_CLIENT
    { "hardware/satip/discover", ACCESS_ADMIN, api_input_satip_discover, NULL },
#endif
    { NULL },
  };
