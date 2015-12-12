static Plugin basicfuncs_plus_plugins[] =
{
  TEMPLATE_FUNCTION_PLUGIN(tf_num_divx, "//"),
#if GLIB_CHECK_VERSION(2,32,0)
  TEMPLATE_FUNCTION_PLUGIN(tf_state, "state"),
#endif
};
