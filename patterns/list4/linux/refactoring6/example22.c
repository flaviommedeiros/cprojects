if (
#if !defined(CONFIG_SUN3)
				    !cmd->device->borken &&
#endif
				    (transfersize = NCR5380_dma_xfer_len(instance, cmd, phase)) >= DMA_MIN_SIZE) {
					len = transfersize;
					cmd->SCp.phase = phase;
					if (NCR5380_transfer_dma(instance, &phase,
					    &len, (unsigned char **)&cmd->SCp.ptr)) {
						/*
						 * If the watchdog timer fires, all future
						 * accesses to this device will use the
						 * polled-IO. */
						scmd_printk(KERN_INFO, cmd,
							"switching to slow handshake\n");
						cmd->device->borken = 1;
						NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE |
							ICR_ASSERT_ATN);
						sink = 1;
						do_abort(instance);
						cmd->result = DID_ERROR << 16;
						cmd->scsi_done(cmd);
						/* XXX - need to source or sink data here, as appropriate */
					} else {
#ifdef REAL_DMA
						/* ++roman: When using real DMA,
						 * information_transfer() should return after
						 * starting DMA since it has nothing more to
						 * do.
						 */
						return;
#else
						cmd->SCp.this_residual -= transfersize - len;
#endif
					}
				} else
#endif /* defined(REAL_DMA) */
					NCR5380_transfer_pio(instance, &phase,
							     (int *)&cmd->SCp.this_residual,
							     (unsigned char **)&cmd->SCp.ptr);
