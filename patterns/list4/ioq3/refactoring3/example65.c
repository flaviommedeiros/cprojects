switch (st->factors[2*i])
      {
      case 2:
         ki_bfly2(fout,fstride[i]<<shift,st,m, fstride[i], m2);
         break;
      case 4:
         ki_bfly4(fout,fstride[i]<<shift,st,m, fstride[i], m2);
         break;
#ifndef RADIX_TWO_ONLY
      case 3:
         ki_bfly3(fout,fstride[i]<<shift,st,m, fstride[i], m2);
         break;
      case 5:
         ki_bfly5(fout,fstride[i]<<shift,st,m, fstride[i], m2);
         break;
#endif
      }
