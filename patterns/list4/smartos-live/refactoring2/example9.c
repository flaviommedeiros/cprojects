#ifdef Avoid_Underflow
if (scale && y <= P*Exp_msk1)
                set_word0(aadj1, word0(aadj1) + (P+1)*Exp_msk1 - y);
