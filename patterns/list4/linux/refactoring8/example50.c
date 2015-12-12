static struct evlist_test test__events[] = {
	{
		.name  = "syscalls:sys_enter_openat",
		.check = test__checkevent_tracepoint,
		.id    = 0,
	},
	{
		.name  = "syscalls:*",
		.check = test__checkevent_tracepoint_multi,
		.id    = 1,
	},
	{
		.name  = "r1a",
		.check = test__checkevent_raw,
		.id    = 2,
	},
	{
		.name  = "1:1",
		.check = test__checkevent_numeric,
		.id    = 3,
	},
	{
		.name  = "instructions",
		.check = test__checkevent_symbolic_name,
		.id    = 4,
	},
	{
		.name  = "cycles/period=100000,config2/",
		.check = test__checkevent_symbolic_name_config,
		.id    = 5,
	},
	{
		.name  = "faults",
		.check = test__checkevent_symbolic_alias,
		.id    = 6,
	},
	{
		.name  = "L1-dcache-load-miss",
		.check = test__checkevent_genhw,
		.id    = 7,
	},
	{
		.name  = "mem:0",
		.check = test__checkevent_breakpoint,
		.id    = 8,
	},
	{
		.name  = "mem:0:x",
		.check = test__checkevent_breakpoint_x,
		.id    = 9,
	},
	{
		.name  = "mem:0:r",
		.check = test__checkevent_breakpoint_r,
		.id    = 10,
	},
	{
		.name  = "mem:0:w",
		.check = test__checkevent_breakpoint_w,
		.id    = 11,
	},
	{
		.name  = "syscalls:sys_enter_openat:k",
		.check = test__checkevent_tracepoint_modifier,
		.id    = 12,
	},
	{
		.name  = "syscalls:*:u",
		.check = test__checkevent_tracepoint_multi_modifier,
		.id    = 13,
	},
	{
		.name  = "r1a:kp",
		.check = test__checkevent_raw_modifier,
		.id    = 14,
	},
	{
		.name  = "1:1:hp",
		.check = test__checkevent_numeric_modifier,
		.id    = 15,
	},
	{
		.name  = "instructions:h",
		.check = test__checkevent_symbolic_name_modifier,
		.id    = 16,
	},
	{
		.name  = "faults:u",
		.check = test__checkevent_symbolic_alias_modifier,
		.id    = 17,
	},
	{
		.name  = "L1-dcache-load-miss:kp",
		.check = test__checkevent_genhw_modifier,
		.id    = 18,
	},
	{
		.name  = "mem:0:u",
		.check = test__checkevent_breakpoint_modifier,
		.id    = 19,
	},
	{
		.name  = "mem:0:x:k",
		.check = test__checkevent_breakpoint_x_modifier,
		.id    = 20,
	},
	{
		.name  = "mem:0:r:hp",
		.check = test__checkevent_breakpoint_r_modifier,
		.id    = 21,
	},
	{
		.name  = "mem:0:w:up",
		.check = test__checkevent_breakpoint_w_modifier,
		.id    = 22,
	},
	{
		.name  = "r1,syscalls:sys_enter_openat:k,1:1:hp",
		.check = test__checkevent_list,
		.id    = 23,
	},
	{
		.name  = "instructions:G",
		.check = test__checkevent_exclude_host_modifier,
		.id    = 24,
	},
	{
		.name  = "instructions:H",
		.check = test__checkevent_exclude_guest_modifier,
		.id    = 25,
	},
	{
		.name  = "mem:0:rw",
		.check = test__checkevent_breakpoint_rw,
		.id    = 26,
	},
	{
		.name  = "mem:0:rw:kp",
		.check = test__checkevent_breakpoint_rw_modifier,
		.id    = 27,
	},
	{
		.name  = "{instructions:k,cycles:upp}",
		.check = test__group1,
		.id    = 28,
	},
	{
		.name  = "{faults:k,cache-references}:u,cycles:k",
		.check = test__group2,
		.id    = 29,
	},
	{
		.name  = "group1{syscalls:sys_enter_openat:H,cycles:kppp},group2{cycles,1:3}:G,instructions:u",
		.check = test__group3,
		.id    = 30,
	},
	{
		.name  = "{cycles:u,instructions:kp}:p",
		.check = test__group4,
		.id    = 31,
	},
	{
		.name  = "{cycles,instructions}:G,{cycles:G,instructions:G},cycles",
		.check = test__group5,
		.id    = 32,
	},
	{
		.name  = "*:*",
		.check = test__all_tracepoints,
		.id    = 33,
	},
	{
		.name  = "{cycles,cache-misses:G}:H",
		.check = test__group_gh1,
		.id    = 34,
	},
	{
		.name  = "{cycles,cache-misses:H}:G",
		.check = test__group_gh2,
		.id    = 35,
	},
	{
		.name  = "{cycles:G,cache-misses:H}:u",
		.check = test__group_gh3,
		.id    = 36,
	},
	{
		.name  = "{cycles:G,cache-misses:H}:uG",
		.check = test__group_gh4,
		.id    = 37,
	},
	{
		.name  = "{cycles,cache-misses,branch-misses}:S",
		.check = test__leader_sample1,
		.id    = 38,
	},
	{
		.name  = "{instructions,branch-misses}:Su",
		.check = test__leader_sample2,
		.id    = 39,
	},
	{
		.name  = "instructions:uDp",
		.check = test__checkevent_pinned_modifier,
		.id    = 40,
	},
	{
		.name  = "{cycles,cache-misses,branch-misses}:D",
		.check = test__pinned_group,
		.id    = 41,
	},
	{
		.name  = "mem:0/1",
		.check = test__checkevent_breakpoint_len,
		.id    = 42,
	},
	{
		.name  = "mem:0/2:w",
		.check = test__checkevent_breakpoint_len_w,
		.id    = 43,
	},
	{
		.name  = "mem:0/4:rw:u",
		.check = test__checkevent_breakpoint_len_rw_modifier,
		.id    = 44
	},
#if defined(__s390x__)
	{
		.name  = "kvm-s390:kvm_s390_create_vm",
		.check = test__checkevent_tracepoint,
		.id    = 100,
	},
#endif
	{
		.name  = "instructions:I",
		.check = test__checkevent_exclude_idle_modifier,
		.id    = 45,
	},
	{
		.name  = "instructions:kIG",
		.check = test__checkevent_exclude_idle_modifier_1,
		.id    = 46,
	},
	{
		.name  = "task-clock:P,cycles",
		.check = test__checkevent_precise_max_modifier,
		.id    = 47,
	},
};
