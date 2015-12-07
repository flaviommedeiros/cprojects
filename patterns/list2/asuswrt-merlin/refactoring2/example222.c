#ifdef HAVE_LIBUNWIND_IA64_H
if (!libunwind_is_initialized ()
	  || libunwind_get_reg_special (gdbarch, regcache, regnum, buf) != 0)
#endif
	{
	  /* The fallback position is to assume that r32-r127 are found sequentially
	     in memory starting at $bof.  This isn't always true, but without libunwind,
	     this is the best we can do.  */
	  ULONGEST cfm;
	  ULONGEST bsp;
	  CORE_ADDR reg;
	  regcache_cooked_read_unsigned (regcache, IA64_BSP_REGNUM, &bsp);
	  regcache_cooked_read_unsigned (regcache, IA64_CFM_REGNUM, &cfm);
	  
	  /* The bsp points at the end of the register frame so we
	     subtract the size of frame from it to get start of register frame.  */
	  bsp = rse_address_add (bsp, -(cfm & 0x7f));
	  
	  if ((cfm & 0x7f) > regnum - V32_REGNUM) 
	    {
	      ULONGEST reg_addr = rse_address_add (bsp, (regnum - V32_REGNUM));
	      reg = read_memory_integer ((CORE_ADDR)reg_addr, 8);
	      store_unsigned_integer (buf, register_size (current_gdbarch, regnum), reg);
	    }
	  else
	    store_unsigned_integer (buf, register_size (current_gdbarch, regnum), 0);
	}
