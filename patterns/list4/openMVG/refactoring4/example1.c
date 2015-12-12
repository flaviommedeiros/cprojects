#if (FLT == VL_TYPE_FLOAT)
if (coeff > VL_EPSILON_F)
#else
        else if (coeff > VL_EPSILON_D)
#endif
        {
          inters = ((r - r_) + coeff * (x2 - x2_)) / (x - x_) / (2*coeff) + offset ;
        } else {
          /* If coeff is very small, the parabolas are flat (= lines).
           In this case the previous parabola should be deleted if the current
           pixel has lower score */
#if (FLT == VL_TYPE_FLOAT)
          inters = (r < r_) ? - VL_INFINITY_F : VL_INFINITY_F ;
#else
          inters = (r < r_) ? - VL_INFINITY_D : VL_INFINITY_D ;
#endif
        }
