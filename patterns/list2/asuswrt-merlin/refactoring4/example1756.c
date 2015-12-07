#ifdef CONFIG_MMU
if (in_interrupt())
		BUG();
