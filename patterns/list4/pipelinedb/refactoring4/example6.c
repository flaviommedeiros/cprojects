#ifdef MEMORY_CONTEXT_CHECKING
if (size > oldrequest)
			randomize_mem((char *) pointer + oldrequest,
						  size - oldrequest);
