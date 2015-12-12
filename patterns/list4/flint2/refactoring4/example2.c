#if FLINT64
if (count > 220 * flint_test_multiplier()) 
#else
   if (count > 430 * flint_test_multiplier())
#endif
   {
      flint_printf("FAIL:\n");
      flint_printf("count = %wu\n", count);
      abort();
   }
