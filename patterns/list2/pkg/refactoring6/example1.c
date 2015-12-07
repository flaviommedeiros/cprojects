if (
#ifndef NFL
      !ps->simplifying && 
#endif
      !--ps->lreduceadjustcnt)
    {
      /* With FREDUCE==110 and FREDADJ=121 we stir 'lreduce' to be
       * proportional to 'sqrt(conflicts)'.  In earlier version we actually
       * used  'FREDADJ=150', which results in 'lreduce' to approximate
       * 'conflicts^(log(1.1)/log(1.5))' which is close to the fourth root
       * of 'conflicts', since log(1.1)/log(1.5)=0.235 (as observed by
       * Donald Knuth). The square root is the same we get by a Glucose
       * style increase, which simply adds a constant at every reduction.
       * This would be way simpler to implement but for now we keep the more
       * complicated code using the adjust increments and counters.
       */
      ps->lreduceadjustinc *= FREDADJ; ps->lreduceadjustinc /= 100; ps->lreduceadjustcnt
      = ps->lreduceadjustinc;
      inc_lreduce (ps);
    }
