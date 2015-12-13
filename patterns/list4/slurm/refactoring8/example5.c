static display_data_t display_data_part[] = {
	{G_TYPE_INT, SORTID_POS, NULL, FALSE, EDIT_NONE, refresh_part},
	{G_TYPE_STRING, SORTID_NAME, "Partition", FALSE,
	 EDIT_NONE, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_COLOR, NULL, TRUE, EDIT_COLOR, refresh_part,
	 create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_ALTERNATE, "Alternate", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_DEFAULT, "Default", FALSE,
	 EDIT_MODEL, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_EXCLUSIVE_USER, "ExclusiveUser", FALSE,
	 EDIT_MODEL, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_GRACE_TIME, "GraceTime", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_HIDDEN, "Hidden", FALSE,
	 EDIT_MODEL, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_PART_STATE, "Part State", FALSE,
	 EDIT_MODEL, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_TIMELIMIT, "Time Limit", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_NODES, "Node Count", FALSE,
	 EDIT_NONE, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_CPUS, "CPU Count", FALSE,
	 EDIT_NONE, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_NODE_STATE, "Node State", FALSE,
	 EDIT_MODEL, refresh_part,
	 create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_JOB_SIZE, "Job Size", FALSE,
	 EDIT_NONE, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_PREEMPT_MODE, "PreemptMode", FALSE,
	 EDIT_MODEL, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_PRIORITY, "Priority", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_NODES_MIN, "Nodes Min", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_NODES_MAX, "Nodes Max", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_MAX_CPUS_PER_NODE, "Max CPUs Per Node", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_ROOT, "Root", FALSE, EDIT_MODEL, refresh_part,
	 create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_SHARE, "Share", FALSE, EDIT_MODEL, refresh_part,
	 create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_QOS_CHAR, "Qos", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_ALLOW_ACCOUNTS, "Allowed Accounts", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_ALLOW_GROUPS, "Allowed Groups", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_ALLOW_QOS, "Allowed Qos", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_DENY_ACCOUNTS, "Denied Accounts", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_DENY_QOS, "Denied Qos", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_NODES_ALLOWED, "Nodes Allowed Allocating", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_TMP_DISK, "Temp Disk", FALSE,
	 EDIT_NONE, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_MEM, "Memory", FALSE, EDIT_NONE, refresh_part,
	 create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_FEATURES, "Features", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_STRING, SORTID_REASON, "Reason", FALSE,
	 EDIT_NONE, refresh_part, create_model_part, admin_edit_part},
#ifdef HAVE_BG
	{G_TYPE_STRING, SORTID_NODELIST, "MidplaneList", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
#else
	{G_TYPE_STRING, SORTID_NODELIST, "NodeList", FALSE,
	 EDIT_TEXTBOX, refresh_part, create_model_part, admin_edit_part},
#endif
	{G_TYPE_INT, SORTID_NODE_STATE_NUM, NULL, FALSE,
	 EDIT_NONE, refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_INT, SORTID_ONLY_LINE, NULL, FALSE, EDIT_NONE, refresh_part,
	 create_model_part, admin_edit_part},
	{G_TYPE_INT, SORTID_COLOR_INX, NULL, FALSE, EDIT_NONE, refresh_part,
	 create_model_part, admin_edit_part},
	{G_TYPE_POINTER, SORTID_NODE_INX, NULL, FALSE, EDIT_NONE,
	 refresh_part, create_model_part, admin_edit_part},
	{G_TYPE_INT, SORTID_UPDATED, NULL, FALSE, EDIT_NONE, refresh_part,
	 create_model_part, admin_edit_part},
	{G_TYPE_NONE, -1, NULL, FALSE, EDIT_NONE}
};