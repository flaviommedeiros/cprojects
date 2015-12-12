static int pxa_videobuf_prepare(struct videobuf_queue *vq,
		struct videobuf_buffer *vb, enum v4l2_field field)
{
	struct soc_camera_device *icd = vq->priv_data;
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct pxa_camera_dev *pcdev = ici->priv;
	struct device *dev = pcdev->soc_host.v4l2_dev.dev;
	struct pxa_buffer *buf = container_of(vb, struct pxa_buffer, vb);
	int ret;
	int size_y, size_u = 0, size_v = 0;

	dev_dbg(dev, "%s (vb=0x%p) 0x%08lx %d\n", __func__,
		vb, vb->baddr, vb->bsize);

	/* Added list head initialization on alloc */
	WARN_ON(!list_empty(&vb->queue));

#ifdef DEBUG
	/*
	 * This can be useful if you want to see if we actually fill
	 * the buffer with something
	 */
	memset((void *)vb->baddr, 0xaa, vb->bsize);
#endif

	BUG_ON(NULL == icd->current_fmt);

	/*
	 * I think, in buf_prepare you only have to protect global data,
	 * the actual buffer is yours
	 */
	buf->inwork = 1;

	if (buf->code	!= icd->current_fmt->code ||
	    vb->width	!= icd->user_width ||
	    vb->height	!= icd->user_height ||
	    vb->field	!= field) {
		buf->code	= icd->current_fmt->code;
		vb->width	= icd->user_width;
		vb->height	= icd->user_height;
		vb->field	= field;
		vb->state	= VIDEOBUF_NEEDS_INIT;
	}

	vb->size = icd->sizeimage;
	if (0 != vb->baddr && vb->bsize < vb->size) {
		ret = -EINVAL;
		goto out;
	}

	if (vb->state == VIDEOBUF_NEEDS_INIT) {
		int size = vb->size;
		int next_ofs = 0;
		struct videobuf_dmabuf *dma = videobuf_to_dma(vb);
		struct scatterlist *sg;

		ret = videobuf_iolock(vq, vb, NULL);
		if (ret)
			goto fail;

		if (pcdev->channels == 3) {
			size_y = size / 2;
			size_u = size_v = size / 4;
		} else {
			size_y = size;
		}

		sg = dma->sglist;

		/* init DMA for Y channel */
		ret = pxa_init_dma_channel(pcdev, buf, dma, 0, CIBR0, size_y,
					   &sg, &next_ofs);
		if (ret) {
			dev_err(dev, "DMA initialization for Y/RGB failed\n");
			goto fail;
		}

		/* init DMA for U channel */
		if (size_u)
			ret = pxa_init_dma_channel(pcdev, buf, dma, 1, CIBR1,
						   size_u, &sg, &next_ofs);
		if (ret) {
			dev_err(dev, "DMA initialization for U failed\n");
			goto fail_u;
		}

		/* init DMA for V channel */
		if (size_v)
			ret = pxa_init_dma_channel(pcdev, buf, dma, 2, CIBR2,
						   size_v, &sg, &next_ofs);
		if (ret) {
			dev_err(dev, "DMA initialization for V failed\n");
			goto fail_v;
		}

		vb->state = VIDEOBUF_PREPARED;
	}

	buf->inwork = 0;
	pxa_videobuf_set_actdma(pcdev, buf);

	return 0;

fail_v:
	dma_free_coherent(dev, buf->dmas[1].sg_size,
			  buf->dmas[1].sg_cpu, buf->dmas[1].sg_dma);
fail_u:
	dma_free_coherent(dev, buf->dmas[0].sg_size,
			  buf->dmas[0].sg_cpu, buf->dmas[0].sg_dma);
fail:
	free_buffer(vq, buf);
out:
	buf->inwork = 0;
	return ret;
}
