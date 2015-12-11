switch (st->factors[2*i])
       {
       case 2:
          kf_bfly2(fout,fstride[i]<<shift,st,m, fstride[i], m2);
          break;
       case 4:
          kf_bfly4(fout,fstride[i]<<shift,st,m, fstride[i], m2);
          break;
 #ifndef RADIX_TWO_ONLY
       case 3:
          kf_bfly3(fout,fstride[i]<<shift,st,m, fstride[i], m2);
          break;
       case 5:
          kf_bfly5(fout,fstride[i]<<shift,st,m, fstride[i], m2);
          break;
 #endif
       }
