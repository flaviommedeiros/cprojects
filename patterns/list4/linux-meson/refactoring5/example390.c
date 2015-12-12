#ifndef __ECOS
if (jffs2_blocks_use_vmalloc(c))
		vfree(c->blocks);
	else
#endif
		kfree(c->blocks);
