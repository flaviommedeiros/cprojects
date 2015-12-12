static void ipr_initiate_ioa_reset(struct ipr_ioa_cfg *,
				   enum ipr_shutdown_type);

#ifdef CONFIG_SCSI_IPR_TRACE
/**
 * ipr_trc_hook - Add a trace entry to the driver trace
 * @ipr_cmd:	ipr command struct
 * @type:		trace type
 * @add_data:	additional data
 *
 * Return value:
 * 	none
 **/
static void ipr_trc_hook(struct ipr_cmnd *ipr_cmd,
			 u8 type, u32 add_data)
{
	struct ipr_trace_entry *trace_entry;
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	unsigned int trace_index;

	trace_index = atomic_add_return(1, &ioa_cfg->trace_index) & IPR_TRACE_INDEX_MASK;
	trace_entry = &ioa_cfg->trace[trace_index];
	trace_entry->time = jiffies;
	trace_entry->op_code = ipr_cmd->ioarcb.cmd_pkt.cdb[0];
	trace_entry->type = type;
	if (ipr_cmd->ioa_cfg->sis64)
		trace_entry->ata_op_code = ipr_cmd->i.ata_ioadl.regs.command;
	else
		trace_entry->ata_op_code = ipr_cmd->ioarcb.u.add_data.u.regs.command;
	trace_entry->cmd_index = ipr_cmd->cmd_index & 0xff;
	trace_entry->res_handle = ipr_cmd->ioarcb.res_handle;
	trace_entry->u.add_data = add_data;
	wmb();
