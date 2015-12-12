static ngx_command_t ngx_http_mruby_commands[] = {

    {ngx_string("mruby_init_code"), NGX_HTTP_MAIN_CONF | NGX_CONF_TAKE1, ngx_http_mruby_init_inline,
     NGX_HTTP_MAIN_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_init"), NGX_HTTP_MAIN_CONF | NGX_CONF_TAKE12, ngx_http_mruby_init_phase,
     NGX_HTTP_MAIN_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_init_worker_code"), NGX_HTTP_MAIN_CONF | NGX_CONF_TAKE1, ngx_http_mruby_init_worker_inline,
     NGX_HTTP_MAIN_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_init_worker"), NGX_HTTP_MAIN_CONF | NGX_CONF_TAKE12, ngx_http_mruby_init_worker_phase,
     NGX_HTTP_MAIN_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_exit_worker_code"), NGX_HTTP_MAIN_CONF | NGX_CONF_TAKE1, ngx_http_mruby_exit_worker_inline,
     NGX_HTTP_MAIN_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_exit_worker"), NGX_HTTP_MAIN_CONF | NGX_CONF_TAKE12, ngx_http_mruby_exit_worker_phase,
     NGX_HTTP_MAIN_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_cache"), NGX_HTTP_LOC_CONF | NGX_HTTP_SRV_CONF | NGX_CONF_FLAG, ngx_conf_set_flag_slot,
     NGX_HTTP_LOC_CONF_OFFSET, offsetof(ngx_http_mruby_loc_conf_t, cached), NULL},

    {ngx_string("mruby_add_handler"), NGX_HTTP_LOC_CONF | NGX_HTTP_SRV_CONF | NGX_CONF_FLAG, ngx_conf_set_flag_slot,
     NGX_HTTP_LOC_CONF_OFFSET, offsetof(ngx_http_mruby_loc_conf_t, add_handler), NULL},

    {ngx_string("mruby_post_read_handler"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE12,
     ngx_http_mruby_post_read_phase, NGX_HTTP_LOC_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_server_rewrite_handler"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE12,
     ngx_http_mruby_server_rewrite_phase, NGX_HTTP_LOC_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_rewrite_handler"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE12,
     ngx_http_mruby_rewrite_phase, NGX_HTTP_LOC_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_access_handler"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE12,
     ngx_http_mruby_access_phase, NGX_HTTP_LOC_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_content_handler"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE12,
     ngx_http_mruby_content_phase, NGX_HTTP_LOC_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_log_handler"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE12,
     ngx_http_mruby_log_phase, NGX_HTTP_LOC_CONF_OFFSET, 0, NULL},

    {ngx_string("mruby_post_read_handler_code"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE1,
     ngx_http_mruby_post_read_inline, NGX_HTTP_LOC_CONF_OFFSET, 0, ngx_http_mruby_post_read_inline_handler},

    {ngx_string("mruby_server_rewrite_handler_code"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE1,
     ngx_http_mruby_server_rewrite_inline, NGX_HTTP_LOC_CONF_OFFSET, 0, ngx_http_mruby_server_rewrite_inline_handler},

    {ngx_string("mruby_rewrite_handler_code"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE1,
     ngx_http_mruby_rewrite_inline, NGX_HTTP_LOC_CONF_OFFSET, 0, ngx_http_mruby_rewrite_inline_handler},

    {ngx_string("mruby_access_handler_code"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE1,
     ngx_http_mruby_access_inline, NGX_HTTP_LOC_CONF_OFFSET, 0, ngx_http_mruby_access_inline_handler},

    {ngx_string("mruby_content_handler_code"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE1,
     ngx_http_mruby_content_inline, NGX_HTTP_LOC_CONF_OFFSET, 0, ngx_http_mruby_content_inline_handler},

    {ngx_string("mruby_log_handler_code"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE1,
     ngx_http_mruby_log_inline, NGX_HTTP_LOC_CONF_OFFSET, 0, ngx_http_mruby_log_inline_handler},

#if defined(NDK) && NDK
    {ngx_string("mruby_set"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_2MORE,
     ngx_http_mruby_set, NGX_HTTP_LOC_CONF_OFFSET, 0, ngx_http_mruby_set_handler},

    {ngx_string("mruby_set_code"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_2MORE,
     ngx_http_mruby_set_inline, NGX_HTTP_LOC_CONF_OFFSET, 0, ngx_http_mruby_set_inline_handler},
#endif

    {ngx_string("mruby_output_filter"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE12,
     ngx_http_mruby_body_filter_phase, NGX_HTTP_LOC_CONF_OFFSET, 0, ngx_http_mruby_body_filter_handler},

    {ngx_string("mruby_output_filter_code"),
     NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE1,
     ngx_http_mruby_body_filter_inline, NGX_HTTP_LOC_CONF_OFFSET, 0, ngx_http_mruby_body_filter_inline_handler},

    ngx_null_command};
