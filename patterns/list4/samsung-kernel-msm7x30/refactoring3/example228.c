switch ((int) heap_data->type) {
	case ION_HEAP_TYPE_SYSTEM_CONTIG:
		heap = ion_system_contig_heap_create(heap_data);
		break;
	case ION_HEAP_TYPE_SYSTEM:
		heap = ion_system_heap_create(heap_data);
		break;
	case ION_HEAP_TYPE_CARVEOUT:
		heap = ion_carveout_heap_create(heap_data);
		break;
	case ION_HEAP_TYPE_IOMMU:
		heap = ion_iommu_heap_create(heap_data);
		break;
	case ION_HEAP_TYPE_CP:
		heap = ion_cp_heap_create(heap_data);
		break;
#ifdef CONFIG_CMA
	case ION_HEAP_TYPE_DMA:
		heap = ion_cma_heap_create(heap_data);
		break;
#endif
	default:
		pr_err("%s: Invalid heap type %d\n", __func__,
		       heap_data->type);
		return ERR_PTR(-EINVAL);
	}
