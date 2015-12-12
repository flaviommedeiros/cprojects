static inline int virtqueue_add(struct virtqueue *_vq,
				struct scatterlist *sgs[],
				struct scatterlist *(*next)
				  (struct scatterlist *, unsigned int *),
				unsigned int total_out,
				unsigned int total_in,
				unsigned int out_sgs,
				unsigned int in_sgs,
				void *data,
				gfp_t gfp)
{
	struct vring_virtqueue *vq = to_vvq(_vq);
	struct scatterlist *sg;
	unsigned int i, n, avail, uninitialized_var(prev), total_sg;
	int head;

	START_USE(vq);

	BUG_ON(data == NULL);

#ifdef DEBUG
	{
		ktime_t now = ktime_get();

		/* No kick or get, with .1 second between?  Warn. */
		if (vq->last_add_time_valid)
			WARN_ON(ktime_to_ms(ktime_sub(now, vq->last_add_time))
					    > 100);
		vq->last_add_time = now;
		vq->last_add_time_valid = true;
	}
#endif

	total_sg = total_in + total_out;

	/* If the host supports indirect descriptor tables, and we have multiple
	 * buffers, then go indirect. FIXME: tune this threshold */
	if (vq->indirect && total_sg > 1 && vq->vq.num_free) {
		head = vring_add_indirect(vq, sgs, next, total_sg, total_out,
					  total_in,
					  out_sgs, in_sgs, gfp);
		if (likely(head >= 0))
			goto add_head;
	}

	BUG_ON(total_sg > vq->vring.num);
	BUG_ON(total_sg == 0);

	if (vq->vq.num_free < total_sg) {
		pr_debug("Can't add buf len %i - avail = %i\n",
			 total_sg, vq->vq.num_free);
		/* FIXME: for historical reasons, we force a notify here if
		 * there are outgoing parts to the buffer.  Presumably the
		 * host should service the ring ASAP. */
		if (out_sgs)
			vq->notify(&vq->vq);
		END_USE(vq);
		return -ENOSPC;
	}

	/* We're about to use some buffers from the free list. */
	vq->vq.num_free -= total_sg;

	head = i = vq->free_head;
	for (n = 0; n < out_sgs; n++) {
		for (sg = sgs[n]; sg; sg = next(sg, &total_out)) {
			vq->vring.desc[i].flags = VRING_DESC_F_NEXT;
			vq->vring.desc[i].addr = sg_phys(sg);
			vq->vring.desc[i].len = sg->length;
			prev = i;
			i = vq->vring.desc[i].next;
		}
	}
	for (; n < (out_sgs + in_sgs); n++) {
		for (sg = sgs[n]; sg; sg = next(sg, &total_in)) {
			vq->vring.desc[i].flags = VRING_DESC_F_NEXT|VRING_DESC_F_WRITE;
			vq->vring.desc[i].addr = sg_phys(sg);
			vq->vring.desc[i].len = sg->length;
			prev = i;
			i = vq->vring.desc[i].next;
		}
	}
	/* Last one doesn't continue. */
	vq->vring.desc[prev].flags &= ~VRING_DESC_F_NEXT;

	/* Update free pointer */
	vq->free_head = i;

add_head:
	/* Set token. */
	vq->data[head] = data;

	/* Put entry in available array (but don't update avail->idx until they
	 * do sync). */
	avail = (vq->vring.avail->idx & (vq->vring.num-1));
	vq->vring.avail->ring[avail] = head;

	/* Descriptors and available array need to be set before we expose the
	 * new available array entries. */
	virtio_wmb(vq->weak_barriers);
	vq->vring.avail->idx++;
	vq->num_added++;

	/* This is very unlikely, but theoretically possible.  Kick
	 * just in case. */
	if (unlikely(vq->num_added == (1 << 16) - 1))
		virtqueue_kick(_vq);

	pr_debug("Added buffer head %i to %p\n", head, vq);
	END_USE(vq);

	return 0;
}
