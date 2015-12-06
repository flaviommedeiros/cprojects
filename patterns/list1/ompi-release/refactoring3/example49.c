switch (combiner) {
#ifdef MPIIMPL_HAVE_MPI_COMBINER_DUP
    case MPI_COMBINER_DUP:
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
                              &old_ntypes, &old_combiner); 
	ADIOI_Datatype_iscontig(types[0], &old_is_contig);
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
	    count = ADIOI_Count_contiguous_blocks(types[0], curr_index);
	else {
		count = 1;
		(*curr_index)++;
	}
        break;
#endif
#ifdef MPIIMPL_HAVE_MPI_COMBINER_SUBARRAY
    case MPI_COMBINER_SUBARRAY:
        {
	    int dims = ints[0];
	    MPI_Datatype stype;

	    ADIO_Type_create_subarray(dims,
				      &ints[1],        /* sizes */
				      &ints[dims+1],   /* subsizes */
				      &ints[2*dims+1], /* starts */
				      ints[3*dims+1],  /* order */
				      types[0],        /* type */
				      &stype);
	    count = ADIOI_Count_contiguous_blocks(stype, curr_index);
	    /* curr_index will have already been updated; just pass
	     * count back up.
	     */
	    MPI_Type_free(&stype);

	}
	break;
#endif
#ifdef MPIIMPL_HAVE_MPI_COMBINER_DARRAY
    case MPI_COMBINER_DARRAY:
	{
	    int dims = ints[2];
	    MPI_Datatype dtype;

	    ADIO_Type_create_darray(ints[0],         /* size */
				    ints[1],         /* rank */
				    dims,
				    &ints[3],        /* gsizes */
				    &ints[dims+3],   /* distribs */
				    &ints[2*dims+3], /* dargs */
				    &ints[3*dims+3], /* psizes */
				    ints[4*dims+3],  /* order */
				    types[0],
				    &dtype);
	    count = ADIOI_Count_contiguous_blocks(dtype, curr_index);
	    /* curr_index will have already been updated; just pass
	     * count back up.
	     */
	    MPI_Type_free(&dtype);
	}
	break;
#endif
    case MPI_COMBINER_CONTIGUOUS:
        top_count = ints[0];
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
                              &old_ntypes, &old_combiner); 
	ADIOI_Datatype_iscontig(types[0], &old_is_contig);

	prev_index = *curr_index;
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
	    count = ADIOI_Count_contiguous_blocks(types[0], curr_index);
	else count = 1;

	if (prev_index == *curr_index) 
/* simplest case, made up of basic or contiguous types */
	    (*curr_index)++;
	else {
/* made up of noncontiguous derived types */
	    num = *curr_index - prev_index;
	    count *= top_count;
	    *curr_index += (top_count - 1)*num;
	}
	break;

    case MPI_COMBINER_VECTOR:
    case MPI_COMBINER_HVECTOR:
    case MPI_COMBINER_HVECTOR_INTEGER: 
        top_count = ints[0];
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
                              &old_ntypes, &old_combiner); 
	ADIOI_Datatype_iscontig(types[0], &old_is_contig);

	prev_index = *curr_index;
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
	    count = ADIOI_Count_contiguous_blocks(types[0], curr_index);
	else count = 1;

	if (prev_index == *curr_index) {
/* simplest case, vector of basic or contiguous types */
	    count = top_count;
	    *curr_index += count;
	}
	else {
/* vector of noncontiguous derived types */
	    num = *curr_index - prev_index;

/* The noncontiguous types have to be replicated blocklen times
   and then strided. */
	    count *= ints[1] * top_count;

/* First one */
	    *curr_index += (ints[1] - 1)*num;

/* Now repeat with strides. */
	    num = *curr_index - prev_index;
	    *curr_index += (top_count - 1)*num;
	}
	break;

    case MPI_COMBINER_INDEXED: 
    case MPI_COMBINER_HINDEXED:
    case MPI_COMBINER_HINDEXED_INTEGER:
        top_count = ints[0];
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
                              &old_ntypes, &old_combiner); 
	ADIOI_Datatype_iscontig(types[0], &old_is_contig);

	prev_index = *curr_index;
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
	    count = ADIOI_Count_contiguous_blocks(types[0], curr_index);
	else count = 1;

	if (prev_index == *curr_index) {
/* simplest case, indexed type made up of basic or contiguous types */
	    count = top_count;
	    *curr_index += count;
	}
	else {
/* indexed type made up of noncontiguous derived types */
	    basic_num = *curr_index - prev_index;

/* The noncontiguous types have to be replicated blocklens[i] times
   and then strided. */
	    *curr_index += (ints[1]-1) * basic_num;
	    count *= ints[1];

/* Now repeat with strides. */
	    for (i=1; i<top_count; i++) {
		count += ints[1+i] * basic_num;
		*curr_index += ints[1+i] * basic_num;
	    }
	}
	break;

    case MPI_COMBINER_INDEXED_BLOCK:
        top_count = ints[0];
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
                              &old_ntypes, &old_combiner); 
	ADIOI_Datatype_iscontig(types[0], &old_is_contig);

	prev_index = *curr_index;
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
	    count = ADIOI_Count_contiguous_blocks(types[0], curr_index);
	else count = 1;

	if (prev_index == *curr_index) {
/* simplest case, indexed type made up of basic or contiguous types */
	    count = top_count;
	    *curr_index += count;
	}
	else {
/* indexed type made up of noncontiguous derived types */
	    basic_num = *curr_index - prev_index;

/* The noncontiguous types have to be replicated blocklens[i] times
   and then strided. */
	    *curr_index += (ints[1]-1) * basic_num;
	    count *= ints[1];

/* Now repeat with strides. */
	    *curr_index += (top_count-1) * count;
	    count *= top_count;
	}
	break;

    case MPI_COMBINER_STRUCT: 
    case MPI_COMBINER_STRUCT_INTEGER: 
        top_count = ints[0];
	count = 0;
	for (n=0; n<top_count; n++) {
            MPI_Type_get_envelope(types[n], &old_nints, &old_nadds,
                                  &old_ntypes, &old_combiner); 
	    ADIOI_Datatype_iscontig(types[n], &old_is_contig);

	    prev_index = *curr_index;
	    if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
	    count += ADIOI_Count_contiguous_blocks(types[n], curr_index);

	    if (prev_index == *curr_index) {
/* simplest case, current type is basic or contiguous types */
		count++;
		(*curr_index)++;
	    }
	    else {
/* current type made up of noncontiguous derived types */
/* The current type has to be replicated blocklens[n] times */

		num = *curr_index - prev_index;
		count += (ints[1+n]-1)*num;
		(*curr_index) += (ints[1+n]-1)*num;
	    }
	}
	break;

    case MPI_COMBINER_RESIZED: 
	/* treat it as a struct with lb, type, ub */

	/* add 2 for lb and ub */
	(*curr_index) += 2;
	count += 2;

	/* add for datatype */ 
	MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
                                  &old_ntypes, &old_combiner); 
	ADIOI_Datatype_iscontig(types[0], &old_is_contig);

	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig)) {
	    count += ADIOI_Count_contiguous_blocks(types[0], curr_index);
	}
	else {
        /* basic or contiguous type */
	    count++;
	    (*curr_index)++;
	}
	break;

    default:
	/* TODO: FIXME */
	DBG_FPRINTF(stderr, "Error: Unsupported datatype passed to ADIOI_Count_contiguous_blocks, combiner = %d\n", combiner);
	MPI_Abort(MPI_COMM_WORLD, 1);
    }
