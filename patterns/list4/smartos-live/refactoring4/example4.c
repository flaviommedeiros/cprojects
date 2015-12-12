#ifdef Avoid_Underflow
if (y <= P*Exp_msk1 && aadj > 1.)
#else
            if (y <= (P-1)*Exp_msk1 && aadj > 1.)
#endif
                {
                aadj1 = (double)(int32)(aadj + 0.5);
                if (!dsign)
                    aadj1 = -aadj1;
            }
