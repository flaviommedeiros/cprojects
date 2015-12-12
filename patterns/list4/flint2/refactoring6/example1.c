if ((
#if FLINT64
                 (factor < FLINT_FACTOR_ONE_LINE_MAX) &&
#endif
                 (cofactor = n_factor_one_line(factor, FLINT_FACTOR_ONE_LINE_ITERS))) 
              || (cofactor = n_factor_SQUFOF(factor, FLINT_FACTOR_SQUFOF_ITERS)))
				{
					exp_arr[factors_left] = exp_arr[factors_left - 1];
               factor_arr[factors_left] = cofactor;
               factor_arr[factors_left - 1] /= cofactor;
               factors_left++;
				} else
				{
               flint_printf("Error (n_factor_partial). Failed to factor %wd.\n", n);
               abort();
				}
