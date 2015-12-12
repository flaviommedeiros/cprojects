#ifdef HAVE_GPU
if(usegpu_flag)
    {
      if(g_proc_id == 0) printf("Using GPU for inversion\n");
      // call mixed_solve_DiracDaggerDaggerD for double precision calculations on gpu - may be faster if the device supports compute capability >= 2.0 (fermi generation)
      {//include M^{*2} into twisted mass g_mu => saves one assign_multiply_add;
        g_mu=sqrt(g_mu*g_mu+mstarsq);
        mixed_solve_DiracDaggerDirac ( R, S, X_psiSIterations, X_psiSPrecision, 0/*!rel_prec*/, VOLUME);
        //mixed_solve_DiracDaggerDiracD( R, S, X_psiSIterations, X_psiSPrecision, 0/*!rel_prec*/, VOLUME);
        g_mu=g_muWithoutMStarSquare;
      }
    }
    else
  #endif
  {
    if(g_proc_id == 0) printf("Using CPU for inversion\n");
    cg_her( R, S, X_psiSIterations, X_psiSPrecision, 0, VOLUME, &DdaggerD_plus_M);
  }
