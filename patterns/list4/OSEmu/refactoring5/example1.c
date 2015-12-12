# ifdef BN_MUL_COMBA
if(n == 4)
	{
		if(!zero)
		{ bn_mul_comba4(&(t[n2]), t, &(t[n])); }
		else
		{ memset(&(t[n2]), 0, 8 * sizeof(BN_ULONG)); }

		bn_mul_comba4(r, a, b);
		bn_mul_comba4(&(r[n2]), &(a[n]), &(b[n]));
	}
	else if(n == 8)
	{
		if(!zero)
		{ bn_mul_comba8(&(t[n2]), t, &(t[n])); }
		else
		{ memset(&(t[n2]), 0, 16 * sizeof(BN_ULONG)); }

		bn_mul_comba8(r, a, b);
		bn_mul_comba8(&(r[n2]), &(a[n]), &(b[n]));
	}
	else
# endif /* BN_MUL_COMBA */
	{
		p = &(t[n2 * 2]);
		if(!zero)
		{ bn_mul_recursive(&(t[n2]), t, &(t[n]), n, p); }
		else
		{ memset(&(t[n2]), 0, n2 * sizeof(BN_ULONG)); }
		bn_mul_recursive(r, a, b, n, p);
		bn_mul_recursive(&(r[n2]), &(a[n]), &(b[n]), n, p);
	}
