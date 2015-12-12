#ifdef CONFIG_ETRAX_NANDFLASH
if (main_mtd->type == MTD_NANDFLASH) {
				axis_partitions[pidx].size =
					(((ptable+1)->offset ==
					  PARTITIONTABLE_END_MARKER) ?
					  main_mtd->size :
					  ((ptable+1)->offset + offset)) -
					(ptable->offset + offset);

			} else
#endif /* CONFIG_ETRAX_NANDFLASH */
				axis_partitions[pidx].size = ptable->size;
