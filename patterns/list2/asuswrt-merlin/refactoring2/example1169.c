#ifndef CONFIG_KPROBES
if (num_possible_cpus() <= 1)
#endif
	{
		change_page_attr(virt_to_page(start),
		                 size >> PAGE_SHIFT, PAGE_KERNEL_RX);
		printk("Write protecting the kernel text: %luk\n", size >> 10);
	}
