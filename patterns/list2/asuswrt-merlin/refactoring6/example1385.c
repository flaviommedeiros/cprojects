if (!vma->vm_pgoff
#if __OS_HAS_AGP
	    && (!dev->agp
		|| dev->agp->agp_info.device->vendor != PCI_VENDOR_ID_APPLE)
#endif
	    )
		return drm_mmap_dma(filp, vma);