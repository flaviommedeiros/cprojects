#ifdef AUTOSENSE
if ((cmd->cmnd[0] != REQUEST_SENSE) && (status_byte(cmd->SCp.Status) == CHECK_CONDITION)) {
						dprintk(NDEBUG_AUTOSENSE, ("scsi%d : performing request sense\n", instance->host_no));
						cmd->cmnd[0] = REQUEST_SENSE;
						cmd->cmnd[1] &= 0xe0;
						cmd->cmnd[2] = 0;
						cmd->cmnd[3] = 0;
						cmd->cmnd[4] = sizeof(cmd->sense_buffer);
						cmd->cmnd[5] = 0;

						cmd->SCp.buffer = NULL;
						cmd->SCp.buffers_residual = 0;
						cmd->SCp.ptr = (char *) cmd->sense_buffer;
						cmd->SCp.this_residual = sizeof(cmd->sense_buffer);

						LIST(cmd, hostdata->issue_queue);
						cmd->host_scribble = (unsigned char *)
						    hostdata->issue_queue;
						hostdata->issue_queue = (Scsi_Cmnd *) cmd;
						dprintk(NDEBUG_QUEUES, ("scsi%d : REQUEST SENSE added to head of issue queue\n", instance->host_no));
					} else
#endif				/* def AUTOSENSE */
					{
						collect_stats(hostdata, cmd);
						cmd->scsi_done(cmd);
					}
