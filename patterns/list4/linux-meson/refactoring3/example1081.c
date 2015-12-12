switch (idx) {
	case FIX_BTMAP_END ... FIX_BTMAP_BEGIN:
	case FIX_RO_IDT:
#ifdef CONFIG_X86_32
	case FIX_WP_TEST:
	case FIX_VDSO:
# ifdef CONFIG_HIGHMEM
	case FIX_KMAP_BEGIN ... FIX_KMAP_END:
# endif
#else
	case VSYSCALL_LAST_PAGE ... VSYSCALL_FIRST_PAGE:
	case VVAR_PAGE:
#endif
	case FIX_TEXT_POKE0:
	case FIX_TEXT_POKE1:
		/* All local page mappings */
		pte = pfn_pte(phys, prot);
		break;

#ifdef CONFIG_X86_LOCAL_APIC
	case FIX_APIC_BASE:	/* maps dummy local APIC */
		pte = pfn_pte(PFN_DOWN(__pa(dummy_mapping)), PAGE_KERNEL);
		break;
#endif

#ifdef CONFIG_X86_IO_APIC
	case FIX_IO_APIC_BASE_0 ... FIX_IO_APIC_BASE_END:
		/*
		 * We just don't map the IO APIC - all access is via
		 * hypercalls.  Keep the address in the pte for reference.
		 */
		pte = pfn_pte(PFN_DOWN(__pa(dummy_mapping)), PAGE_KERNEL);
		break;
#endif

	case FIX_PARAVIRT_BOOTMAP:
		/* This is an MFN, but it isn't an IO mapping from the
		   IO domain */
		pte = mfn_pte(phys, prot);
		break;

	default:
		/* By default, set_fixmap is used for hardware mappings */
		pte = mfn_pte(phys, __pgprot(pgprot_val(prot) | _PAGE_IOMAP));
		break;
	}
