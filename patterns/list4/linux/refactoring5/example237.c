#ifndef __ECOS
if (jffs2_blocks_use_vmalloc(c))
		c->blocks = vzalloc(size);
	else
#endif
		c->blocks = kzalloc(size, GFP_KERNEL);
