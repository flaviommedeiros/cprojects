if(distance==0 || 
#if FASTLZ_LEVEL==1
    (distance >= MAX_DISTANCE) ||
#else
    (distance >= MAX_FARDISTANCE) ||
#endif
    *ref++ != *ip++ || *ref++!=*ip++ || *ref++!=*ip++)
      goto literal;
