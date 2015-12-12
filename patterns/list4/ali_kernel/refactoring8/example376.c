static struct callback_op callback_ops[] = {
	[0] = {
		.res_maxsize = CB_OP_HDR_RES_MAXSZ,
	},
	[OP_CB_GETATTR] = {
		.process_op = (callback_process_op_t)nfs4_callback_getattr,
		.decode_args = (callback_decode_arg_t)decode_getattr_args,
		.encode_res = (callback_encode_res_t)encode_getattr_res,
		.res_maxsize = CB_OP_GETATTR_RES_MAXSZ,
	},
	[OP_CB_RECALL] = {
		.process_op = (callback_process_op_t)nfs4_callback_recall,
		.decode_args = (callback_decode_arg_t)decode_recall_args,
		.res_maxsize = CB_OP_RECALL_RES_MAXSZ,
	},
#if defined(CONFIG_NFS_V4_1)
	[OP_CB_LAYOUTRECALL] = {
		.process_op = (callback_process_op_t)nfs4_callback_layoutrecall,
		.decode_args =
			(callback_decode_arg_t)decode_layoutrecall_args,
		.res_maxsize = CB_OP_LAYOUTRECALL_RES_MAXSZ,
	},
	[OP_CB_NOTIFY_DEVICEID] = {
		.process_op = (callback_process_op_t)nfs4_callback_devicenotify,
		.decode_args =
			(callback_decode_arg_t)decode_devicenotify_args,
		.res_maxsize = CB_OP_DEVICENOTIFY_RES_MAXSZ,
	},
	[OP_CB_SEQUENCE] = {
		.process_op = (callback_process_op_t)nfs4_callback_sequence,
		.decode_args = (callback_decode_arg_t)decode_cb_sequence_args,
		.encode_res = (callback_encode_res_t)encode_cb_sequence_res,
		.res_maxsize = CB_OP_SEQUENCE_RES_MAXSZ,
	},
	[OP_CB_RECALL_ANY] = {
		.process_op = (callback_process_op_t)nfs4_callback_recallany,
		.decode_args = (callback_decode_arg_t)decode_recallany_args,
		.res_maxsize = CB_OP_RECALLANY_RES_MAXSZ,
	},
	[OP_CB_RECALL_SLOT] = {
		.process_op = (callback_process_op_t)nfs4_callback_recallslot,
		.decode_args = (callback_decode_arg_t)decode_recallslot_args,
		.res_maxsize = CB_OP_RECALLSLOT_RES_MAXSZ,
	},
#endif /* CONFIG_NFS_V4_1 */
};
