switch (l) {
#ifdef CONFIG_SCHED_SMT
	case SD_LV_SIBLING: /* set up CPU (sibling) groups */
		cpumask_and(d->this_sibling_map, cpu_map,
			    topology_thread_cpumask(cpu));
		if (cpu == cpumask_first(d->this_sibling_map))
			init_sched_build_groups(d->this_sibling_map, cpu_map,
						&cpu_to_cpu_group,
						d->send_covered, d->tmpmask);
		break;
#endif
#ifdef CONFIG_SCHED_MC
	case SD_LV_MC: /* set up multi-core groups */
		cpumask_and(d->this_core_map, cpu_map, cpu_coregroup_mask(cpu));
		if (cpu == cpumask_first(d->this_core_map))
			init_sched_build_groups(d->this_core_map, cpu_map,
						&cpu_to_core_group,
						d->send_covered, d->tmpmask);
		break;
#endif
#ifdef CONFIG_SCHED_BOOK
	case SD_LV_BOOK: /* set up book groups */
		cpumask_and(d->this_book_map, cpu_map, cpu_book_mask(cpu));
		if (cpu == cpumask_first(d->this_book_map))
			init_sched_build_groups(d->this_book_map, cpu_map,
						&cpu_to_book_group,
						d->send_covered, d->tmpmask);
		break;
#endif
	case SD_LV_CPU: /* set up physical groups */
		cpumask_and(d->nodemask, cpumask_of_node(cpu), cpu_map);
		if (!cpumask_empty(d->nodemask))
			init_sched_build_groups(d->nodemask, cpu_map,
						&cpu_to_phys_group,
						d->send_covered, d->tmpmask);
		break;
#ifdef CONFIG_NUMA
	case SD_LV_ALLNODES:
		init_sched_build_groups(cpu_map, cpu_map, &cpu_to_allnodes_group,
					d->send_covered, d->tmpmask);
		break;
#endif
	default:
		break;
	}
