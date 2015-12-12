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

					dprintk(NDEBUG_LINKED, "scsi%d: target %d lun %llu linked command "
						   "complete.\n", HOSTNO, cmd->device->id, cmd->device->lun);

					/* Enable reselect interrupts */
					NCR5380_write(SELECT_ENABLE_REG, hostdata->id_mask);
					/*
					 * Sanity check : A linked command should only terminate
					 * with one of these messages if there are more linked
					 * commands available.
					 */

					if (!cmd->next_link) {
						 printk(KERN_NOTICE "scsi%d: target %d lun %llu "
							"linked command complete, no next_link\n",
							HOSTNO, cmd->device->id, cmd->device->lun);
						sink = 1;
						do_abort(instance);
						return;
					}

					initialize_SCp(cmd->next_link);
					/* The next command is still part of this process; copy it
					 * and don't free it! */
					cmd->next_link->tag = cmd->tag;
					cmd->result = cmd->SCp.Status | (cmd->SCp.Message << 8);
					dprintk(NDEBUG_LINKED, "scsi%d: target %d lun %llu linked request "
						   "done, calling scsi_done().\n",
						   HOSTNO, cmd->device->id, cmd->device->lun);
					cmd->scsi_done(cmd);
					cmd = hostdata->connected;
					break;
#endif /* def LINKED */
				case ABORT:
				case COMMAND_COMPLETE:
					/* Accept message by clearing ACK */
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
					dprintk(NDEBUG_QUEUES, "scsi%d: command for target %d, lun %llu "
						  "completed\n", HOSTNO, cmd->device->id, cmd->device->lun);

					local_irq_save(flags);
					hostdata->retain_dma_intr++;
					hostdata->connected = NULL;
#ifdef SUPPORT_TAGS
					cmd_free_tag(cmd);
					if (status_byte(cmd->SCp.Status) == QUEUE_FULL) {
						/* Turn a QUEUE FULL status into BUSY, I think the
						 * mid level cannot handle QUEUE FULL :-( (The
						 * command is retried after BUSY). Also update our
						 * queue size to the number of currently issued
						 * commands now.
						 */
						/* ++Andreas: the mid level code knows about
						   QUEUE_FULL now. */
						struct tag_alloc *ta = &hostdata->TagAlloc[scmd_id(cmd)][cmd->device->lun];
						dprintk(NDEBUG_TAGS, "scsi%d: target %d lun %llu returned "
							   "QUEUE_FULL after %d commands\n",
							   HOSTNO, cmd->device->id, cmd->device->lun,
							   ta->nr_allocated);
						if (ta->queue_size > ta->nr_allocated)
							ta->nr_allocated = ta->queue_size;
					}
#else
					hostdata->busy[cmd->device->id] &= ~(1 << cmd->device->lun);
#endif
					/* Enable reselect interrupts */
					NCR5380_write(SELECT_ENABLE_REG, hostdata->id_mask);

					/*
					 * I'm not sure what the correct thing to do here is :
					 *
					 * If the command that just executed is NOT a request
					 * sense, the obvious thing to do is to set the result
					 * code to the values of the stored parameters.
					 *
					 * If it was a REQUEST SENSE command, we need some way to
					 * differentiate between the failure code of the original
					 * and the failure code of the REQUEST sense - the obvious
					 * case is success, where we fall through and leave the
					 * result code unchanged.
					 *
					 * The non-obvious place is where the REQUEST SENSE failed
					 */

					if (cmd->cmnd[0] != REQUEST_SENSE)
						cmd->result = cmd->SCp.Status | (cmd->SCp.Message << 8);
					else if (status_byte(cmd->SCp.Status) != GOOD)
						cmd->result = (cmd->result & 0x00ffff) | (DID_ERROR << 16);

					if ((cmd->cmnd[0] == REQUEST_SENSE) &&
						hostdata->ses.cmd_len) {
						scsi_eh_restore_cmnd(cmd, &hostdata->ses);
						hostdata->ses.cmd_len = 0 ;
					}

					if ((cmd->cmnd[0] != REQUEST_SENSE) &&
					    (status_byte(cmd->SCp.Status) == CHECK_CONDITION)) {
						scsi_eh_prep_cmnd(cmd, &hostdata->ses, NULL, 0, ~0);

						dprintk(NDEBUG_AUTOSENSE, "scsi%d: performing request sense\n", HOSTNO);

						LIST(cmd,hostdata->issue_queue);
						SET_NEXT(cmd, hostdata->issue_queue);
						hostdata->issue_queue = (struct scsi_cmnd *) cmd;
						dprintk(NDEBUG_QUEUES, "scsi%d: REQUEST SENSE added to head of "
							  "issue queue\n", H_NO(cmd));
					} else {
						cmd->scsi_done(cmd);
					}

					local_irq_restore(flags);

					NCR5380_write(SELECT_ENABLE_REG, hostdata->id_mask);
					/*
					 * Restore phase bits to 0 so an interrupted selection,
					 * arbitration can resume.
					 */
					NCR5380_write(TARGET_COMMAND_REG, 0);

					while ((NCR5380_read(STATUS_REG) & SR_BSY) && !hostdata->connected)
						barrier();

					local_irq_save(flags);
					hostdata->retain_dma_intr--;
					/* ++roman: For Falcon SCSI, release the lock on the
					 * ST-DMA here if no other commands are waiting on the
					 * disconnected queue.
					 */
					maybe_release_dma_irq(instance);
					local_irq_restore(flags);
					return;
				case MESSAGE_REJECT:
					/* Accept message by clearing ACK */
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
					/* Enable reselect interrupts */
					NCR5380_write(SELECT_ENABLE_REG, hostdata->id_mask);
					switch (hostdata->last_message) {
					case HEAD_OF_QUEUE_TAG:
					case ORDERED_QUEUE_TAG:
					case SIMPLE_QUEUE_TAG:
						/* The target obviously doesn't support tagged
						 * queuing, even though it announced this ability in
						 * its INQUIRY data ?!? (maybe only this LUN?) Ok,
						 * clear 'tagged_supported' and lock the LUN, since
						 * the command is treated as untagged further on.
						 */
						cmd->device->tagged_supported = 0;
						hostdata->busy[cmd->device->id] |= (1 << cmd->device->lun);
						cmd->tag = TAG_NONE;
						dprintk(NDEBUG_TAGS, "scsi%d: target %d lun %llu rejected "
							   "QUEUE_TAG message; tagged queuing "
							   "disabled\n",
							   HOSTNO, cmd->device->id, cmd->device->lun);
						break;
					}
					break;
				case DISCONNECT:
					/* Accept message by clearing ACK */
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
					local_irq_save(flags);
					cmd->device->disconnect = 1;
					LIST(cmd,hostdata->disconnected_queue);
					SET_NEXT(cmd, hostdata->disconnected_queue);
					hostdata->connected = NULL;
					hostdata->disconnected_queue = cmd;
					local_irq_restore(flags);
					dprintk(NDEBUG_QUEUES, "scsi%d: command for target %d lun %llu was "
						  "moved from connected to the "
						  "disconnected_queue\n", HOSTNO,
						  cmd->device->id, cmd->device->lun);
					/*
					 * Restore phase bits to 0 so an interrupted selection,
					 * arbitration can resume.
					 */
					NCR5380_write(TARGET_COMMAND_REG, 0);

					/* Enable reselect interrupts */
					NCR5380_write(SELECT_ENABLE_REG, hostdata->id_mask);
					/* Wait for bus free to avoid nasty timeouts */
					while ((NCR5380_read(STATUS_REG) & SR_BSY) && !hostdata->connected)
						barrier();
