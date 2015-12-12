#ifdef RESAMPLER_SSE
if ( resampler_has_sse )
                resampler_run_blam_sse( r, &out, out + write_size + write_extra );
            else
#endif
                resampler_run_blam( r, &out, out + write_size + write_extra );
