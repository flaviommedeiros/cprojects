if (!(Syy>=0 && Sxx>=0 && See >= 0)
#ifndef FIXED_POINT
       || !(Sff < N*1e9 && Syy < N*1e9 && Sxx < N*1e9)
#endif
      )
   {
      /* Things have gone really bad */
      st->screwed_up += 50;
      for (i=0;i<st->frame_size*C;i++)
         out[i] = 0;
   } else if (SHR32(Sff, 2) > ADD32(Sdd, SHR32(MULT16_16(N, 10000),6)))
   {
      /* AEC seems to add lots of echo instead of removing it, let's see if it will improve */
      st->screwed_up++;
   } else {
      /* Everything's fine */
      st->screwed_up=0;
   }
