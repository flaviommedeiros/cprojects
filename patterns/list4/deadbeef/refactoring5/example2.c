#ifdef ARM7_THUMB
if (cpu->Rx[ARM7_CPSR] & ARM7_CPSR_T)
  {
	ARM7i_Thumb_Step(cpu);
  }
  else
#endif
  {
        ARM7i_Step (cpu);
  }
