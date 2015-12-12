#ifdef CONFIG_BLK_DEV_INTEGRITY
if (virtio_has_feature(vscsi->vdev, VIRTIO_SCSI_F_T10_PI)) {
		virtio_scsi_init_hdr_pi(vscsi->vdev, &cmd->req.cmd_pi, sc);
		memcpy(cmd->req.cmd_pi.cdb, sc->cmnd, sc->cmd_len);
		req_size = sizeof(cmd->req.cmd_pi);
	} else
#endif
	{
		virtio_scsi_init_hdr(vscsi->vdev, &cmd->req.cmd, sc);
		memcpy(cmd->req.cmd.cdb, sc->cmnd, sc->cmd_len);
		req_size = sizeof(cmd->req.cmd);
	}
