#ifdef RESAMPLER_SSE
if ( resampler_has_sse )
                resampler_run_cubic_sse( r, &out, out + write_size );
            else
#endif
                resampler_run_cubic( r, &out, out + write_size );