#ifdef SUN3_SCSI_VME
					dregs->csr |= CSR_DMA_ENABLE;
#endif
					return;
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
					/* Enable reselect interrupts */
					NCR5380_write(SELECT_ENABLE_REG, hostdata->id_mask);
					break;
				case EXTENDED_MESSAGE:
					/*
					 * Extended messages are sent in the following format :
					 * Byte
					 * 0		EXTENDED_MESSAGE == 1
					 * 1		length (includes one byte for code, doesn't
					 *		include first two bytes)
					 * 2		code
					 * 3..length+1	arguments
					 *
					 * Start the extended message buffer with the EXTENDED_MESSAGE
					 * byte, since spi_print_msg() wants the whole thing.
					 */
					extended_msg[0] = EXTENDED_MESSAGE;
					/* Accept first byte by clearing ACK */
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);

					dprintk(NDEBUG_EXTENDED, "scsi%d: receiving extended message\n", HOSTNO);

					len = 2;
					data = extended_msg + 1;
					phase = PHASE_MSGIN;
					NCR5380_transfer_pio(instance, &phase, &len, &data);
					dprintk(NDEBUG_EXTENDED, "scsi%d: length=%d, code=0x%02x\n", HOSTNO,
						   (int)extended_msg[1], (int)extended_msg[2]);

					if (!len && extended_msg[1] <=
					    (sizeof(extended_msg) - 1)) {
						/* Accept third byte by clearing ACK */
						NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
						len = extended_msg[1] - 1;
						data = extended_msg + 3;
						phase = PHASE_MSGIN;

						NCR5380_transfer_pio(instance, &phase, &len, &data);
						dprintk(NDEBUG_EXTENDED, "scsi%d: message received, residual %d\n",
							   HOSTNO, len);

						switch (extended_msg[2]) {
						case EXTENDED_SDTR:
						case EXTENDED_WDTR:
						case EXTENDED_MODIFY_DATA_POINTER:
						case EXTENDED_EXTENDED_IDENTIFY:
							tmp = 0;
						}
					} else if (len) {
						printk(KERN_NOTICE "scsi%d: error receiving "
						       "extended message\n", HOSTNO);
						tmp = 0;
					} else {
						printk(KERN_NOTICE "scsi%d: extended message "
							   "code %02x length %d is too long\n",
							   HOSTNO, extended_msg[2], extended_msg[1]);
						tmp = 0;
					}
					/* Fall through to reject message */

					/*
					 * If we get something weird that we aren't expecting,
					 * reject it.
					 */
				default:
					if (!tmp) {
						printk(KERN_INFO "scsi%d: rejecting message ",
						       instance->host_no);
						spi_print_msg(extended_msg);
						printk("\n");
					} else if (tmp != EXTENDED_MESSAGE)
						scmd_printk(KERN_INFO, cmd,
						            "rejecting unknown message %02x\n",
						            tmp);
					else
						scmd_printk(KERN_INFO, cmd,
						            "rejecting unknown extended message code %02x, length %d\n",
						            extended_msg[1], extended_msg[0]);

					msgout = MESSAGE_REJECT;
					NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE | ICR_ASSERT_ATN);
					break;
				}
