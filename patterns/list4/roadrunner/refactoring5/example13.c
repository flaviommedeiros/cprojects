#ifdef TCC_ARM_EABI
if(vtop->type.t == VT_VOID) {
        if(s == RC_INT)
          o(0xE24DD004); /* sub sp,sp,#4 */
        vtop--;
      } else
#endif      
      if(s == RC_INT) {
	r = gv(s);
	o(0xE52D0004|(intr(r)<<12)); /* str r,[sp,#-4]! */
	vtop--;
      } else {
	plan2[keep]=s;
	keep++;
      }
