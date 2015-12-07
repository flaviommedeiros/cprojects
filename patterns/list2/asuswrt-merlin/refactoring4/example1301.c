#ifdef PRIOQ
if (!bcanputnext(q,mp->b_band))
#else
        if (!canputnext(q))
#endif /* PRIOQ */
	{
	    putbq(q, mp);
	    break;
	}
