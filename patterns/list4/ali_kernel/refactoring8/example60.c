static int __init init_cpu_info(enum arch_id arch)
{
	union save_area *sa;

	/* get info for boot cpu from lowcore, stored in the HSA */

	sa = kmalloc(sizeof(*sa), GFP_KERNEL);
	if (!sa)
		return -ENOMEM;
	if (memcpy_hsa_kernel(sa, sys_info.sa_base, sys_info.sa_size) < 0) {
		TRACE("could not copy from HSA\n");
		kfree(sa);
		return -EIO;
	}
	zfcpdump_save_areas[0] = sa;

#ifdef __s390x__
	/* convert s390x regs to s390, if we are dumping an s390 Linux */

	if (arch == ARCH_S390)
		s390x_to_s390_save_areas();
#endif

	return 0;
}
