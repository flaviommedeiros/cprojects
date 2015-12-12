switch (tmp) {
					/*
					 * Linking lets us reduce the time required to get the 
					 * next command out to the device, hopefully this will
					 * mean we don't waste another revolution due to the delays
					 * required by ARBITRATION and another SELECTION.
					 *
					 * In the current implementation proposal, low level drivers
					 * merely have to start the next command, pointed to by 
					 * next_link, done() is called as with unlinked commands.
					 */
#ifdef LINKED
				case LINKED_CMD_COMPLETE:
				case LINKED_FLG_CMD_COMPLETE:
					/* Accept message by clearing ACK */
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
					dprintk(NDEBUG_LINKED, ("scsi%d : target %d lun %d linked command complete.\n", instance->host_no, cmd->device->id, cmd->device->lun));
					/* 
					 * Sanity check : A linked command should only terminate with
					 * one of these messages if there are more linked commands
					 * available.
					 */
					if (!cmd->next_link) {
						printk("scsi%d : target %d lun %d linked command complete, no next_link\n" instance->host_no, cmd->device->id, cmd->device->lun);
						sink = 1;
						do_abort(instance);
						return;
					}
					initialize_SCp(cmd->next_link);
					/* The next command is still part of this process */
					cmd->next_link->tag = cmd->tag;
					cmd->result = cmd->SCp.Status | (cmd->SCp.Message << 8);
					dprintk(NDEBUG_LINKED, ("scsi%d : target %d lun %d linked request done, calling scsi_done().\n", instance->host_no, cmd->device->id, cmd->device->lun));
					collect_stats(hostdata, cmd);
					cmd->scsi_done(cmd);
					cmd = hostdata->connected;
					break;
#endif				/* def LINKED */
				case ABORT:
				case COMMAND_COMPLETE:
					/* Accept message by clearing ACK */
					sink = 1;
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
					hostdata->connected = NULL;
					dprintk(NDEBUG_QUEUES, ("scsi%d : command for target %d, lun %d completed\n", instance->host_no, cmd->device->id, cmd->device->lun));
					hostdata->busy[cmd->device->id] &= ~(1 << cmd->device->lun);

					/* 
					 * I'm not sure what the correct thing to do here is : 
					 * 
					 * If the command that just executed is NOT a request 
					 * sense, the obvious thing to do is to set the result
					 * code to the values of the stored parameters.
					 * 
					 * If it was a REQUEST SENSE command, we need some way 
					 * to differentiate between the failure code of the original
					 * and the failure code of the REQUEST sense - the obvious
					 * case is success, where we fall through and leave the result
					 * code unchanged.
					 * 
					 * The non-obvious place is where the REQUEST SENSE failed 
					 */

					if (cmd->cmnd[0] != REQUEST_SENSE)
						cmd->result = cmd->SCp.Status | (cmd->SCp.Message << 8);
					else if (status_byte(cmd->SCp.Status) != GOOD)
						cmd->result = (cmd->result & 0x00ffff) | (DID_ERROR << 16);

#ifdef AUTOSENSE
					if ((cmd->cmnd[0] == REQUEST_SENSE) &&
						hostdata->ses.cmd_len) {
						scsi_eh_restore_cmnd(cmd, &hostdata->ses);
						hostdata->ses.cmd_len = 0 ;
					}

					if ((cmd->cmnd[0] != REQUEST_SENSE) && (status_byte(cmd->SCp.Status) == CHECK_CONDITION)) {
						scsi_eh_prep_cmnd(cmd, &hostdata->ses, NULL, 0, ~0);

						dprintk(NDEBUG_AUTOSENSE, ("scsi%d : performing request sense\n", instance->host_no));

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

					NCR5380_write(SELECT_ENABLE_REG, hostdata->id_mask);
					/* 
					 * Restore phase bits to 0 so an interrupted selection, 
					 * arbitration can resume.
					 */
					NCR5380_write(TARGET_COMMAND_REG, 0);

					while ((NCR5380_read(STATUS_REG) & SR_BSY) && !hostdata->connected)
						barrier();
					return;
				case MESSAGE_REJECT:
					/* Accept message by clearing ACK */
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
					switch (hostdata->last_message) {
					case HEAD_OF_QUEUE_TAG:
					case ORDERED_QUEUE_TAG:
					case SIMPLE_QUEUE_TAG:
						cmd->device->simple_tags = 0;
						hostdata->busy[cmd->device->id] |= (1 << cmd->device->lun);
						break;
					default:
						break;
					}
				case DISCONNECT:{
						/* Accept message by clearing ACK */
						NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
						cmd->device->disconnect = 1;
						LIST(cmd, hostdata->disconnected_queue);
						cmd->host_scribble = (unsigned char *)
						    hostdata->disconnected_queue;
						hostdata->connected = NULL;
						hostdata->disconnected_queue = cmd;
						dprintk(NDEBUG_QUEUES, ("scsi%d : command for target %d lun %d was moved from connected to" "  the disconnected_queue\n", instance->host_no, cmd->device->id, cmd->device->lun));
						/* 
						 * Restore phase bits to 0 so an interrupted selection, 
						 * arbitration can resume.
						 */
						NCR5380_write(TARGET_COMMAND_REG, 0);

						/* Enable reselect interrupts */
						NCR5380_write(SELECT_ENABLE_REG, hostdata->id_mask);
						/* Wait for bus free to avoid nasty timeouts - FIXME timeout !*/
						/* NCR538_poll_politely(instance, STATUS_REG, SR_BSY, 0, 30 * HZ); */
						while ((NCR5380_read(STATUS_REG) & SR_BSY) && !hostdata->connected)
							barrier();
						return;
					}
					/* 
					 * The SCSI data pointer is *IMPLICITLY* saved on a disconnect
					 * operation, in violation of the SCSI spec so we can safely 
					 * ignore SAVE/RESTORE pointers calls.
					 *
					 * Unfortunately, some disks violate the SCSI spec and 
					 * don't issue the required SAVE_POINTERS message before
					 * disconnecting, and we have to break spec to remain 
					 * compatible.
					 */
				case SAVE_POINTERS:
				case RESTORE_POINTERS:
					/* Accept message by clearing ACK */
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
					break;
				case EXTENDED_MESSAGE:
/* 
 * Extended messages are sent in the following format :
 * Byte         
 * 0            EXTENDED_MESSAGE == 1
 * 1            length (includes one byte for code, doesn't 
 *              include first two bytes)
 * 2            code
 * 3..length+1  arguments
 *
 * Start the extended message buffer with the EXTENDED_MESSAGE
 * byte, since spi_print_msg() wants the whole thing.  
 */
					extended_msg[0] = EXTENDED_MESSAGE;
					/* Accept first byte by clearing ACK */
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
					dprintk(NDEBUG_EXTENDED, ("scsi%d : receiving extended message\n", instance->host_no));

					len = 2;
					data = extended_msg + 1;
					phase = PHASE_MSGIN;
					NCR5380_transfer_pio(instance, &phase, &len, &data);

					dprintk(NDEBUG_EXTENDED, ("scsi%d : length=%d, code=0x%02x\n", instance->host_no, (int) extended_msg[1], (int) extended_msg[2]));

					if (!len && extended_msg[1] <= (sizeof(extended_msg) - 1)) {
						/* Accept third byte by clearing ACK */
						NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
						len = extended_msg[1] - 1;
						data = extended_msg + 3;
						phase = PHASE_MSGIN;

						NCR5380_transfer_pio(instance, &phase, &len, &data);
						dprintk(NDEBUG_EXTENDED, ("scsi%d : message received, residual %d\n", instance->host_no, len));

						switch (extended_msg[2]) {
						case EXTENDED_SDTR:
						case EXTENDED_WDTR:
						case EXTENDED_MODIFY_DATA_POINTER:
						case EXTENDED_EXTENDED_IDENTIFY:
							tmp = 0;
						}
					} else if (len) {
						printk("scsi%d: error receiving extended message\n", instance->host_no);
						tmp = 0;
					} else {
						printk("scsi%d: extended message code %02x length %d is too long\n", instance->host_no, extended_msg[2], extended_msg[1]);
						tmp = 0;
					}
					/* Fall through to reject message */

					/* 
					 * If we get something weird that we aren't expecting, 
					 * reject it.
					 */
				default:
					if (!tmp) {
						printk("scsi%d: rejecting message ", instance->host_no);
						spi_print_msg(extended_msg);
						printk("\n");
					} else if (tmp != EXTENDED_MESSAGE)
						scmd_printk(KERN_INFO, cmd,
							"rejecting unknown message %02x\n",tmp);
					else
						scmd_printk(KERN_INFO, cmd,
							"rejecting unknown extended message code %02x, length %d\n", extended_msg[1], extended_msg[0]);

					msgout = MESSAGE_REJECT;
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN);
					break;
				}
