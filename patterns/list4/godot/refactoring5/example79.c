# ifdef BN_MUL_COMBA
if (n == 8)
		{
		bn_mul_comba8(&(t[0]),&(r[0]),&(r[n]));
		bn_mul_comba8(r,&(a[n]),&(b[n]));
		}
	else
# endif
		{
		bn_mul_recursive(&(t[0]),&(r[0]),&(r[n]),n,0,0,&(t[n2]));
		bn_mul_recursive(r,&(a[n]),&(b[n]),n,0,0,&(t[n2]));
		}
