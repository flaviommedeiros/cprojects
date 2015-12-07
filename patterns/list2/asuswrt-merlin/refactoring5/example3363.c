#ifdef CONFIG_SMP
if (online_cpus > 1)
			schedule_work_on(1 - raw_smp_processor_id(), &et->txq_task.work);
			else
#endif /* CONFIG_SMP */
			schedule_work(&et->txq_task.work);
