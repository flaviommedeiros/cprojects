#ifdef pgprot_noncached
if (file->f_flags & O_DSYNC || off >= __pa(high_memory))
			vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
