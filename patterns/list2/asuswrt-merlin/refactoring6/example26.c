if (r_type == R_SH_REL32
#ifdef INCLUDE_SHMEDIA
		  || r_type == R_SH_IMM_LOW16_PCREL
		  || r_type == R_SH_IMM_MEDLOW16_PCREL
		  || r_type == R_SH_IMM_MEDHI16_PCREL
		  || r_type == R_SH_IMM_HI16_PCREL
#endif
		  )
		p->pc_count += 1;
