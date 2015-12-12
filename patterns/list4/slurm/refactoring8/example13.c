extern int cr_job_test(struct job_record *job_ptr, bitstr_t *node_bitmap,
			uint32_t min_nodes, uint32_t max_nodes,
			uint32_t req_nodes, int mode,
			uint16_t cr_type, enum node_cr_state job_node_req,
			uint32_t cr_node_cnt,
			struct part_res_record *cr_part_ptr,
			struct node_use_record *node_usage,
			bitstr_t *exc_core_bitmap, bool prefer_alloc_nodes,
			bool qos_preemptor, bool preempt_mode)
{
	static int gang_mode = -1;
	int error_code = SLURM_SUCCESS, ll; /* ll = layout array index */
	uint16_t *layout_ptr = NULL;
	bitstr_t *orig_map, *avail_cores, *free_cores, *part_core_map = NULL;
	bitstr_t *tmpcore = NULL, *reqmap = NULL;
	bool test_only;
	uint32_t c, i, j, k, n, csize, total_cpus, save_mem = 0;
	int32_t build_cnt;
	job_resources_t *job_res;
	struct job_details *details_ptr;
	struct part_res_record *p_ptr, *jp_ptr;
	uint16_t *cpu_count;
	int first, last;

	if (gang_mode == -1) {
		if (slurm_get_preempt_mode() & PREEMPT_MODE_GANG)
			gang_mode = 1;
		else
			gang_mode = 0;
	}

	details_ptr = job_ptr->details;
	layout_ptr  = details_ptr->req_node_layout;
	reqmap      = details_ptr->req_node_bitmap;

	free_job_resources(&job_ptr->job_resrcs);

	if (mode == SELECT_MODE_TEST_ONLY)
		test_only = true;
	else	/* SELECT_MODE_RUN_NOW || SELECT_MODE_WILL_RUN  */
		test_only = false;

	/* check node_state and update the node_bitmap as necessary */
	if (!test_only) {
		error_code = _verify_node_state(cr_part_ptr, job_ptr,
						node_bitmap, cr_type,
						node_usage, job_node_req,
						exc_core_bitmap, qos_preemptor);
		if (error_code != SLURM_SUCCESS) {
			return error_code;
		}
	}

	/* This is the case if -O/--overcommit  is true */
	if (details_ptr->min_cpus == details_ptr->min_nodes) {
		struct multi_core_data *mc_ptr = details_ptr->mc_ptr;

		if ((mc_ptr->threads_per_core != (uint16_t) NO_VAL) &&
		    (mc_ptr->threads_per_core > 1))
			details_ptr->min_cpus *= mc_ptr->threads_per_core;
		if ((mc_ptr->cores_per_socket != (uint16_t) NO_VAL) &&
		    (mc_ptr->cores_per_socket > 1))
			details_ptr->min_cpus *= mc_ptr->cores_per_socket;
		if ((mc_ptr->sockets_per_node != (uint16_t) NO_VAL) &&
		    (mc_ptr->sockets_per_node > 1))
			details_ptr->min_cpus *= mc_ptr->sockets_per_node;
	}

	if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
		info("cons_res: cr_job_test: evaluating job %u on %u nodes",
		     job_ptr->job_id, bit_set_count(node_bitmap));
	}

	orig_map = bit_copy(node_bitmap);
	avail_cores = _make_core_bitmap(node_bitmap,
					job_ptr->details->core_spec);

	/* test to make sure that this job can succeed with all avail_cores
	 * if 'no' then return FAIL
	 * if 'yes' then we will seek the optimal placement for this job
	 *          within avail_cores
	 */
	free_cores = bit_copy(avail_cores);
	cpu_count = _select_nodes(job_ptr, min_nodes, max_nodes, req_nodes,
				  node_bitmap, cr_node_cnt, free_cores,
				  node_usage, cr_type, test_only,
				  part_core_map, prefer_alloc_nodes);
	if (cpu_count == NULL) {
		/* job cannot fit */
		FREE_NULL_BITMAP(orig_map);
		FREE_NULL_BITMAP(free_cores);
		FREE_NULL_BITMAP(avail_cores);
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
			info("cons_res: cr_job_test: test 0 fail: "
			     "insufficient resources");
		}
		return SLURM_ERROR;
	} else if (test_only) {
		FREE_NULL_BITMAP(orig_map);
		FREE_NULL_BITMAP(free_cores);
		FREE_NULL_BITMAP(avail_cores);
		xfree(cpu_count);
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE)
			info("cons_res: cr_job_test: test 0 pass: test_only");
		return SLURM_SUCCESS;
	} else if (!job_ptr->best_switch) {
		FREE_NULL_BITMAP(orig_map);
		FREE_NULL_BITMAP(free_cores);
		FREE_NULL_BITMAP(avail_cores);
		xfree(cpu_count);
		if (select_debug_flags & DEBUG_FLAG_CPU_BIND) {
			info("cons_res: cr_job_test: test 0 fail: "
			     "waiting for switches");
		}
		return SLURM_ERROR;
	}
	if (cr_type == CR_MEMORY) {
		/* CR_MEMORY does not care about existing CPU allocations,
		 * so we can jump right to job allocation from here */
		goto alloc_job;
	}
	xfree(cpu_count);
	if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
		info("cons_res: cr_job_test: test 0 pass - "
		     "job fits on given resources");
	}

	/* now that we know that this job can run with the given resources,
	 * let's factor in the existing allocations and seek the optimal set
	 * of resources for this job. Here is the procedure:
	 *
	 * Step 1: Seek idle CPUs across all partitions. If successful then
	 *         place job and exit. If not successful, then continue. Two
	 *         related items to note:
	 *          1. Jobs that don't share CPUs finish with step 1.
	 *          2. The remaining steps assume sharing or preemption.
	 *
	 * Step 2: Remove resources that are in use by higher-priority
	 *         partitions, and test that job can still succeed. If not
	 *         then exit.
	 *
	 * Step 3: Seek idle nodes among the partitions with the same
	 *         priority as the job's partition. If successful then
	 *         goto Step 6. If not then continue:
	 *
	 * Step 4: Seek placement within the job's partition. Search
	 *         row-by-row. If no placement if found, then exit. If a row
	 *         is found, then continue:
	 *
	 * Step 5: Place job and exit. FIXME! Here is where we need a
	 *         placement algorithm that recognizes existing job
	 *         boundaries and tries to "overlap jobs" as efficiently
	 *         as possible.
	 *
	 * Step 6: Place job and exit. FIXME! here is we use a placement
	 *         algorithm similar to Step 5 on jobs from lower-priority
	 *         partitions.
	 */


	/*** Step 1 ***/
	bit_copybits(node_bitmap, orig_map);
	bit_copybits(free_cores, avail_cores);

	if (exc_core_bitmap) {
		int exc_core_size  = bit_size(exc_core_bitmap);
		int free_core_size = bit_size(free_cores);
		if (exc_core_size != free_core_size) {
			/* This would indicate that cores were added to or
			 * removed from nodes in this reservation when the
			 * slurmctld daemon restarted with a new slurm.conf
			 * file. This can result in cores being lost from a
			 * reservation. */
			error("Bad core_bitmap size for reservation %s "
			      "(%d != %d), ignoring core reservation",
			      job_ptr->resv_name,
			      exc_core_size, free_core_size);
			exc_core_bitmap = NULL;	/* Clear local value */
		}
	}
	if (exc_core_bitmap) {
#if _DEBUG
		char str[100];
		bit_fmt(str, (sizeof(str) - 1), exc_core_bitmap);
		debug2("excluding cores reserved: %s", str);
#endif
		bit_not(exc_core_bitmap);
		bit_and(free_cores, exc_core_bitmap);
		bit_not(exc_core_bitmap);
	}

	/* remove all existing allocations from free_cores */
	tmpcore = bit_copy(free_cores);
	for (p_ptr = cr_part_ptr; p_ptr; p_ptr = p_ptr->next) {
		if (!p_ptr->row)
			continue;
		for (i = 0; i < p_ptr->num_rows; i++) {
			if (!p_ptr->row[i].row_bitmap)
				continue;
			bit_copybits(tmpcore, p_ptr->row[i].row_bitmap);
			bit_not(tmpcore); /* set bits now "free" resources */
			bit_and(free_cores, tmpcore);
			if (p_ptr->part_ptr != job_ptr->part_ptr)
				continue;
			if (part_core_map) {
				bit_or(part_core_map, p_ptr->row[i].row_bitmap);
			} else {
				part_core_map = bit_copy(p_ptr->row[i].
							 row_bitmap);
			}
		}
	}
	if (job_ptr->details->whole_node == 1)
		_block_whole_nodes(node_bitmap, avail_cores, free_cores);

	cpu_count = _select_nodes(job_ptr, min_nodes, max_nodes, req_nodes,
				  node_bitmap, cr_node_cnt, free_cores,
				  node_usage, cr_type, test_only,
				  part_core_map, prefer_alloc_nodes);

	if ((cpu_count) && (job_ptr->best_switch)) {
		/* job fits! We're done. */
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
			info("cons_res: cr_job_test: test 1 pass - "
			     "idle resources found");
		}
		goto alloc_job;
	}

	if ((gang_mode == 0) && (job_node_req == NODE_CR_ONE_ROW)) {
		/* This job CANNOT share CPUs regardless of priority,
		 * so we fail here. Note that Shared=EXCLUSIVE was already
		 * addressed in _verify_node_state() and job preemption
		 * removes jobs from simulated resource allocation map
		 * before this point. */
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
			info("cons_res: cr_job_test: test 1 fail - no idle resources available");
		}
		goto alloc_job;
	}
	if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
		info("cons_res: cr_job_test: test 1 fail - "
		     "not enough idle resources");
	}

	/*** Step 2 ***/
	bit_copybits(node_bitmap, orig_map);
	bit_copybits(free_cores, avail_cores);

	if (exc_core_bitmap) {
		bit_not(exc_core_bitmap);
		bit_and(free_cores, exc_core_bitmap);
		bit_not(exc_core_bitmap);
	}

	for (jp_ptr = cr_part_ptr; jp_ptr; jp_ptr = jp_ptr->next) {
		if (jp_ptr->part_ptr == job_ptr->part_ptr)
			break;
	}
	if (!jp_ptr) {
		fatal("cons_res error: could not find partition for job %u",
			job_ptr->job_id);
		return SLURM_ERROR;	/* CLANG false positive */
	}

	/* remove existing allocations (jobs) from higher-priority partitions
	 * from avail_cores */
	if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
		info("cons_res: cr_job_test: looking for higher-priority or "
		     "PREEMPT_MODE_OFF part's to remove from avail_cores");
	}

	for (p_ptr = cr_part_ptr; p_ptr; p_ptr = p_ptr->next) {
		if ((p_ptr->part_ptr->priority <= jp_ptr->part_ptr->priority) &&
		    (p_ptr->part_ptr->preempt_mode != PREEMPT_MODE_OFF)) {
			if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
				info("cons_res: cr_job_test: continuing on "
				     "part: %s", p_ptr->part_ptr->name);
			}
			continue;
		}
		if (!p_ptr->row)
			continue;
		for (i = 0; i < p_ptr->num_rows; i++) {
			if (!p_ptr->row[i].row_bitmap)
				continue;
			bit_copybits(tmpcore, p_ptr->row[i].row_bitmap);
			bit_not(tmpcore); /* set bits now "free" resources */
			bit_and(free_cores, tmpcore);
		}
	}
	if (job_ptr->details->whole_node == 1)
		_block_whole_nodes(node_bitmap, avail_cores, free_cores);
	/* make these changes permanent */
	bit_copybits(avail_cores, free_cores);
	cpu_count = _select_nodes(job_ptr, min_nodes, max_nodes, req_nodes,
				  node_bitmap, cr_node_cnt, free_cores,
				  node_usage, cr_type, test_only,
				  part_core_map, prefer_alloc_nodes);
	if (!cpu_count) {
		/* job needs resources that are currently in use by
		 * higher-priority jobs, so fail for now */
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
			info("cons_res: cr_job_test: test 2 fail - "
			     "resources busy with higher priority jobs");
		}
		goto alloc_job;
	}
	xfree(cpu_count);
	if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
		info("cons_res: cr_job_test: test 2 pass - "
		     "available resources for this priority");
	}

	/*** Step 3 ***/
	bit_copybits(node_bitmap, orig_map);
	bit_copybits(free_cores, avail_cores);

	/* remove existing allocations (jobs) from same-priority partitions
	 * from avail_cores */
	for (p_ptr = cr_part_ptr; p_ptr; p_ptr = p_ptr->next) {
		if (p_ptr->part_ptr->priority != jp_ptr->part_ptr->priority)
			continue;
		if (!p_ptr->row)
			continue;
		for (i = 0; i < p_ptr->num_rows; i++) {
			if (!p_ptr->row[i].row_bitmap)
				continue;
			bit_copybits(tmpcore, p_ptr->row[i].row_bitmap);
			bit_not(tmpcore); /* set bits now "free" resources */
			bit_and(free_cores, tmpcore);
		}
	}
	cpu_count = _select_nodes(job_ptr, min_nodes, max_nodes, req_nodes,
				  node_bitmap, cr_node_cnt, free_cores,
				  node_usage, cr_type, test_only,
				  part_core_map, prefer_alloc_nodes);
	if (cpu_count) {
		/* jobs from low-priority partitions are the only thing left
		 * in our way. for now we'll ignore them, but FIXME: we need
		 * a good placement algorithm here that optimizes "job overlap"
		 * between this job (in these idle nodes) and the low-priority
		 * jobs */
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
			info("cons_res: cr_job_test: test 3 pass - "
			     "found resources");
		}
		goto alloc_job;
	}
	if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
		info("cons_res: cr_job_test: test 3 fail - "
		     "not enough idle resources in same priority");
	}


	/*** Step 4 ***/
	/* try to fit the job into an existing row
	 *
	 * tmpcore = worker core_bitmap
	 * free_cores = core_bitmap to be built
	 * avail_cores = static core_bitmap of all available cores
	 */

	if (!jp_ptr || !jp_ptr->row) {
		/* there's no existing jobs in this partition, so place
		 * the job in avail_cores. FIXME: still need a good
		 * placement algorithm here that optimizes "job overlap"
		 * between this job (in these idle nodes) and existing
		 * jobs in the other partitions with <= priority to
		 * this partition */
		bit_copybits(node_bitmap, orig_map);
		bit_copybits(free_cores, avail_cores);
		cpu_count = _select_nodes(job_ptr, min_nodes, max_nodes,
					  req_nodes, node_bitmap, cr_node_cnt,
					  free_cores, node_usage, cr_type,
					  test_only, part_core_map,
					  prefer_alloc_nodes);
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
			info("cons_res: cr_job_test: test 4 pass - "
			     "first row found");
		}
		goto alloc_job;
	}

	if ((jp_ptr->num_rows > 1) && !preempt_by_qos)
		cr_sort_part_rows(jp_ptr);	/* Preserve row order for QOS */
	c = jp_ptr->num_rows;
	if (preempt_by_qos && !qos_preemptor)
		c--;				/* Do not use extra row */
	if (preempt_by_qos && (job_node_req != NODE_CR_AVAILABLE))
		c = 1;
	for (i = 0; i < c; i++) {
		if (!jp_ptr->row[i].row_bitmap)
			break;
		bit_copybits(node_bitmap, orig_map);
		bit_copybits(free_cores, avail_cores);
		bit_copybits(tmpcore, jp_ptr->row[i].row_bitmap);
		bit_not(tmpcore);
		bit_and(free_cores, tmpcore);
		cpu_count = _select_nodes(job_ptr, min_nodes, max_nodes,
					  req_nodes, node_bitmap, cr_node_cnt,
					  free_cores, node_usage, cr_type,
					  test_only, part_core_map,
					  prefer_alloc_nodes);
		if (cpu_count) {
			if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
				info("cons_res: cr_job_test: test 4 pass - "
				     "row %i", i);
			}
			break;
		}
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE)
			info("cons_res: cr_job_test: test 4 fail - row %i", i);
	}

	if ((i < c) && !jp_ptr->row[i].row_bitmap) {
		/* we've found an empty row, so use it */
		bit_copybits(node_bitmap, orig_map);
		bit_copybits(free_cores, avail_cores);
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
			info("cons_res: cr_job_test: "
			     "test 4 trying empty row %i",i);
		}
		cpu_count = _select_nodes(job_ptr, min_nodes, max_nodes,
					  req_nodes, node_bitmap, cr_node_cnt,
					  free_cores, node_usage, cr_type,
					  test_only, part_core_map,
					  prefer_alloc_nodes);
	}

	if (!cpu_count) {
		/* job can't fit into any row, so exit */
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
			info("cons_res: cr_job_test: test 4 fail - "
			     "busy partition");
		}
		goto alloc_job;

	}

	/*** CONSTRUCTION ZONE FOR STEPs 5 AND 6 ***
	 * Note that while the job may have fit into a row, it should
	 * still be run through a good placement algorithm here that
	 * optimizes "job overlap" between this job (in these idle nodes)
	 * and existing jobs in the other partitions with <= priority to
	 * this partition */

