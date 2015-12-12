static const struct mmc_test_case mmc_test_cases[] = {
	{
		.name = "Basic write (no data verification)",
		.run = mmc_test_basic_write,
	},

	{
		.name = "Basic read (no data verification)",
		.run = mmc_test_basic_read,
	},

	{
		.name = "Basic write (with data verification)",
		.prepare = mmc_test_prepare_write,
		.run = mmc_test_verify_write,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Basic read (with data verification)",
		.prepare = mmc_test_prepare_read,
		.run = mmc_test_verify_read,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Multi-block write",
		.prepare = mmc_test_prepare_write,
		.run = mmc_test_multi_write,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Multi-block read",
		.prepare = mmc_test_prepare_read,
		.run = mmc_test_multi_read,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Power of two block writes",
		.prepare = mmc_test_prepare_write,
		.run = mmc_test_pow2_write,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Power of two block reads",
		.prepare = mmc_test_prepare_read,
		.run = mmc_test_pow2_read,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Weird sized block writes",
		.prepare = mmc_test_prepare_write,
		.run = mmc_test_weird_write,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Weird sized block reads",
		.prepare = mmc_test_prepare_read,
		.run = mmc_test_weird_read,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Badly aligned write",
		.prepare = mmc_test_prepare_write,
		.run = mmc_test_align_write,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Badly aligned read",
		.prepare = mmc_test_prepare_read,
		.run = mmc_test_align_read,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Badly aligned multi-block write",
		.prepare = mmc_test_prepare_write,
		.run = mmc_test_align_multi_write,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Badly aligned multi-block read",
		.prepare = mmc_test_prepare_read,
		.run = mmc_test_align_multi_read,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Correct xfer_size at write (start failure)",
		.run = mmc_test_xfersize_write,
	},

	{
		.name = "Correct xfer_size at read (start failure)",
		.run = mmc_test_xfersize_read,
	},

	{
		.name = "Correct xfer_size at write (midway failure)",
		.run = mmc_test_multi_xfersize_write,
	},

	{
		.name = "Correct xfer_size at read (midway failure)",
		.run = mmc_test_multi_xfersize_read,
	},

#ifdef CONFIG_HIGHMEM

	{
		.name = "Highmem write",
		.prepare = mmc_test_prepare_write,
		.run = mmc_test_write_high,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Highmem read",
		.prepare = mmc_test_prepare_read,
		.run = mmc_test_read_high,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Multi-block highmem write",
		.prepare = mmc_test_prepare_write,
		.run = mmc_test_multi_write_high,
		.cleanup = mmc_test_cleanup,
	},

	{
		.name = "Multi-block highmem read",
		.prepare = mmc_test_prepare_read,
		.run = mmc_test_multi_read_high,
		.cleanup = mmc_test_cleanup,
	},

#else

	{
		.name = "Highmem write",
		.run = mmc_test_no_highmem,
	},

	{
		.name = "Highmem read",
		.run = mmc_test_no_highmem,
	},

	{
		.name = "Multi-block highmem write",
		.run = mmc_test_no_highmem,
	},

	{
		.name = "Multi-block highmem read",
		.run = mmc_test_no_highmem,
	},

#endif /* CONFIG_HIGHMEM */

	{
		.name = "Best-case read performance",
		.prepare = mmc_test_area_prepare_fill,
		.run = mmc_test_best_read_performance,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Best-case write performance",
		.prepare = mmc_test_area_prepare_erase,
		.run = mmc_test_best_write_performance,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Best-case read performance into scattered pages",
		.prepare = mmc_test_area_prepare_fill,
		.run = mmc_test_best_read_perf_max_scatter,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Best-case write performance from scattered pages",
		.prepare = mmc_test_area_prepare_erase,
		.run = mmc_test_best_write_perf_max_scatter,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Single read performance by transfer size",
		.prepare = mmc_test_area_prepare_fill,
		.run = mmc_test_profile_read_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Single write performance by transfer size",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_write_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Single trim performance by transfer size",
		.prepare = mmc_test_area_prepare_fill,
		.run = mmc_test_profile_trim_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Consecutive read performance by transfer size",
		.prepare = mmc_test_area_prepare_fill,
		.run = mmc_test_profile_seq_read_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Consecutive write performance by transfer size",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_seq_write_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Consecutive trim performance by transfer size",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_seq_trim_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Random read performance by transfer size",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_random_read_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Random write performance by transfer size",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_random_write_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Large sequential read into scattered pages",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_large_seq_read_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Large sequential write from scattered pages",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_large_seq_write_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Write performance with blocking req 4k to 4MB",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_mult_write_blocking_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Write performance with non-blocking req 4k to 4MB",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_mult_write_nonblock_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Read performance with blocking req 4k to 4MB",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_mult_read_blocking_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Read performance with non-blocking req 4k to 4MB",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_mult_read_nonblock_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Write performance blocking req 1 to 512 sg elems",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_sglen_wr_blocking_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Write performance non-blocking req 1 to 512 sg elems",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_sglen_wr_nonblock_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Read performance blocking req 1 to 512 sg elems",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_sglen_r_blocking_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Read performance non-blocking req 1 to 512 sg elems",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_sglen_r_nonblock_perf,
		.cleanup = mmc_test_area_cleanup,
	},

	{
		.name = "Reset test",
		.run = mmc_test_reset,
	},
};
