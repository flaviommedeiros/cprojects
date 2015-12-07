#ifndef __ECOS
if (jffs2_blocks_use_vmalloc(c))
		c->blocks = vmalloc(size);
	else
#endif
		c->blocks = kmalloc(size, GFP_KERNEL);