alloc_job:
	/* at this point we've found a good set of
	 * bits to allocate to this job:
	 * - node_bitmap is the set of nodes to allocate
	 * - free_cores is the set of allocated cores
	 * - cpu_count is the number of cpus per allocated node
	 *
	 * Next steps are to cleanup the worker variables,
	 * create the job_resources struct,
	 * distribute the job on the bits, and exit
	 */
	FREE_NULL_BITMAP(orig_map);
	FREE_NULL_BITMAP(avail_cores);
	FREE_NULL_BITMAP(tmpcore);
	FREE_NULL_BITMAP(part_core_map);
	if ((!cpu_count) || (!job_ptr->best_switch)) {
		/* we were sent here to cleanup and exit */
		FREE_NULL_BITMAP(free_cores);
		if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
			info("cons_res: exiting cr_job_test with no "
			     "allocation");
		}
		return SLURM_ERROR;
	}

	/* At this point we have:
	 * - a node_bitmap of selected nodes
	 * - a free_cores bitmap of usable cores on each selected node
	 * - a per-alloc-node cpu_count array
	 */

	if ((mode != SELECT_MODE_WILL_RUN) && (job_ptr->part_ptr == NULL))
		error_code = EINVAL;
	if ((error_code == SLURM_SUCCESS) && (mode == SELECT_MODE_WILL_RUN)) {
		/* Set a reasonable value for the number of allocated CPUs.
		 * Without computing task distribution this is only a guess */
		job_ptr->total_cpus = MAX(job_ptr->details->min_cpus,
					  job_ptr->details->min_nodes);
	}
	if ((error_code != SLURM_SUCCESS) || (mode != SELECT_MODE_RUN_NOW)) {
		FREE_NULL_BITMAP(free_cores);
		xfree(cpu_count);
		return error_code;
	}

	if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
		info("cons_res: cr_job_test: distributing job %u",
		     job_ptr->job_id);
	}

	/** create the struct_job_res  **/
	job_res                   = create_job_resources();
	job_res->node_bitmap      = bit_copy(node_bitmap);
	job_res->nodes            = bitmap2node_name(node_bitmap);
	job_res->nhosts           = bit_set_count(node_bitmap);
	job_res->ncpus            = job_res->nhosts;
	if (job_ptr->details->ntasks_per_node)
		job_res->ncpus   *= details_ptr->ntasks_per_node;
	job_res->ncpus            = MAX(job_res->ncpus,
					details_ptr->min_cpus);
	job_res->ncpus            = MAX(job_res->ncpus,
					(job_res->nhosts *
					 details_ptr->pn_min_cpus));
	job_res->node_req         = job_node_req;
	job_res->cpus             = cpu_count;
	job_res->cpus_used        = xmalloc(job_res->nhosts *
					    sizeof(uint16_t));
	job_res->memory_allocated = xmalloc(job_res->nhosts *
					    sizeof(uint32_t));
	job_res->memory_used      = xmalloc(job_res->nhosts *
					    sizeof(uint32_t));
	job_res->whole_node       = job_ptr->details->whole_node;

	/* store the hardware data for the selected nodes */
	error_code = build_job_resources(job_res, node_record_table_ptr,
					  select_fast_schedule);
	if (error_code != SLURM_SUCCESS) {
		free_job_resources(&job_res);
		FREE_NULL_BITMAP(free_cores);
		return error_code;
	}

	/* sync up cpus with layout_ptr, total up
	 * all cpus, and load the core_bitmap */
	ll = -1;
	total_cpus = 0;
	c = 0;
	csize = bit_size(job_res->core_bitmap);

	for (i = 0, n = 0; n < cr_node_cnt; n++) {
		if (layout_ptr && reqmap && bit_test(reqmap,n))
			ll++;
		if (bit_test(node_bitmap, n) == 0)
			continue;
		j = cr_get_coremap_offset(n);
		k = cr_get_coremap_offset(n + 1);
		for (; j < k; j++, c++) {
			if (bit_test(free_cores, j)) {
				if (c >= csize)	{
					error("cons_res: cr_job_test "
					      "core_bitmap index error on "
					      "node %s",
					      select_node_record[n].node_ptr->
					      name);
					drain_nodes(select_node_record[n].
						    node_ptr->name,
						    "Bad core count",
						    getuid());
					free_job_resources(&job_res);
					FREE_NULL_BITMAP(free_cores);
					return SLURM_ERROR;
				}
				bit_set(job_res->core_bitmap, c);
			}
		}

		if (layout_ptr && reqmap && bit_test(reqmap, n)) {
			job_res->cpus[i] = MIN(job_res->cpus[i],
					       layout_ptr[ll]);
		} else if (layout_ptr) {
			job_res->cpus[i] = 0;
		}
		total_cpus += job_res->cpus[i];
		i++;
	}

	/* When 'srun --overcommit' is used, ncpus is set to a minimum value
	 * in order to allocate the appropriate number of nodes based on the
	 * job request.
	 * For cons_res, all available logical processors will be allocated on
	 * each allocated node in order to accommodate the overcommit request.
	 */
	if (details_ptr->overcommit && details_ptr->num_tasks)
		job_res->ncpus = MIN(total_cpus, details_ptr->num_tasks);

	if (select_debug_flags & DEBUG_FLAG_SELECT_TYPE) {
		info("cons_res: cr_job_test: job %u ncpus %u cbits "
		     "%u/%u nbits %u", job_ptr->job_id,
		     job_res->ncpus, bit_set_count(free_cores),
		     bit_set_count(job_res->core_bitmap), job_res->nhosts);
	}
	FREE_NULL_BITMAP(free_cores);

	/* distribute the tasks and clear any unused cores */
	job_ptr->job_resrcs = job_res;
	error_code = cr_dist(job_ptr, cr_type, preempt_mode);
	if (error_code != SLURM_SUCCESS) {
		free_job_resources(&job_ptr->job_resrcs);
		return error_code;
	}

	/* translate job_res->cpus array into format with rep count */
	build_cnt = build_job_resources_cpu_array(job_res);
	if (job_ptr->details->whole_node == 1) {
		first = bit_ffs(job_res->node_bitmap);
		if (first != -1)
			last  = bit_fls(job_res->node_bitmap);
		else
			last = first - 1;
		job_ptr->total_cpus = 0;
		for (i = first; i <= last; i++) {
			if (!bit_test(job_res->node_bitmap, i))
				continue;
			/* This could make the job_res->cpus incorrect.
			 * Don't use job_res->cpus when allocating
			 * whole nodes as the job is finishing to
			 * subtract from the total cpu count or you
			 * will get an incorrect count.
			 */
			job_ptr->total_cpus += select_node_record[i].cpus;
		}
	} else if (cr_type & CR_SOCKET) {
		int ci = 0;
		int s, last_s, sock_cnt = 0;
		first = bit_ffs(job_res->node_bitmap);
		if (first != -1)
			last  = bit_fls(job_res->node_bitmap);
		else
			last = first - 1;
		job_ptr->total_cpus = 0;
		for (i = first; i <= last; i++) {
			if (!bit_test(job_res->node_bitmap, i))
				continue;
			sock_cnt = 0;
			for (s = 0; s < select_node_record[i].sockets; s++) {
				last_s = -1;
				for (c = 0; c<select_node_record[i].cores; c++){
					if (bit_test(job_res->core_bitmap, ci)){
						if (s != last_s) {
							sock_cnt++;
							last_s = s;
						}
					}
					ci++;
				}
			}
			job_ptr->total_cpus += (sock_cnt *
						select_node_record[i].cores *
						select_node_record[i].vpus);
		}
	} else if (build_cnt >= 0)
		job_ptr->total_cpus = build_cnt;
	else
		job_ptr->total_cpus = total_cpus;	/* best guess */

	if (!(cr_type & CR_MEMORY))
		return error_code;

	/* load memory allocated array */
	save_mem = details_ptr->pn_min_memory;
	if (save_mem & MEM_PER_CPU) {
		/* memory is per-cpu */
		save_mem &= (~MEM_PER_CPU);
		for (i = 0; i < job_res->nhosts; i++) {
			job_res->memory_allocated[i] = job_res->cpus[i] *
						       save_mem;
		}
	} else if (save_mem) {
		/* memory is per-node */
		for (i = 0; i < job_res->nhosts; i++) {
			job_res->memory_allocated[i] = save_mem;
		}
	} else {	/* --mem=0, allocate job all memory on node */
		uint32_t avail_mem, lowest_mem = 0;
		first = bit_ffs(job_res->node_bitmap);
		if (first != -1)
			last  = bit_fls(job_res->node_bitmap);
		else
			last = first - 1;
		for (i = first, j = 0; i <= last; i++) {
			if (!bit_test(job_res->node_bitmap, i))
				continue;
			avail_mem = select_node_record[i].real_memory -
				    select_node_record[i].mem_spec_limit;
			if ((j == 0) || (lowest_mem > avail_mem))
				lowest_mem = avail_mem;
			job_res->memory_allocated[j++] = avail_mem;
		}
		details_ptr->pn_min_memory = lowest_mem;
	}
	return error_code;
}
