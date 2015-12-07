#ifdef CONFIG_I2O_EXT_ADAPTEC
if (c->adaptec) {
		u8 cmd[10];
		u32 scsi_flags;
		u16 hwsec;

		hwsec = queue_logical_block_size(req->q) >> KERNEL_SECTOR_SHIFT;
		memset(cmd, 0, 10);

		sgl_offset = SGL_OFFSET_12;

		msg->u.head[1] =
		    cpu_to_le32(I2O_CMD_PRIVATE << 24 | HOST_TID << 12 | tid);

		*mptr++ = cpu_to_le32(I2O_VENDOR_DPT << 16 | I2O_CMD_SCSI_EXEC);
		*mptr++ = cpu_to_le32(tid);

		/*
		 * ENABLE_DISCONNECT
		 * SIMPLE_TAG
		 * RETURN_SENSE_DATA_IN_REPLY_MESSAGE_FRAME
		 */
		if (rq_data_dir(req) == READ) {
			cmd[0] = READ_10;
			scsi_flags = 0x60a0000a;
		} else {
			cmd[0] = WRITE_10;
			scsi_flags = 0xa0a0000a;
		}

		*mptr++ = cpu_to_le32(scsi_flags);

		*((u32 *) & cmd[2]) = cpu_to_be32(blk_rq_pos(req) * hwsec);
		*((u16 *) & cmd[7]) = cpu_to_be16(blk_rq_sectors(req) * hwsec);

		memcpy(mptr, cmd, 10);
		mptr += 4;
		*mptr++ = cpu_to_le32(blk_rq_bytes(req));
	} else
#endif
	{
		msg->u.head[1] = cpu_to_le32(cmd | HOST_TID << 12 | tid);
		*mptr++ = cpu_to_le32(ctl_flags);
		*mptr++ = cpu_to_le32(blk_rq_bytes(req));
		*mptr++ =
		    cpu_to_le32((u32) (blk_rq_pos(req) << KERNEL_SECTOR_SHIFT));
		*mptr++ =
		    cpu_to_le32(blk_rq_pos(req) >> (32 - KERNEL_SECTOR_SHIFT));
	}
