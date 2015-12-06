#if MXM_API >= MXM_VERSION(2,1)
if (MXM_OK != mxm_config_read_opts(&ompi_mtl_mxm.mxm_ctx_opts,
                                       &ompi_mtl_mxm.mxm_ep_opts,
                                       "MPI", NULL, 0))
#else
    if ((MXM_OK != mxm_config_read_context_opts(&ompi_mtl_mxm.mxm_ctx_opts)) ||
        (MXM_OK != mxm_config_read_ep_opts(&ompi_mtl_mxm.mxm_ep_opts)))
#endif
    {
        MXM_ERROR("Failed to parse MXM configuration");
        return OPAL_ERR_BAD_PARAM;
    }
