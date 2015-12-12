switch (cmd) {
	case PCIIOC_CONTROLLER:
		ret = pci_domain_nr(dev->bus);
		break;

#ifdef HAVE_PCI_MMAP
	case PCIIOC_MMAP_IS_IO:
		fpriv->mmap_state = pci_mmap_io;
		break;

	case PCIIOC_MMAP_IS_MEM:
		fpriv->mmap_state = pci_mmap_mem;
		break;

	case PCIIOC_WRITE_COMBINE:
		if (arg)
			fpriv->write_combine = 1;
		else
			fpriv->write_combine = 0;
		break;

#endif /* HAVE_PCI_MMAP */

	default:
		ret = -EINVAL;
		break;
	}
