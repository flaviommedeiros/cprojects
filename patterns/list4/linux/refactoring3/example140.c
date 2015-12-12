switch (vsi->type) {
	case I40E_VSI_MAIN:
		vsi->alloc_queue_pairs = pf->num_lan_qps;
		vsi->num_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
				      I40E_REQ_DESCRIPTOR_MULTIPLE);
		if (pf->flags & I40E_FLAG_MSIX_ENABLED)
			vsi->num_q_vectors = pf->num_lan_msix;
		else
			vsi->num_q_vectors = 1;

		break;

	case I40E_VSI_FDIR:
		vsi->alloc_queue_pairs = 1;
		vsi->num_desc = ALIGN(I40E_FDIR_RING_COUNT,
				      I40E_REQ_DESCRIPTOR_MULTIPLE);
		vsi->num_q_vectors = 1;
		break;

	case I40E_VSI_VMDQ2:
		vsi->alloc_queue_pairs = pf->num_vmdq_qps;
		vsi->num_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
				      I40E_REQ_DESCRIPTOR_MULTIPLE);
		vsi->num_q_vectors = pf->num_vmdq_msix;
		break;

	case I40E_VSI_SRIOV:
		vsi->alloc_queue_pairs = pf->num_vf_qps;
		vsi->num_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
				      I40E_REQ_DESCRIPTOR_MULTIPLE);
		break;

#ifdef I40E_FCOE
	case I40E_VSI_FCOE:
		vsi->alloc_queue_pairs = pf->num_fcoe_qps;
		vsi->num_desc = ALIGN(I40E_DEFAULT_NUM_DESCRIPTORS,
				      I40E_REQ_DESCRIPTOR_MULTIPLE);
		vsi->num_q_vectors = pf->num_fcoe_msix;
		break;

#endif /* I40E_FCOE */
	default:
		WARN_ON(1);
		return -ENODATA;
	}
