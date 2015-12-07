#ifdef AUTOSENSE
if ((cmd->cmnd[0] != REQUEST_SENSE) &&
					    (status_byte(cmd->SCp.Status) == CHECK_CONDITION)) {
						ASEN_PRINTK("scsi%d: performing request sense\n", HOSTNO);
						cmd->cmnd[0] = REQUEST_SENSE;
						cmd->cmnd[1] &= 0xe0;
						cmd->cmnd[2] = 0;
						cmd->cmnd[3] = 0;
						cmd->cmnd[4] = sizeof(cmd->sense_buffer);
						cmd->cmnd[5] = 0;
						cmd->cmd_len = COMMAND_SIZE(cmd->cmnd[0]);

						cmd->use_sg = 0;
						/* this is initialized from initialize_SCp
						cmd->SCp.buffer = NULL;
						cmd->SCp.buffers_residual = 0;
						*/
						cmd->request_buffer = (char *) cmd->sense_buffer;
						cmd->request_bufflen = sizeof(cmd->sense_buffer);

						local_irq_save(flags);
						LIST(cmd,hostdata->issue_queue);
						SET_NEXT(cmd, hostdata->issue_queue);
						hostdata->issue_queue = (Scsi_Cmnd *) cmd;
						local_irq_restore(flags);
						QU_PRINTK("scsi%d: REQUEST SENSE added to head of "
							  "issue queue\n", H_NO(cmd));
					} else
#endif /* def AUTOSENSE */
					{
#ifdef NCR5380_STATS
						collect_stats(hostdata, cmd);
#endif
						cmd->scsi_done(cmd);
					}
