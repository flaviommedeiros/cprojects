switch (combiner) {
#ifdef MPIIMPL_HAVE_MPI_COMBINER_DUP
    case MPI_COMBINER_DUP:
    #ifdef FLATTEN_DEBUG 
    DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_DUP\n");
    #endif
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
			      &old_ntypes, &old_combiner); 
        ADIOI_Datatype_iscontig(types[0], &old_is_contig);
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
            ADIOI_Flatten(types[0], flat, st_offset, curr_index);
        break;
#endif
#ifdef MPIIMPL_HAVE_MPI_COMBINER_SUBARRAY
    case MPI_COMBINER_SUBARRAY:
        {
	    int dims = ints[0];
	    MPI_Datatype stype;
      #ifdef FLATTEN_DEBUG 
      DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_SUBARRAY\n");
      #endif

	    ADIO_Type_create_subarray(dims,
				      &ints[1],        /* sizes */
				      &ints[dims+1],   /* subsizes */
				      &ints[2*dims+1], /* starts */
				      ints[3*dims+1],  /* order */
				      types[0],        /* type */
				      &stype);
	    ADIOI_Flatten(stype, flat, st_offset, curr_index);
	    MPI_Type_free(&stype);
	}
	break;
#endif
#ifdef MPIIMPL_HAVE_MPI_COMBINER_DARRAY
    case MPI_COMBINER_DARRAY:
	{
	    int dims = ints[2];
	    MPI_Datatype dtype;
      #ifdef FLATTEN_DEBUG 
      DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_DARRAY\n");
      #endif

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
      #ifdef FLATTEN_DEBUG 
      DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_DARRAY <ADIOI_Flatten(dtype, flat->indices[%#X] %#llX, flat->blocklens[%#X] %#llX, st_offset %#llX, curr_index %#X);\n",
              0, flat->indices[0], 0, flat->blocklens[0], st_offset, *curr_index);
      #endif
	    ADIOI_Flatten(dtype, flat, st_offset, curr_index);
      #ifdef FLATTEN_DEBUG 
      DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_DARRAY >ADIOI_Flatten(dtype, flat->indices[%#X] %#llX, flat->blocklens[%#X] %#llX, st_offset %#llX, curr_index %#X);\n",
              0, flat->indices[0], 0, flat->blocklens[0], st_offset, *curr_index);
      #endif
	    MPI_Type_free(&dtype);
	}
	break;
#endif
    case MPI_COMBINER_CONTIGUOUS:
    #ifdef FLATTEN_DEBUG 
    DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_CONTIGUOUS\n");
    #endif
	top_count = ints[0];
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
			      &old_ntypes, &old_combiner); 
        ADIOI_Datatype_iscontig(types[0], &old_is_contig);

	prev_index = *curr_index;
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
	    ADIOI_Flatten(types[0], flat, st_offset, curr_index);

	if (prev_index == *curr_index) {
/* simplest case, made up of basic or contiguous types */
	    j = *curr_index;
	    flat->indices[j] = st_offset;
	    MPI_Type_size(types[0], (int*)&old_size);
	    flat->blocklens[j] = top_count * old_size;
      #ifdef FLATTEN_DEBUG 
      DBG_FPRINTF(stderr,"ADIOI_Flatten:: simple flat->indices[%#X] %#llX, flat->blocklens[%#X] %#llX\n",j, flat->indices[j], j, flat->blocklens[j]);
      #endif
	    (*curr_index)++;
	}
	else {
/* made up of noncontiguous derived types */
	    j = *curr_index;
	    num = *curr_index - prev_index;

/* The noncontiguous types have to be replicated count times */
	    MPI_Type_extent(types[0], &old_extent);
	    for (m=1; m<top_count; m++) {
		for (i=0; i<num; i++) {
		    flat->indices[j] = flat->indices[j-num] + ADIOI_AINT_CAST_TO_OFFSET old_extent;
		    flat->blocklens[j] = flat->blocklens[j-num];
          #ifdef FLATTEN_DEBUG 
          DBG_FPRINTF(stderr,"ADIOI_Flatten:: derived flat->indices[%#X] %#llX, flat->blocklens[%#X] %#llX\n",j, flat->indices[j], j, flat->blocklens[j]);
          #endif
		    j++;
		}
	    }
	    *curr_index = j;
	}
	break;

    case MPI_COMBINER_VECTOR: 
    #ifdef FLATTEN_DEBUG 
    DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_VECTOR\n");
    #endif
	top_count = ints[0];
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
			      &old_ntypes, &old_combiner); 
        ADIOI_Datatype_iscontig(types[0], &old_is_contig);

	prev_index = *curr_index;
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
	    ADIOI_Flatten(types[0], flat, st_offset, curr_index);

	if (prev_index == *curr_index) {
/* simplest case, vector of basic or contiguous types */
    /* By using ADIO_Offset we preserve +/- sign and 
         avoid >2G integer arithmetic problems */
    ADIO_Offset blocklength = ints[1], stride = ints[2];
	    j = *curr_index;
	    flat->indices[j] = st_offset;
	    MPI_Type_size(types[0], (int*)&old_size);
	    flat->blocklens[j] = blocklength * old_size;
	    for (i=j+1; i<j+top_count; i++) {
		flat->indices[i] = flat->indices[i-1] + stride * old_size;
		flat->blocklens[i] = flat->blocklens[j];
	    }
	    *curr_index = i;
	}
	else {
/* vector of noncontiguous derived types */
    /* By using ADIO_Offset we preserve +/- sign and 
         avoid >2G integer arithmetic problems */
    ADIO_Offset blocklength = ints[1], stride = ints[2];

	    j = *curr_index;
	    num = *curr_index - prev_index;

/* The noncontiguous types have to be replicated blocklen times
   and then strided. Replicate the first one. */
	    MPI_Type_extent(types[0], &old_extent);
	    for (m=1; m<blocklength; m++) {
		for (i=0; i<num; i++) {
		    flat->indices[j] = flat->indices[j-num] + ADIOI_AINT_CAST_TO_OFFSET old_extent;
		    flat->blocklens[j] = flat->blocklens[j-num];
		    j++;
		}
	    }
	    *curr_index = j;

/* Now repeat with strides. */
	    num = *curr_index - prev_index;
	    for (i=1; i<top_count; i++) {
 		for (m=0; m<num; m++) {
		   flat->indices[j] =  flat->indices[j-num] + stride * ADIOI_AINT_CAST_TO_OFFSET old_extent;
		   flat->blocklens[j] = flat->blocklens[j-num];
		   j++;
		}
	    }
	    *curr_index = j;
	}
	break;

    case MPI_COMBINER_HVECTOR: 
    case MPI_COMBINER_HVECTOR_INTEGER: 
    #ifdef FLATTEN_DEBUG 
    DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_HVECTOR_INTEGER\n");
    #endif
	top_count = ints[0];
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
			      &old_ntypes, &old_combiner); 
        ADIOI_Datatype_iscontig(types[0], &old_is_contig);

	prev_index = *curr_index;
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
	    ADIOI_Flatten(types[0], flat, st_offset, curr_index);

	if (prev_index == *curr_index) {
/* simplest case, vector of basic or contiguous types */
    /* By using ADIO_Offset we preserve +/- sign and 
         avoid >2G integer arithmetic problems */
    ADIO_Offset blocklength = ints[1];
	    j = *curr_index;
	    flat->indices[j] = st_offset;
	    MPI_Type_size(types[0], (int*)&old_size);
	    flat->blocklens[j] = blocklength * old_size;
	    for (i=j+1; i<j+top_count; i++) {
		flat->indices[i] = flat->indices[i-1] + adds[0];
		flat->blocklens[i] = flat->blocklens[j];
	    }
	    *curr_index = i;
	}
	else {
/* vector of noncontiguous derived types */
    /* By using ADIO_Offset we preserve +/- sign and 
         avoid >2G integer arithmetic problems */
    ADIO_Offset blocklength = ints[1];

	    j = *curr_index;
	    num = *curr_index - prev_index;

/* The noncontiguous types have to be replicated blocklen times
   and then strided. Replicate the first one. */
	    MPI_Type_extent(types[0], &old_extent);
	    for (m=1; m<blocklength; m++) {
		for (i=0; i<num; i++) {
		    flat->indices[j] = flat->indices[j-num] + ADIOI_AINT_CAST_TO_OFFSET old_extent;
		    flat->blocklens[j] = flat->blocklens[j-num];
		    j++;
		}
	    }
	    *curr_index = j;

/* Now repeat with strides. */
	    num = *curr_index - prev_index;
	    for (i=1; i<top_count; i++) {
 		for (m=0; m<num; m++) {
		   flat->indices[j] =  flat->indices[j-num] + adds[0];
		   flat->blocklens[j] = flat->blocklens[j-num];
		   j++;
		}
	    }
	    *curr_index = j;
	}
	break;

    case MPI_COMBINER_INDEXED: 
    #ifdef FLATTEN_DEBUG 
    DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_INDEXED\n");
    #endif
	top_count = ints[0];
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
			      &old_ntypes, &old_combiner); 
        ADIOI_Datatype_iscontig(types[0], &old_is_contig);
	MPI_Type_extent(types[0], &old_extent);

	prev_index = *curr_index;
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
  {
    /* By using ADIO_Offset we preserve +/- sign and 
         avoid >2G integer arithmetic problems */
    ADIO_Offset stride = ints[top_count+1];
        ADIOI_Flatten(types[0], flat,
         st_offset+stride* ADIOI_AINT_CAST_TO_OFFSET old_extent, curr_index);
  }

	if (prev_index == *curr_index) {
/* simplest case, indexed type made up of basic or contiguous types */
	    j = *curr_index;
	    for (i=j; i<j+top_count; i++) {
    /* By using ADIO_Offset we preserve +/- sign and 
         avoid >2G integer arithmetic problems */
    ADIO_Offset blocklength = ints[1+i-j], stride = ints[top_count+1+i-j];
		flat->indices[i] = st_offset + stride* ADIOI_AINT_CAST_TO_OFFSET old_extent;
		flat->blocklens[i] = blocklength* ADIOI_AINT_CAST_TO_OFFSET old_extent;
	    }
	    *curr_index = i;
	}
	else {
/* indexed type made up of noncontiguous derived types */

	    j = *curr_index;
	    num = *curr_index - prev_index;
	    basic_num = num;

/* The noncontiguous types have to be replicated blocklens[i] times
   and then strided. Replicate the first one. */
	    for (m=1; m<ints[1]; m++) {
		for (i=0; i<num; i++) {
		    flat->indices[j] = flat->indices[j-num] + ADIOI_AINT_CAST_TO_OFFSET old_extent;
		    flat->blocklens[j] = flat->blocklens[j-num];
		    j++;
		}
	    }
	    *curr_index = j;

/* Now repeat with strides. */
	    for (i=1; i<top_count; i++) {
		num = *curr_index - prev_index;
		prev_index = *curr_index;
		for (m=0; m<basic_num; m++) {
      /* By using ADIO_Offset we preserve +/- sign and 
         avoid >2G integer arithmetic problems */
      ADIO_Offset stride = ints[top_count+1+i]-ints[top_count+i];
		    flat->indices[j] = flat->indices[j-num] + stride* ADIOI_AINT_CAST_TO_OFFSET old_extent;
		    flat->blocklens[j] = flat->blocklens[j-num];
		    j++;
		}
		*curr_index = j;
		for (m=1; m<ints[1+i]; m++) {
                    for (k=0; k<basic_num; k++) {
                        flat->indices[j] = flat->indices[j-basic_num] + ADIOI_AINT_CAST_TO_OFFSET old_extent;
                        flat->blocklens[j] = flat->blocklens[j-basic_num];
                        j++;
                    }
                }
		*curr_index = j;
	    }
	}
	break;

        /* FIXME: using the same code as indexed_block for
         * hindexed_block doesn't look correct.  Needs to be carefully
         * looked into. */
    case MPI_COMBINER_HINDEXED_BLOCK:
    case MPI_COMBINER_INDEXED_BLOCK:
    #ifdef FLATTEN_DEBUG 
    DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_INDEXED_BLOCK\n");
    #endif
	top_count = ints[0];
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
			      &old_ntypes, &old_combiner); 
        ADIOI_Datatype_iscontig(types[0], &old_is_contig);
	MPI_Type_extent(types[0], &old_extent);

	prev_index = *curr_index;
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
  {
      /* By using ADIO_Offset we preserve +/- sign and 
         avoid >2G integer arithmetic problems */
      ADIO_Offset stride = ints[1+1];
        ADIOI_Flatten(types[0], flat,
         st_offset+stride* ADIOI_AINT_CAST_TO_OFFSET old_extent, curr_index);
  }

	if (prev_index == *curr_index) {
/* simplest case, indexed type made up of basic or contiguous types */
	    j = *curr_index;
	    for (i=j; i<j+top_count; i++) {
      /* By using ADIO_Offset we preserve +/- sign and 
         avoid >2G integer arithmetic problems */
      ADIO_Offset blocklength = ints[1], stride = ints[1+1+i-j];
		flat->indices[i]   = st_offset + stride* ADIOI_AINT_CAST_TO_OFFSET old_extent;
		flat->blocklens[i] = blocklength* ADIOI_AINT_CAST_TO_OFFSET old_extent;
	    }
	    *curr_index = i;
	}
	else {
/* vector of noncontiguous derived types */

	    j = *curr_index;
	    num = *curr_index - prev_index;

/* The noncontiguous types have to be replicated blocklens[i] times
   and then strided. Replicate the first one. */
	    for (m=1; m<ints[1]; m++) {
		for (i=0; i<num; i++) {
		    flat->indices[j]   = flat->indices[j-num] + ADIOI_AINT_CAST_TO_OFFSET old_extent;
		    flat->blocklens[j] = flat->blocklens[j-num];
		    j++;
		}
	    }
	    *curr_index = j;

/* Now repeat with strides. */
	    num = *curr_index - prev_index;
	    for (i=1; i<top_count; i++) {
		for (m=0; m<num; m++) {
      /* By using ADIO_Offset we preserve +/- sign and 
         avoid >2G integer arithmetic problems */
      ADIO_Offset stride = ints[2+i]-ints[1+i];
		    flat->indices[j]   = flat->indices[j-num] + stride* ADIOI_AINT_CAST_TO_OFFSET old_extent;
		    flat->blocklens[j] = flat->blocklens[j-num];
		    j++;
		}
	    }
	    *curr_index = j;
	}
	break;

    case MPI_COMBINER_HINDEXED: 
    case MPI_COMBINER_HINDEXED_INTEGER:
    #ifdef FLATTEN_DEBUG 
    DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_HINDEXED_INTEGER\n");
    #endif
	top_count = ints[0];
        MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
			      &old_ntypes, &old_combiner); 
        ADIOI_Datatype_iscontig(types[0], &old_is_contig);

	prev_index = *curr_index;
	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
  {
        ADIOI_Flatten(types[0], flat, st_offset+adds[0], curr_index); 
  }

	if (prev_index == *curr_index) {
/* simplest case, indexed type made up of basic or contiguous types */
	    j = *curr_index;
	    MPI_Type_size(types[0], (int*)&old_size);
	    for (i=j; i<j+top_count; i++) {
        /* By using ADIO_Offset we preserve +/- sign and 
           avoid >2G integer arithmetic problems */
        ADIO_Offset blocklength = ints[1+i-j];
		flat->indices[i] = st_offset + adds[i-j];
		flat->blocklens[i] = blocklength*old_size;
	    }
	    *curr_index = i;
	}
	else {
/* indexed type made up of noncontiguous derived types */

	    j = *curr_index;
	    num = *curr_index - prev_index;
	    basic_num = num;

/* The noncontiguous types have to be replicated blocklens[i] times
   and then strided. Replicate the first one. */
	    MPI_Type_extent(types[0], &old_extent);
	    for (m=1; m<ints[1]; m++) {
		for (i=0; i<num; i++) {
		    flat->indices[j] = flat->indices[j-num] + ADIOI_AINT_CAST_TO_OFFSET old_extent;
		    flat->blocklens[j] = flat->blocklens[j-num];
		    j++;
		}
	    }
	    *curr_index = j;

/* Now repeat with strides. */
	    for (i=1; i<top_count; i++) {
		num = *curr_index - prev_index;
		prev_index = *curr_index;
		for (m=0; m<basic_num; m++) {
		    flat->indices[j] = flat->indices[j-num] + adds[i] - adds[i-1];
		    flat->blocklens[j] = flat->blocklens[j-num];
		    j++;
		}
		*curr_index = j;
		for (m=1; m<ints[1+i]; m++) {
                    for (k=0; k<basic_num; k++) {
                        flat->indices[j] = flat->indices[j-basic_num] + ADIOI_AINT_CAST_TO_OFFSET old_extent;
                        flat->blocklens[j] = flat->blocklens[j-basic_num];
		    j++;
                    }
		}
		*curr_index = j;
	    }
	}
	break;

    case MPI_COMBINER_STRUCT: 
    case MPI_COMBINER_STRUCT_INTEGER: 
    #ifdef FLATTEN_DEBUG 
    DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_STRUCT_INTEGER\n");
    #endif
	top_count = ints[0];
	for (n=0; n<top_count; n++) {
	    MPI_Type_get_envelope(types[n], &old_nints, &old_nadds,
				  &old_ntypes, &old_combiner); 
            ADIOI_Datatype_iscontig(types[n], &old_is_contig);

	    prev_index = *curr_index;
            if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig))
		ADIOI_Flatten(types[n], flat, st_offset+adds[n], curr_index);

	    if (prev_index == *curr_index) {
/* simplest case, current type is basic or contiguous types */
        /* By using ADIO_Offset we preserve +/- sign and 
           avoid >2G integer arithmetic problems */
        ADIO_Offset blocklength = ints[1+n];
		j = *curr_index;
		flat->indices[j] = st_offset + adds[n];
		MPI_Type_size(types[n], (int*)&old_size);
		flat->blocklens[j] = blocklength * old_size;
        #ifdef FLATTEN_DEBUG 
        DBG_FPRINTF(stderr,"ADIOI_Flatten:: simple adds[%#X] "MPI_AINT_FMT_HEX_SPEC", flat->indices[%#X] %#llX, flat->blocklens[%#X] %#llX\n",n,adds[n],j, flat->indices[j], j, flat->blocklens[j]);
        #endif
		(*curr_index)++;
	    }
	    else {
/* current type made up of noncontiguous derived types */

		j = *curr_index;
		num = *curr_index - prev_index;

/* The current type has to be replicated blocklens[n] times */
		MPI_Type_extent(types[n], &old_extent);
		for (m=1; m<ints[1+n]; m++) {
		    for (i=0; i<num; i++) {
			flat->indices[j] = flat->indices[j-num] + ADIOI_AINT_CAST_TO_OFFSET old_extent;
			flat->blocklens[j] = flat->blocklens[j-num];
            #ifdef FLATTEN_DEBUG 
            DBG_FPRINTF(stderr,"ADIOI_Flatten:: simple old_extent "MPI_AINT_FMT_HEX_SPEC", flat->indices[%#X] %#llX, flat->blocklens[%#X] %#llX\n",old_extent,j, flat->indices[j], j, flat->blocklens[j]);
            #endif
			j++;
		    }
		}
		*curr_index = j;
	    }
	}
 	break;

    case MPI_COMBINER_RESIZED: 
    #ifdef FLATTEN_DEBUG 
    DBG_FPRINTF(stderr,"ADIOI_Flatten:: MPI_COMBINER_RESIZED\n");
    #endif

    /* This is done similar to a type_struct with an lb, datatype, ub */

    /* handle the Lb */
	j = *curr_index;
	flat->indices[j] = st_offset + adds[0];
	flat->blocklens[j] = 0;

        #ifdef FLATTEN_DEBUG 
        DBG_FPRINTF(stderr,"ADIOI_Flatten:: simple adds[%#X] "MPI_AINT_FMT_HEX_SPEC", flat->indices[%#X] %#llX, flat->blocklens[%#X] %#llX\n",0,adds[0],j, flat->indices[j], j, flat->blocklens[j]);
        #endif

	(*curr_index)++;

	/* handle the datatype */

	MPI_Type_get_envelope(types[0], &old_nints, &old_nadds,
			      &old_ntypes, &old_combiner); 
	ADIOI_Datatype_iscontig(types[0], &old_is_contig);

	if ((old_combiner != MPI_COMBINER_NAMED) && (!old_is_contig)) {
	    ADIOI_Flatten(types[0], flat, st_offset+adds[0], curr_index);
	}
	else {
            /* current type is basic or contiguous */
	    j = *curr_index;
	    flat->indices[j] = st_offset;
	    MPI_Type_size(types[0], (int*)&old_size);
	    flat->blocklens[j] = old_size;

            #ifdef FLATTEN_DEBUG 
	    DBG_FPRINTF(stderr,"ADIOI_Flatten:: simple adds[%#X] "MPI_AINT_FMT_HEX_SPEC", flat->indices[%#X] %#llX, flat->blocklens[%#X] %#llX\n",0,adds[0],j, flat->indices[j], j, flat->blocklens[j]);
            #endif

	    (*curr_index)++;
	}

	/* take care of the extent as a UB */
	j = *curr_index;
	flat->indices[j] = st_offset + adds[0] + adds[1];
	flat->blocklens[j] = 0;

        #ifdef FLATTEN_DEBUG 
        DBG_FPRINTF(stderr,"ADIOI_Flatten:: simple adds[%#X] "MPI_AINT_FMT_HEX_SPEC", flat->indices[%#X] %#llX, flat->blocklens[%#X] %#llX\n",1,adds[1],j, flat->indices[j], j, flat->blocklens[j]);
        #endif

	(*curr_index)++;

 	break;

    default:
	/* TODO: FIXME (requires changing prototypes to return errors...) */
	DBG_FPRINTF(stderr, "Error: Unsupported datatype passed to ADIOI_Flatten\n");
	MPI_Abort(MPI_COMM_WORLD, 1);
    }
