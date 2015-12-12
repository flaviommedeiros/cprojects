#if defined(__MPIR_VERSION)
if (mpf_fits_si_p(x))
#else
    if (flint_mpf_fits_slong_p(x))
#endif
    {
        slong cx = flint_mpf_get_si(x);
        fmpz_set_si(f, cx);
    }
    else
    {
        __mpz_struct *z = _fmpz_promote(f);
        mpz_set_f(z, x);
    }
