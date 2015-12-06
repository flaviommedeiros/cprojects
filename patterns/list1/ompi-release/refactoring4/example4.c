#if MXM_API < MXM_VERSION(2,1)
if ((MXM_OK != mxm_config_read_context_opts(&mca_spml_ikrit.mxm_ctx_opts)) ||
        (MXM_OK != mxm_config_read_ep_opts(&mca_spml_ikrit.mxm_ep_opts)))
#else
    if (OSHMEM_SUCCESS != set_mxm_tls()) {
        return OSHMEM_ERROR;
    }
