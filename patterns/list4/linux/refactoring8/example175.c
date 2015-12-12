static const struct cl_io_operations lov_empty_io_ops = {
	.op = {
		[CIT_READ] = {
			.cio_fini       = lov_empty_io_fini,
#if 0
			.cio_iter_init  = LOV_EMPTY_IMPOSSIBLE,
			.cio_lock       = LOV_EMPTY_IMPOSSIBLE,
			.cio_start      = LOV_EMPTY_IMPOSSIBLE,
			.cio_end	= LOV_EMPTY_IMPOSSIBLE
#endif
		},
		[CIT_WRITE] = {
			.cio_fini      = lov_empty_io_fini,
			.cio_iter_init = LOV_EMPTY_IMPOSSIBLE,
			.cio_lock      = LOV_EMPTY_IMPOSSIBLE,
			.cio_start     = LOV_EMPTY_IMPOSSIBLE,
			.cio_end       = LOV_EMPTY_IMPOSSIBLE
		},
		[CIT_SETATTR] = {
			.cio_fini      = lov_empty_io_fini,
			.cio_iter_init = LOV_EMPTY_IMPOSSIBLE,
			.cio_lock      = LOV_EMPTY_IMPOSSIBLE,
			.cio_start     = LOV_EMPTY_IMPOSSIBLE,
			.cio_end       = LOV_EMPTY_IMPOSSIBLE
		},
		[CIT_FAULT] = {
			.cio_fini      = lov_empty_io_fini,
			.cio_iter_init = LOV_EMPTY_IMPOSSIBLE,
			.cio_lock      = LOV_EMPTY_IMPOSSIBLE,
			.cio_start     = LOV_EMPTY_IMPOSSIBLE,
			.cio_end       = LOV_EMPTY_IMPOSSIBLE
		},
		[CIT_FSYNC] = {
			.cio_fini   = lov_empty_io_fini
		},
		[CIT_MISC] = {
			.cio_fini   = lov_empty_io_fini
		}
	},
	.req_op = {
		 [CRT_READ] = {
			 .cio_submit    = LOV_EMPTY_IMPOSSIBLE
		 },
		 [CRT_WRITE] = {
			 .cio_submit    = LOV_EMPTY_IMPOSSIBLE
		 }
	 },
	.cio_commit_write = LOV_EMPTY_IMPOSSIBLE
};
