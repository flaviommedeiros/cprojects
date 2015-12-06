#  ifdef MONT_EXP_WORD
if (a->top == 1 && !a->neg && (BN_get_flags(p, BN_FLG_CONSTTIME) == 0))
			{
			BN_ULONG A = a->d[0];
			ret=BN_mod_exp_mont_word(r,A,p,m,ctx,NULL);
			}
		else
#  endif
			ret=BN_mod_exp_mont(r,a,p,m,ctx,NULL);
