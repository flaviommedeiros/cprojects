#ifdef COFF_WITH_PE
if (output_bfd == (bfd *) NULL)
	{
	  reloc_howto_type *howto = reloc_entry->howto;

	  /* Although PC relative relocations are very similar between
	     PE and non-PE formats, but they are off by 1 << howto->size
	     bytes. For the external relocation, PE is very different
	     from others. See md_apply_fix3 () in gas/config/tc-i386.c.
	     When we link PE and non-PE object files together to
	     generate a non-PE executable, we have to compensate it
	     here.  */
	  if (howto->pc_relative && howto->pcrel_offset)
	    diff = -(1 << howto->size);
	  else if (symbol->flags & BSF_WEAK)
	    diff = reloc_entry->addend - symbol->value;
	  else
	    diff = -reloc_entry->addend;
	}
      else
#endif
	diff = reloc_entry->addend;
