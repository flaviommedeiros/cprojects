#if 1
if (nt->lwn > 0)
		{
		num=nt->lwn;
		nt->lwn=0;
		}
	else
		{
		RAND_pseudo_bytes(&n,1);
		num=(n&7);
		}
