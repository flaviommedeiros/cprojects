#ifdef SIMD_COEF_32
if (curdat.using_flat_buffers_sse2_ok)
						pFmt->params.algorithm_name = ALGORITHM_NAME_S2_256;
					else
#endif
						pFmt->params.algorithm_name = ALGORITHM_NAME_X86_S2_256;
