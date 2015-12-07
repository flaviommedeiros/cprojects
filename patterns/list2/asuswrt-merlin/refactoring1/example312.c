if (0)
        {
          ;
        }
#ifdef USE_AESNI
      else if ((_gcry_get_hw_features () & HWF_INTEL_AESNI))
        {
          ctx->use_aesni = 1;
        }
#endif
