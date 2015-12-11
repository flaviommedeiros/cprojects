if (alpha == 1 /* opaque pixel component */ || !do_background
#ifdef PNG_READ_ALPHA_MODE_SUPPORTED
      || do_background == ALPHA_MODE_OFFSET + PNG_ALPHA_PNG
#endif
      || (alpha < 0 /* alpha channel */
#ifdef PNG_READ_ALPHA_MODE_SUPPORTED
      && do_background != ALPHA_MODE_OFFSET + PNG_ALPHA_BROKEN
#endif
      ))
   {
      /* Then get the gamma corrected version of 'i' and compare to 'od', any
       * error less than .5 is insignificant - just quantization of the output
       * value to the nearest digital value (nevertheless the error is still
       * recorded - it's interesting ;-)
       */
      double encoded_sample = i;
      double encoded_error;

      /* alpha less than 0 indicates the alpha channel, which is always linear
       */
      if (alpha >= 0 && vi->gamma_correction > 0)
         encoded_sample = pow(encoded_sample, vi->gamma_correction);
      encoded_sample *= outmax;

      encoded_error = fabs(od-encoded_sample);

      if (encoded_error > vi->dp->maxerrout)
         vi->dp->maxerrout = encoded_error;

      if (encoded_error < vi->maxout_total && encoded_error < vi->outlog)
         return i;
   }
