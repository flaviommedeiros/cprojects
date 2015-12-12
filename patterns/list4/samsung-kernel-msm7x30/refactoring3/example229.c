switch ((int) heap->type) {
	case ION_HEAP_TYPE_SYSTEM_CONTIG:
		ion_system_contig_heap_destroy(heap);
		break;
	case ION_HEAP_TYPE_SYSTEM:
		ion_system_heap_destroy(heap);
		break;
	case ION_HEAP_TYPE_CARVEOUT:
		ion_carveout_heap_destroy(heap);
		break;
	case ION_HEAP_TYPE_IOMMU:
		ion_iommu_heap_destroy(heap);
		break;
	case ION_HEAP_TYPE_CP:
		ion_cp_heap_destroy(heap);
		break;
#ifdef CONFIG_CMA
	case ION_HEAP_TYPE_DMA:
		ion_cma_heap_destroy(heap);
		break;
#endif
	default:
		pr_err("%s: Invalid heap type %d\n", __func__,
		       heap->type);
	}
