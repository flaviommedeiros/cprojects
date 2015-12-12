#ifdef BCM_CNIC
if (IS_FCOE_IDX(fp_index)) {
		memset(sb, 0, sizeof(union host_hc_status_block));
		fp->status_blk_mapping = 0;

	} else {
#endif
		/* status blocks */
		if (!CHIP_IS_E1x(bp))
			BNX2X_PCI_FREE(sb->e2_sb,
				       bnx2x_fp(bp, fp_index,
						status_blk_mapping),
				       sizeof(struct host_hc_status_block_e2));
		else
			BNX2X_PCI_FREE(sb->e1x_sb,
				       bnx2x_fp(bp, fp_index,
						status_blk_mapping),
				       sizeof(struct host_hc_status_block_e1x));
#ifdef BCM_CNIC
	}
