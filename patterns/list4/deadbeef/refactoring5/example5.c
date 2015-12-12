#ifdef RESAMPLER_SSE
if ( resampler_has_sse )
                used = resampler_run_blep_sse( r, &out, out + write_size + write_extra );
            else
#endif
                used = resampler_run_blep( r, &out, out + write_size + write_extra );
