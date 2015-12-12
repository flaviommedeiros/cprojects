#ifdef HAVE_GPU
if(usegpu_flag)
    {
      if(g_proc_id == 0) printf("Using GPU for inversion\n");
      // call mixed_solve_DiracDaggerDaggerD for double precision calculations on gpu - may be faster if the device supports compute capability >= 2.0 (fermi generation)
      
      {//include M^{*2} into twisted mass g_mu => saves one assign_multiply_add;
        double g_muWithoutMStarSquare=g_mu;

        g_mu=sqrt(g_mu*g_mu+mstarsq);
        mixed_solve_DiracDaggerDiracDiracDaggerDirac ( R, S, X_psiSIterations, X_psiSPrecision, 0/*!rel_prec*/, VOLUME);
        //mixed_solve_DiracDaggerDiracDiracDagerDiracD( R, S, X_psiSIterations, X_psiSPrecision, 0/*!rel_prec*/, VOLUME);
        g_mu=g_muWithoutMStarSquare;
      }//R holds now the value of (D^+DD^+D)^-1 !

      DdaggerD_plus_M(aux,R);
      
      assign_mul_add_mul_r( R, aux, mstarsq, -1, VOLUME);
      assign_mul_add_mul_r( R, S, 4*mstarsq,  1, VOLUME);//1-4mstarsq(-(D^+D+mstarsq)^-1 + mstarsq*(D^+D+mstarsq)^-2)


      free(aux_);
      fflush(stdout);
    }
    else
  #endif
  {
    X_psi(aux, S, mstarsq);
    X_psi(R, aux, mstarsq);
  }
