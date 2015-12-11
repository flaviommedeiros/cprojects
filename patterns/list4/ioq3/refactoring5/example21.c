#ifdef MEMDEBUG
if (block->id == HUNK_ID)
		{
			Log_Write("%6d, hunk %p, %8d: %24s line %6d: %s\r\n", i, block->ptr, block->size, block->file, block->line, block->label);
		} //end if
		else
		{
			Log_Write("%6d,      %p, %8d: %24s line %6d: %s\r\n", i, block->ptr, block->size, block->file, block->line, block->label);
		}
