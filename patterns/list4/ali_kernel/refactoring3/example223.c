switch (intstat & SEQINT_MASK)
  {
    case NO_MATCH:
      {
        aic_outb(p, aic_inb(p, SCSISEQ) & (ENSELI|ENRSELI|ENAUTOATNP),
                 SCSISEQ);
        printk(WARN_LEAD "No active SCB for reconnecting target - Issuing "
               "BUS DEVICE RESET.\n", p->host_no, channel, target, lun);
        printk(WARN_LEAD "      SAVED_TCL=0x%x, ARG_1=0x%x, SEQADDR=0x%x\n",
               p->host_no, channel, target, lun,
               aic_inb(p, SAVED_TCL), aic_inb(p, ARG_1),
               (aic_inb(p, SEQADDR1) << 8) | aic_inb(p, SEQADDR0));
        if (aic7xxx_panic_on_abort)
          aic7xxx_panic_abort(p, NULL);
      }
      break;

    case SEND_REJECT:
      {
        if (aic7xxx_verbose & VERBOSE_MINOR_ERROR)
          printk(INFO_LEAD "Rejecting unknown message (0x%x) received from "
            "target, SEQ_FLAGS=0x%x\n", p->host_no, channel, target, lun,
            aic_inb(p, ACCUM), aic_inb(p, SEQ_FLAGS));
      }
      break;

    case NO_IDENT:
      {
        /*
         * The reconnecting target either did not send an identify
         * message, or did, but we didn't find an SCB to match and
         * before it could respond to our ATN/abort, it hit a dataphase.
         * The only safe thing to do is to blow it away with a bus
         * reset.
         */
        if (aic7xxx_verbose & (VERBOSE_SEQINT | VERBOSE_RESET_MID))
          printk(INFO_LEAD "Target did not send an IDENTIFY message; "
            "LASTPHASE 0x%x, SAVED_TCL 0x%x\n", p->host_no, channel, target,
            lun, aic_inb(p, LASTPHASE), aic_inb(p, SAVED_TCL));

        aic7xxx_reset_channel(p, channel, /*initiate reset*/ TRUE);
        aic7xxx_run_done_queue(p, TRUE);

      }
      break;

    case BAD_PHASE:
      if (aic_inb(p, LASTPHASE) == P_BUSFREE)
      {
        if (aic7xxx_verbose & VERBOSE_SEQINT)
          printk(INFO_LEAD "Missed busfree.\n", p->host_no, channel,
            target, lun);
        restart_sequencer(p);
      }
      else
      {
        if (aic7xxx_verbose & VERBOSE_SEQINT)
          printk(INFO_LEAD "Unknown scsi bus phase, continuing\n", p->host_no,
            channel, target, lun);
      }
      break;

    case EXTENDED_MSG:
      {
        p->msg_type = MSG_TYPE_INITIATOR_MSGIN;
        p->msg_len = 0;
        p->msg_index = 0;

#ifdef AIC7XXX_VERBOSE_DEBUGGING
        if (aic7xxx_verbose > 0xffff)
          printk(INFO_LEAD "Enabling REQINITs for MSG_IN\n", p->host_no,
                 channel, target, lun);
#endif

       /*      
        * To actually receive the message, simply turn on
        * REQINIT interrupts and let our interrupt handler
        * do the rest (REQINIT should already be true).
        */
        p->flags |= AHC_HANDLING_REQINITS;
        aic_outb(p, aic_inb(p, SIMODE1) | ENREQINIT, SIMODE1);

       /*
        * We don't want the sequencer unpaused yet so we return early
        */
        return;
      }

    case REJECT_MSG:
      {
        /*
         * What we care about here is if we had an outstanding SDTR
         * or WDTR message for this target. If we did, this is a
         * signal that the target is refusing negotiation.
         */
        unsigned char scb_index;
        unsigned char last_msg;

        scb_index = aic_inb(p, SCB_TAG);
        scb = p->scb_data->scb_array[scb_index];
	aic_dev = AIC_DEV(scb->cmd);
        last_msg = aic_inb(p, LAST_MSG);

        if ( (last_msg == MSG_IDENTIFYFLAG) &&
             (scb->tag_action) &&
            !(scb->flags & SCB_MSGOUT_BITS) )
        {
          if (scb->tag_action == MSG_ORDERED_Q_TAG)
          {
            /*
             * OK...the device seems able to accept tagged commands, but
             * not ordered tag commands, only simple tag commands.  So, we
             * disable ordered tag commands and go on with life just like
             * normal.
             */
	    scsi_adjust_queue_depth(scb->cmd->device, MSG_SIMPLE_TAG,
			    scb->cmd->device->queue_depth);
            scb->tag_action = MSG_SIMPLE_Q_TAG;
            scb->hscb->control &= ~SCB_TAG_TYPE;
            scb->hscb->control |= MSG_SIMPLE_Q_TAG;
            aic_outb(p, scb->hscb->control, SCB_CONTROL);
            /*
             * OK..we set the tag type to simple tag command, now we re-assert
             * ATNO and hope this will take us into the identify phase again
             * so we can resend the tag type and info to the device.
             */
            aic_outb(p, MSG_IDENTIFYFLAG, MSG_OUT);
            aic_outb(p, aic_inb(p, SCSISIGI) | ATNO, SCSISIGO);
          }
          else if (scb->tag_action == MSG_SIMPLE_Q_TAG)
          {
            unsigned char i;
            struct aic7xxx_scb *scbp;
            int old_verbose;
            /*
             * Hmmmm....the device is flaking out on tagged commands.
             */
	    scsi_adjust_queue_depth(scb->cmd->device, 0 /* untagged */,
			    p->host->cmd_per_lun);
            aic_dev->max_q_depth = aic_dev->temp_q_depth = 1;
            /*
             * We set this command up as a bus device reset.  However, we have
             * to clear the tag type as it's causing us problems.  We shouldnt
             * have to worry about any other commands being active, since if
             * the device is refusing tagged commands, this should be the
             * first tagged command sent to the device, however, we do have
             * to worry about any other tagged commands that may already be
             * in the qinfifo.  The easiest way to do this, is to issue a BDR,
             * send all the commands back to the mid level code, then let them
             * come back and get rebuilt as untagged commands.
             */
            scb->tag_action = 0;
            scb->hscb->control &= ~(TAG_ENB | SCB_TAG_TYPE);
            aic_outb(p,  scb->hscb->control, SCB_CONTROL);

            old_verbose = aic7xxx_verbose;
            aic7xxx_verbose &= ~(VERBOSE_RESET|VERBOSE_ABORT);
            for (i=0; i < p->scb_data->numscbs; i++)
            {
              scbp = p->scb_data->scb_array[i];
              if ((scbp->flags & SCB_ACTIVE) && (scbp != scb))
              {
                if (aic7xxx_match_scb(p, scbp, target, channel, lun, i))
                {
                  aic7xxx_reset_device(p, target, channel, lun, i);
                }
              }
            }
            aic7xxx_run_done_queue(p, TRUE);
            aic7xxx_verbose = old_verbose;
            /*
             * Wait until after the for loop to set the busy index since
             * aic7xxx_reset_device will clear the busy index during its
             * operation.
             */
            aic7xxx_busy_target(p, scb);
            printk(INFO_LEAD "Device is refusing tagged commands, using "
              "untagged I/O.\n", p->host_no, channel, target, lun);
            aic_outb(p, MSG_IDENTIFYFLAG, MSG_OUT);
            aic_outb(p, aic_inb(p, SCSISIGI) | ATNO, SCSISIGO);
          }
        }
        else if (scb->flags & SCB_MSGOUT_PPR)
        {
          /*
           * As per the draft specs, any device capable of supporting any of
           * the option values other than 0 are not allowed to reject the
           * PPR message.  Instead, they must negotiate out what they do
           * support instead of rejecting our offering or else they cause
           * a parity error during msg_out phase to signal that they don't
           * like our settings.
           */
          aic_dev->needppr = aic_dev->needppr_copy = 0;
          aic7xxx_set_width(p, target, channel, lun, MSG_EXT_WDTR_BUS_8_BIT,
            (AHC_TRANS_ACTIVE|AHC_TRANS_CUR|AHC_TRANS_QUITE), aic_dev);
          aic7xxx_set_syncrate(p, NULL, target, channel, 0, 0, 0,
                               AHC_TRANS_ACTIVE|AHC_TRANS_CUR|AHC_TRANS_QUITE,
			       aic_dev);
          aic_dev->goal.options = aic_dev->dtr_pending = 0;
          scb->flags &= ~SCB_MSGOUT_BITS;
          if(aic7xxx_verbose & VERBOSE_NEGOTIATION2)
          {
            printk(INFO_LEAD "Device is rejecting PPR messages, falling "
              "back.\n", p->host_no, channel, target, lun);
          }
          if ( aic_dev->goal.width )
          {
            aic_dev->needwdtr = aic_dev->needwdtr_copy = 1;
            aic_dev->dtr_pending = 1;
            scb->flags |= SCB_MSGOUT_WDTR;
          }
          if ( aic_dev->goal.offset )
          {
            aic_dev->needsdtr = aic_dev->needsdtr_copy = 1;
            if( !aic_dev->dtr_pending )
            {
              aic_dev->dtr_pending = 1;
              scb->flags |= SCB_MSGOUT_SDTR;
            }
          }
          if ( aic_dev->dtr_pending )
          {
            aic_outb(p, HOST_MSG, MSG_OUT);
            aic_outb(p, aic_inb(p, SCSISIGI) | ATNO, SCSISIGO);
          }
        }
        else if (scb->flags & SCB_MSGOUT_WDTR)
        {
          /*
           * note 8bit xfers and clear flag
           */
          aic_dev->needwdtr = aic_dev->needwdtr_copy = 0;
          scb->flags &= ~SCB_MSGOUT_BITS;
          aic7xxx_set_width(p, target, channel, lun, MSG_EXT_WDTR_BUS_8_BIT,
            (AHC_TRANS_ACTIVE|AHC_TRANS_GOAL|AHC_TRANS_CUR), aic_dev);
          aic7xxx_set_syncrate(p, NULL, target, channel, 0, 0, 0,
                               AHC_TRANS_ACTIVE|AHC_TRANS_CUR|AHC_TRANS_QUITE,
			       aic_dev);
          if(aic7xxx_verbose & VERBOSE_NEGOTIATION2)
          {
            printk(INFO_LEAD "Device is rejecting WDTR messages, using "
              "narrow transfers.\n", p->host_no, channel, target, lun);
          }
          aic_dev->needsdtr = aic_dev->needsdtr_copy;
        }
        else if (scb->flags & SCB_MSGOUT_SDTR)
        {
         /*
          * note asynch xfers and clear flag
          */
          aic_dev->needsdtr = aic_dev->needsdtr_copy = 0;
          scb->flags &= ~SCB_MSGOUT_BITS;
          aic7xxx_set_syncrate(p, NULL, target, channel, 0, 0, 0,
            (AHC_TRANS_CUR|AHC_TRANS_ACTIVE|AHC_TRANS_GOAL), aic_dev);
          if(aic7xxx_verbose & VERBOSE_NEGOTIATION2)
          {
            printk(INFO_LEAD "Device is rejecting SDTR messages, using "
              "async transfers.\n", p->host_no, channel, target, lun);
          }
        }
        else if (aic7xxx_verbose & VERBOSE_SEQINT)
        {
          /*
           * Otherwise, we ignore it.
           */
          printk(INFO_LEAD "Received MESSAGE_REJECT for unknown cause.  "
            "Ignoring.\n", p->host_no, channel, target, lun);
        }
      }
      break;

    case BAD_STATUS:
      {
	unsigned char scb_index;
	struct aic7xxx_hwscb *hscb;
	struct scsi_cmnd *cmd;

	/* The sequencer will notify us when a command has an error that
	 * would be of interest to the kernel.  This allows us to leave
	 * the sequencer running in the common case of command completes
	 * without error.  The sequencer will have DMA'd the SCB back
	 * up to us, so we can reference the drivers SCB array.
	 *
	 * Set the default return value to 0 indicating not to send
	 * sense.  The sense code will change this if needed and this
	 * reduces code duplication.
	 */
        aic_outb(p, 0, RETURN_1);
        scb_index = aic_inb(p, SCB_TAG);
        if (scb_index > p->scb_data->numscbs)
        {
          printk(WARN_LEAD "Invalid SCB during SEQINT 0x%02x, SCB_TAG %d.\n",
            p->host_no, channel, target, lun, intstat, scb_index);
          break;
        }
        scb = p->scb_data->scb_array[scb_index];
        hscb = scb->hscb;

        if (!(scb->flags & SCB_ACTIVE) || (scb->cmd == NULL))
        {
          printk(WARN_LEAD "Invalid SCB during SEQINT 0x%x, scb %d, flags 0x%x,"
            " cmd 0x%lx.\n", p->host_no, channel, target, lun, intstat,
            scb_index, scb->flags, (unsigned long) scb->cmd);
        }
        else
        {
          cmd = scb->cmd;
	  aic_dev = AIC_DEV(scb->cmd);
          hscb->target_status = aic_inb(p, SCB_TARGET_STATUS);
          aic7xxx_status(cmd) = hscb->target_status;

          cmd->result = hscb->target_status;

          switch (status_byte(hscb->target_status))
          {
            case GOOD:
              if (aic7xxx_verbose & VERBOSE_SEQINT)
                printk(INFO_LEAD "Interrupted for status of GOOD???\n",
                  p->host_no, CTL_OF_SCB(scb));
              break;

            case COMMAND_TERMINATED:
            case CHECK_CONDITION:
              if ( !(scb->flags & SCB_SENSE) )
              {
                /*
                 * Send a sense command to the requesting target.
                 * XXX - revisit this and get rid of the memcopys.
                 */
                memcpy(scb->sense_cmd, &generic_sense[0],
                       sizeof(generic_sense));

                scb->sense_cmd[1] = (cmd->device->lun << 5);
                scb->sense_cmd[4] = SCSI_SENSE_BUFFERSIZE;

                scb->sg_list[0].length = 
                  cpu_to_le32(SCSI_SENSE_BUFFERSIZE);
		scb->sg_list[0].address =
                        cpu_to_le32(pci_map_single(p->pdev, cmd->sense_buffer,
                                                   SCSI_SENSE_BUFFERSIZE,
                                                   PCI_DMA_FROMDEVICE));

                /*
                 * XXX - We should allow disconnection, but can't as it
                 * might allow overlapped tagged commands.
                 */
                /* hscb->control &= DISCENB; */
                hscb->control = 0;
                hscb->target_status = 0;
                hscb->SG_list_pointer = 
		  cpu_to_le32(SCB_DMA_ADDR(scb, scb->sg_list));
                hscb->SCSI_cmd_pointer = 
                  cpu_to_le32(SCB_DMA_ADDR(scb, scb->sense_cmd));
                hscb->data_count = scb->sg_list[0].length;
                hscb->data_pointer = scb->sg_list[0].address;
                hscb->SCSI_cmd_length = COMMAND_SIZE(scb->sense_cmd[0]);
                hscb->residual_SG_segment_count = 0;
                hscb->residual_data_count[0] = 0;
                hscb->residual_data_count[1] = 0;
                hscb->residual_data_count[2] = 0;

                scb->sg_count = hscb->SG_segment_count = 1;
                scb->sg_length = SCSI_SENSE_BUFFERSIZE;
                scb->tag_action = 0;
                scb->flags |= SCB_SENSE;
                /*
                 * Ensure the target is busy since this will be an
                 * an untagged request.
                 */
#ifdef AIC7XXX_VERBOSE_DEBUGGING
                if (aic7xxx_verbose & VERBOSE_NEGOTIATION2)
                {
                  if (scb->flags & SCB_MSGOUT_BITS)
                    printk(INFO_LEAD "Requesting SENSE with %s\n", p->host_no,
                           CTL_OF_SCB(scb), (scb->flags & SCB_MSGOUT_SDTR) ?
                           "SDTR" : "WDTR");
                  else
                    printk(INFO_LEAD "Requesting SENSE, no MSG\n", p->host_no,
                           CTL_OF_SCB(scb));
                }
#endif
                aic7xxx_busy_target(p, scb);
                aic_outb(p, SEND_SENSE, RETURN_1);
                aic7xxx_error(cmd) = DID_OK;
                break;
              }  /* first time sense, no errors */
              printk(INFO_LEAD "CHECK_CONDITION on REQUEST_SENSE, returning "
                     "an error.\n", p->host_no, CTL_OF_SCB(scb));
              aic7xxx_error(cmd) = DID_ERROR;
              scb->flags &= ~SCB_SENSE;
              break;

            case QUEUE_FULL:
              queue_flag = TRUE;    /* Mark that this is a QUEUE_FULL and */
            case BUSY:              /* drop through to here */
            {
              struct aic7xxx_scb *next_scbp, *prev_scbp;
              unsigned char active_hscb, next_hscb, prev_hscb, scb_index;
              /*
               * We have to look three places for queued commands:
               *  1: p->waiting_scbs queue
               *  2: QINFIFO
               *  3: WAITING_SCBS list on card (for commands that are started
               *     but haven't yet made it to the device)
	       *
	       * Of special note here is that commands on 2 or 3 above will
	       * have already been marked as active, while commands on 1 will
	       * not.  The aic7xxx_done() function will want to unmark them
	       * from active, so any commands we pull off of 1 need to
	       * up the active count.
               */
              next_scbp = p->waiting_scbs.head;
              while ( next_scbp != NULL )
              {
                prev_scbp = next_scbp;
                next_scbp = next_scbp->q_next;
                if ( aic7xxx_match_scb(p, prev_scbp, target, channel, lun,
                     SCB_LIST_NULL) )
                {
                  scbq_remove(&p->waiting_scbs, prev_scbp);
		  scb->flags = SCB_QUEUED_FOR_DONE | SCB_QUEUE_FULL;
		  p->activescbs++;
		  aic_dev->active_cmds++;
                }
              }
              aic7xxx_search_qinfifo(p, target, channel, lun,
                SCB_LIST_NULL, SCB_QUEUED_FOR_DONE | SCB_QUEUE_FULL,
	       	FALSE, NULL);
              next_scbp = NULL;
              active_hscb = aic_inb(p, SCBPTR);
              prev_hscb = next_hscb = scb_index = SCB_LIST_NULL;
              next_hscb = aic_inb(p, WAITING_SCBH);
              while (next_hscb != SCB_LIST_NULL)
              {
                aic_outb(p, next_hscb, SCBPTR);
                scb_index = aic_inb(p, SCB_TAG);
                if (scb_index < p->scb_data->numscbs)
                {
                  next_scbp = p->scb_data->scb_array[scb_index];
                  if (aic7xxx_match_scb(p, next_scbp, target, channel, lun,
                      SCB_LIST_NULL) )
                  {
		    next_scbp->flags = SCB_QUEUED_FOR_DONE | SCB_QUEUE_FULL;
                    next_hscb = aic_inb(p, SCB_NEXT);
                    aic_outb(p, 0, SCB_CONTROL);
                    aic_outb(p, SCB_LIST_NULL, SCB_TAG);
                    aic7xxx_add_curscb_to_free_list(p);
                    if (prev_hscb == SCB_LIST_NULL)
                    {
                      /* We were first on the list,
                       * so we kill the selection
                       * hardware.  Let the sequencer
                       * re-init the hardware itself
                       */
                      aic_outb(p, aic_inb(p, SCSISEQ) & ~ENSELO, SCSISEQ);
                      aic_outb(p, CLRSELTIMEO, CLRSINT1);
                      aic_outb(p, next_hscb, WAITING_SCBH);
                    }
                    else
                    {
                      aic_outb(p, prev_hscb, SCBPTR);
                      aic_outb(p, next_hscb, SCB_NEXT);
                    }
                  }
                  else
                  {
                    prev_hscb = next_hscb;
                    next_hscb = aic_inb(p, SCB_NEXT);
                  }
                } /* scb_index >= p->scb_data->numscbs */
              }
              aic_outb(p, active_hscb, SCBPTR);
	      aic7xxx_run_done_queue(p, FALSE);
                  
#ifdef AIC7XXX_VERBOSE_DEBUGGING
              if( (aic7xxx_verbose & VERBOSE_MINOR_ERROR) ||
                  (aic7xxx_verbose > 0xffff) )
              {
                if (queue_flag)
                  printk(INFO_LEAD "Queue full received; queue depth %d, "
                    "active %d\n", p->host_no, CTL_OF_SCB(scb),
                    aic_dev->max_q_depth, aic_dev->active_cmds);
                else
                  printk(INFO_LEAD "Target busy\n", p->host_no, CTL_OF_SCB(scb));
              }
#endif
              if (queue_flag)
              {
		int diff;
		result = scsi_track_queue_full(cmd->device,
			       	aic_dev->active_cmds);
		if ( result < 0 )
		{
                  if (aic7xxx_verbose & VERBOSE_NEGOTIATION2)
                    printk(INFO_LEAD "Tagged Command Queueing disabled.\n",
			p->host_no, CTL_OF_SCB(scb));
		  diff = aic_dev->max_q_depth - p->host->cmd_per_lun;
		  aic_dev->temp_q_depth = 1;
		  aic_dev->max_q_depth = 1;
		}
		else if ( result > 0 )
		{
                  if (aic7xxx_verbose & VERBOSE_NEGOTIATION2)
                    printk(INFO_LEAD "Queue depth reduced to %d\n", p->host_no,
                      CTL_OF_SCB(scb), result);
		  diff = aic_dev->max_q_depth - result;
		  aic_dev->max_q_depth = result;
		  /* temp_q_depth could have been dropped to 1 for an untagged
		   * command that might be coming up */
		  if(aic_dev->temp_q_depth > result)
		    aic_dev->temp_q_depth = result;
		}
		/* We should free up the no unused SCB entries.  But, that's
		 * a difficult thing to do because we use a direct indexed
		 * array, so we can't just take any entries and free them,
		 * we *have* to free the ones at the end of the array, and
		 * they very well could be in use right now, which means
		 * in order to do this right, we have to add a delayed
		 * freeing mechanism tied into the scb_free() code area.
		 * We'll add that later.
		 */
	      }
              break;
            }
            
            default:
              if (aic7xxx_verbose & VERBOSE_SEQINT)
                printk(INFO_LEAD "Unexpected target status 0x%x.\n", p->host_no,
                     CTL_OF_SCB(scb), scb->hscb->target_status);
              if (!aic7xxx_error(cmd))
              {
                aic7xxx_error(cmd) = DID_RETRY_COMMAND;
              }
              break;
          }  /* end switch */
        }  /* end else of */
      }
      break;

    case AWAITING_MSG:
      {
        unsigned char scb_index, msg_out;

        scb_index = aic_inb(p, SCB_TAG);
        msg_out = aic_inb(p, MSG_OUT);
        scb = p->scb_data->scb_array[scb_index];
	aic_dev = AIC_DEV(scb->cmd);
        p->msg_index = p->msg_len = 0;
        /*
         * This SCB had a MK_MESSAGE set in its control byte informing
         * the sequencer that we wanted to send a special message to
         * this target.
         */

        if ( !(scb->flags & SCB_DEVICE_RESET) &&
              (msg_out == MSG_IDENTIFYFLAG) &&
              (scb->hscb->control & TAG_ENB) )
        {
          p->msg_buf[p->msg_index++] = scb->tag_action;
          p->msg_buf[p->msg_index++] = scb->hscb->tag;
          p->msg_len += 2;
        }

        if (scb->flags & SCB_DEVICE_RESET)
        {
          p->msg_buf[p->msg_index++] = MSG_BUS_DEV_RESET;
          p->msg_len++;
          if (aic7xxx_verbose & VERBOSE_RESET_PROCESS)
            printk(INFO_LEAD "Bus device reset mailed.\n",
                 p->host_no, CTL_OF_SCB(scb));
        }
        else if (scb->flags & SCB_ABORT)
        {
          if (scb->tag_action)
          {
            p->msg_buf[p->msg_index++] = MSG_ABORT_TAG;
          }
          else
          {
            p->msg_buf[p->msg_index++] = MSG_ABORT;
          }
          p->msg_len++;
          if (aic7xxx_verbose & VERBOSE_ABORT_PROCESS)
            printk(INFO_LEAD "Abort message mailed.\n", p->host_no,
              CTL_OF_SCB(scb));
        }
        else if (scb->flags & SCB_MSGOUT_PPR)
        {
          if (aic7xxx_verbose & VERBOSE_NEGOTIATION2)
          {
            printk(INFO_LEAD "Sending PPR (%d/%d/%d/%d) message.\n",
                   p->host_no, CTL_OF_SCB(scb),
                   aic_dev->goal.period,
                   aic_dev->goal.offset,
                   aic_dev->goal.width,
                   aic_dev->goal.options);
          }
          aic7xxx_construct_ppr(p, scb);
        }
        else if (scb->flags & SCB_MSGOUT_WDTR)
        {
          if (aic7xxx_verbose & VERBOSE_NEGOTIATION2)
          {
            printk(INFO_LEAD "Sending WDTR message.\n", p->host_no,
                   CTL_OF_SCB(scb));
          }
          aic7xxx_construct_wdtr(p, aic_dev->goal.width);
        }
        else if (scb->flags & SCB_MSGOUT_SDTR)
        {
          unsigned int max_sync, period;
          unsigned char options = 0;
          /*
           * Now that the device is selected, use the bits in SBLKCTL and
           * SSTAT2 to determine the max sync rate for this device.
           */
          if (p->features & AHC_ULTRA2)
          {
            if ( (aic_inb(p, SBLKCTL) & ENAB40) &&
                !(aic_inb(p, SSTAT2) & EXP_ACTIVE) )
            {
              max_sync = AHC_SYNCRATE_ULTRA2;
            }
            else
            {
              max_sync = AHC_SYNCRATE_ULTRA;
            }
          }
          else if (p->features & AHC_ULTRA)
          {
            max_sync = AHC_SYNCRATE_ULTRA;
          }
          else
          {
            max_sync = AHC_SYNCRATE_FAST;
          }
          period = aic_dev->goal.period;
          aic7xxx_find_syncrate(p, &period, max_sync, &options);
          if (aic7xxx_verbose & VERBOSE_NEGOTIATION2)
          {
            printk(INFO_LEAD "Sending SDTR %d/%d message.\n", p->host_no,
                   CTL_OF_SCB(scb), period,
                   aic_dev->goal.offset);
          }
          aic7xxx_construct_sdtr(p, period, aic_dev->goal.offset);
        }
        else 
        {
          panic("aic7xxx: AWAITING_MSG for an SCB that does "
                "not have a waiting message.\n");
        }
        /*
         * We've set everything up to send our message, now to actually do
         * so we need to enable reqinit interrupts and let the interrupt
         * handler do the rest.  We don't want to unpause the sequencer yet
         * though so we'll return early.  We also have to make sure that
         * we clear the SEQINT *BEFORE* we set the REQINIT handler active
         * or else it's possible on VLB cards to lose the first REQINIT
         * interrupt.  Edge triggered EISA cards could also lose this
         * interrupt, although PCI and level triggered cards should not
         * have this problem since they continually interrupt the kernel
         * until we take care of the situation.
         */
        scb->flags |= SCB_MSGOUT_SENT;
        p->msg_index = 0;
        p->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
        p->flags |= AHC_HANDLING_REQINITS;
        aic_outb(p, aic_inb(p, SIMODE1) | ENREQINIT, SIMODE1);
        return;
      }
      break;

    case DATA_OVERRUN:
      {
        unsigned char scb_index = aic_inb(p, SCB_TAG);
        unsigned char lastphase = aic_inb(p, LASTPHASE);
        unsigned int i;

        scb = (p->scb_data->scb_array[scb_index]);
        /*
         * XXX - What do we really want to do on an overrun?  The
         *       mid-level SCSI code should handle this, but for now,
         *       we'll just indicate that the command should retried.
         *    If we retrieved sense info on this target, then the 
         *    base SENSE info should have been saved prior to the
         *    overrun error.  In that case, we return DID_OK and let
         *    the mid level code pick up on the sense info.  Otherwise
         *    we return DID_ERROR so the command will get retried.
         */
        if ( !(scb->flags & SCB_SENSE) )
        {
          printk(WARN_LEAD "Data overrun detected in %s phase, tag %d;\n",
            p->host_no, CTL_OF_SCB(scb), 
            (lastphase == P_DATAIN) ? "Data-In" : "Data-Out", scb->hscb->tag);
          printk(KERN_WARNING "  %s seen Data Phase. Length=%d, NumSGs=%d.\n",
            (aic_inb(p, SEQ_FLAGS) & DPHASE) ? "Have" : "Haven't",
            scb->sg_length, scb->sg_count);
          printk(KERN_WARNING "  Raw SCSI Command: 0x");
          for (i = 0; i < scb->hscb->SCSI_cmd_length; i++)
          {
            printk("%02x ", scb->cmd->cmnd[i]);
          }
          printk("\n");
          if(aic7xxx_verbose > 0xffff)
          {
            for (i = 0; i < scb->sg_count; i++)
            {
              printk(KERN_WARNING "     sg[%d] - Addr 0x%x : Length %d\n",
                 i, 
                 le32_to_cpu(scb->sg_list[i].address),
                 le32_to_cpu(scb->sg_list[i].length) );
            }
          }
          aic7xxx_error(scb->cmd) = DID_ERROR;
        }
        else
          printk(INFO_LEAD "Data Overrun during SEND_SENSE operation.\n",
            p->host_no, CTL_OF_SCB(scb));
      }
      break;

    case WIDE_RESIDUE:
      {
        unsigned char resid_sgcnt, index;
        unsigned char scb_index = aic_inb(p, SCB_TAG);
        unsigned int cur_addr, resid_dcnt;
        unsigned int native_addr, native_length, sg_addr;
        int i;

        if(scb_index > p->scb_data->numscbs)
        {
          printk(WARN_LEAD "invalid scb_index during WIDE_RESIDUE.\n",
            p->host_no, -1, -1, -1);
          /*
           * XXX: Add error handling here
           */
          break;
        }
        scb = p->scb_data->scb_array[scb_index];
        if(!(scb->flags & SCB_ACTIVE) || (scb->cmd == NULL))
        {
          printk(WARN_LEAD "invalid scb during WIDE_RESIDUE flags:0x%x "
                 "scb->cmd:0x%lx\n", p->host_no, CTL_OF_SCB(scb),
                 scb->flags, (unsigned long)scb->cmd);
          break;
        }
        if(aic7xxx_verbose & VERBOSE_MINOR_ERROR)
          printk(INFO_LEAD "Got WIDE_RESIDUE message, patching up data "
                 "pointer.\n", p->host_no, CTL_OF_SCB(scb));

        /*
         * We have a valid scb to use on this WIDE_RESIDUE message, so
         * we need to walk the sg list looking for this particular sg
         * segment, then see if we happen to be at the very beginning of
         * the segment.  If we are, then we have to back things up to
         * the previous segment.  If not, then we simply need to remove
         * one byte from this segments address and add one to the byte
         * count.
         */
        cur_addr = aic_inb(p, SHADDR) | (aic_inb(p, SHADDR + 1) << 8) |
          (aic_inb(p, SHADDR + 2) << 16) | (aic_inb(p, SHADDR + 3) << 24);
        sg_addr = aic_inb(p, SG_COUNT + 1) | (aic_inb(p, SG_COUNT + 2) << 8) |
          (aic_inb(p, SG_COUNT + 3) << 16) | (aic_inb(p, SG_COUNT + 4) << 24);
        resid_sgcnt = aic_inb(p, SCB_RESID_SGCNT);
        resid_dcnt = aic_inb(p, SCB_RESID_DCNT) |
          (aic_inb(p, SCB_RESID_DCNT + 1) << 8) |
          (aic_inb(p, SCB_RESID_DCNT + 2) << 16);
        index = scb->sg_count - ((resid_sgcnt) ? resid_sgcnt : 1);
        native_addr = le32_to_cpu(scb->sg_list[index].address);
        native_length = le32_to_cpu(scb->sg_list[index].length);
        /*
         * If resid_dcnt == native_length, then we just loaded this SG
         * segment and we need to back it up one...
         */
        if(resid_dcnt == native_length)
        {
          if(index == 0)
          {
            /*
             * Oops, this isn't right, we can't back up to before the
             * beginning.  This must be a bogus message, ignore it.
             */
            break;
          }
          resid_dcnt = 1;
          resid_sgcnt += 1;
          native_addr = le32_to_cpu(scb->sg_list[index - 1].address);
          native_length = le32_to_cpu(scb->sg_list[index - 1].length);
          cur_addr = native_addr + (native_length - 1);
          sg_addr -= sizeof(struct hw_scatterlist);
        }
        else
        {
          /*
           * resid_dcnt != native_length, so we are in the middle of a SG
           * element.  Back it up one byte and leave the rest alone.
           */
          resid_dcnt += 1;
          cur_addr -= 1;
        }
        
        /*
         * Output the new addresses and counts to the right places on the
         * card.
         */
        aic_outb(p, resid_sgcnt, SG_COUNT);
        aic_outb(p, resid_sgcnt, SCB_RESID_SGCNT);
        aic_outb(p, sg_addr & 0xff, SG_COUNT + 1);
        aic_outb(p, (sg_addr >> 8) & 0xff, SG_COUNT + 2);
        aic_outb(p, (sg_addr >> 16) & 0xff, SG_COUNT + 3);
        aic_outb(p, (sg_addr >> 24) & 0xff, SG_COUNT + 4);
        aic_outb(p, resid_dcnt & 0xff, SCB_RESID_DCNT);
        aic_outb(p, (resid_dcnt >> 8) & 0xff, SCB_RESID_DCNT + 1);
        aic_outb(p, (resid_dcnt >> 16) & 0xff, SCB_RESID_DCNT + 2);

        /*
         * The sequencer actually wants to find the new address
         * in the SHADDR register set.  On the Ultra2 and later controllers
         * this register set is readonly.  In order to get the right number
         * into the register, you actually have to enter it in HADDR and then
         * use the PRELOADEN bit of DFCNTRL to drop it through from the
         * HADDR register to the SHADDR register.  On non-Ultra2 controllers,
         * we simply write it direct.
         */
        if(p->features & AHC_ULTRA2)
        {
          /*
           * We might as well be accurate and drop both the resid_dcnt and
           * cur_addr into HCNT and HADDR and have both of them drop
           * through to the shadow layer together.
           */
          aic_outb(p, resid_dcnt & 0xff, HCNT);
          aic_outb(p, (resid_dcnt >> 8) & 0xff, HCNT + 1);
          aic_outb(p, (resid_dcnt >> 16) & 0xff, HCNT + 2);
          aic_outb(p, cur_addr & 0xff, HADDR);
          aic_outb(p, (cur_addr >> 8) & 0xff, HADDR + 1);
          aic_outb(p, (cur_addr >> 16) & 0xff, HADDR + 2);
          aic_outb(p, (cur_addr >> 24) & 0xff, HADDR + 3);
          aic_outb(p, aic_inb(p, DMAPARAMS) | PRELOADEN, DFCNTRL);
          udelay(1);
          aic_outb(p, aic_inb(p, DMAPARAMS) & ~(SCSIEN|HDMAEN), DFCNTRL);
          i=0;
          while(((aic_inb(p, DFCNTRL) & (SCSIEN|HDMAEN)) != 0) && (i++ < 1000))
          {
            udelay(1);
          }
        }
        else
        {
          aic_outb(p, cur_addr & 0xff, SHADDR);
          aic_outb(p, (cur_addr >> 8) & 0xff, SHADDR + 1);
          aic_outb(p, (cur_addr >> 16) & 0xff, SHADDR + 2);
          aic_outb(p, (cur_addr >> 24) & 0xff, SHADDR + 3);
        }
      }
      break;

    case SEQ_SG_FIXUP:
    {
      unsigned char scb_index, tmp;
      int sg_addr, sg_length;

      scb_index = aic_inb(p, SCB_TAG);

      if(scb_index > p->scb_data->numscbs)
      {
        printk(WARN_LEAD "invalid scb_index during SEQ_SG_FIXUP.\n",
          p->host_no, -1, -1, -1);
        printk(INFO_LEAD "SCSISIGI 0x%x, SEQADDR 0x%x, SSTAT0 0x%x, SSTAT1 "
           "0x%x\n", p->host_no, -1, -1, -1,
           aic_inb(p, SCSISIGI),
           aic_inb(p, SEQADDR0) | (aic_inb(p, SEQADDR1) << 8),
           aic_inb(p, SSTAT0), aic_inb(p, SSTAT1));
        printk(INFO_LEAD "SG_CACHEPTR 0x%x, SSTAT2 0x%x, STCNT 0x%x\n",
           p->host_no, -1, -1, -1, aic_inb(p, SG_CACHEPTR),
           aic_inb(p, SSTAT2), aic_inb(p, STCNT + 2) << 16 |
           aic_inb(p, STCNT + 1) << 8 | aic_inb(p, STCNT));
        /*
         * XXX: Add error handling here
         */
        break;
      }
      scb = p->scb_data->scb_array[scb_index];
      if(!(scb->flags & SCB_ACTIVE) || (scb->cmd == NULL))
      {
        printk(WARN_LEAD "invalid scb during SEQ_SG_FIXUP flags:0x%x "
               "scb->cmd:0x%p\n", p->host_no, CTL_OF_SCB(scb),
               scb->flags, scb->cmd);
        printk(INFO_LEAD "SCSISIGI 0x%x, SEQADDR 0x%x, SSTAT0 0x%x, SSTAT1 "
           "0x%x\n", p->host_no, CTL_OF_SCB(scb),
           aic_inb(p, SCSISIGI),
           aic_inb(p, SEQADDR0) | (aic_inb(p, SEQADDR1) << 8),
           aic_inb(p, SSTAT0), aic_inb(p, SSTAT1));
        printk(INFO_LEAD "SG_CACHEPTR 0x%x, SSTAT2 0x%x, STCNT 0x%x\n",
           p->host_no, CTL_OF_SCB(scb), aic_inb(p, SG_CACHEPTR),
           aic_inb(p, SSTAT2), aic_inb(p, STCNT + 2) << 16 |
           aic_inb(p, STCNT + 1) << 8 | aic_inb(p, STCNT));
        break;
      }
      if(aic7xxx_verbose & VERBOSE_MINOR_ERROR)
        printk(INFO_LEAD "Fixing up SG address for sequencer.\n", p->host_no,
               CTL_OF_SCB(scb));
      /*
       * Advance the SG pointer to the next element in the list
       */
      tmp = aic_inb(p, SG_NEXT);
      tmp += SG_SIZEOF;
      aic_outb(p, tmp, SG_NEXT);
      if( tmp < SG_SIZEOF )
        aic_outb(p, aic_inb(p, SG_NEXT + 1) + 1, SG_NEXT + 1);
      tmp = aic_inb(p, SG_COUNT) - 1;
      aic_outb(p, tmp, SG_COUNT);
      sg_addr = le32_to_cpu(scb->sg_list[scb->sg_count - tmp].address);
      sg_length = le32_to_cpu(scb->sg_list[scb->sg_count - tmp].length);
      /*
       * Now stuff the element we just advanced past down onto the
       * card so it can be stored in the residual area.
       */
      aic_outb(p, sg_addr & 0xff, HADDR);
      aic_outb(p, (sg_addr >> 8) & 0xff, HADDR + 1);
      aic_outb(p, (sg_addr >> 16) & 0xff, HADDR + 2);
      aic_outb(p, (sg_addr >> 24) & 0xff, HADDR + 3);
      aic_outb(p, sg_length & 0xff, HCNT);
      aic_outb(p, (sg_length >> 8) & 0xff, HCNT + 1);
      aic_outb(p, (sg_length >> 16) & 0xff, HCNT + 2);
      aic_outb(p, (tmp << 2) | ((tmp == 1) ? LAST_SEG : 0), SG_CACHEPTR);
      aic_outb(p, aic_inb(p, DMAPARAMS), DFCNTRL);
      while(aic_inb(p, SSTAT0) & SDONE) udelay(1);
      while(aic_inb(p, DFCNTRL) & (HDMAEN|SCSIEN)) aic_outb(p, 0, DFCNTRL);
    }
    break;

#ifdef AIC7XXX_NOT_YET 
    case TRACEPOINT2:
      {
        printk(INFO_LEAD "Tracepoint #2 reached.\n", p->host_no,
               channel, target, lun);
      }
      break;

    /* XXX Fill these in later */
    case MSG_BUFFER_BUSY:
      printk("aic7xxx: Message buffer busy.\n");
      break;
    case MSGIN_PHASEMIS:
      printk("aic7xxx: Message-in phasemis.\n");
      break;
#endif

    default:                   /* unknown */
      printk(WARN_LEAD "Unknown SEQINT, INTSTAT 0x%x, SCSISIGI 0x%x.\n",
             p->host_no, channel, target, lun, intstat,
             aic_inb(p, SCSISIGI));
      break;
  }
