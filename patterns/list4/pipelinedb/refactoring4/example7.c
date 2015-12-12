#ifdef MEMORY_CONTEXT_CHECKING
if (size < chunk->size)
			set_sentinel(AllocChunkGetPointer(chunk), size);
