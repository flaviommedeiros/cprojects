if (mxIsChar(Tarray)
#ifdef V4
#else
	     || mxIsCell(Tarray)
#endif
	) {
      if (mxIsChar(Tarray)) {
#ifdef V4
	len = mxGetM(Tarray);	/* number of elements */
	lmax = mxGetN(Tarray);	/* length of each element */
	if (len == 1)
	  ndim = 0;
	else {
	  ndim = 1;		/* array of strings */
	  matdum[0] = len;	/* number of strings */
	  matdum[MAX_DIMS] = lmax;	/* SPECIAL.... copy w_length into last element */
	}
	strptr = (char *)MatAlloc((lmax * len + 1), sizeof(char));
	strptr[lmax * len] = '\0';
	mxGetString(Tarray, strptr, lmax * len + 1);	/* Get the data */
#else
	ndim--;			/* remove second array */
	lmax = ndimP[1];	/* length of each element */
	*matdum = *ndimP;	/* first element gives size */
	for (j = 1; j < ndim; j++)
	  matdum[j] = ndimP[j + 1];	/* copy the other dimensions */
	s2trptr = strptr = (char *)MatAlloc((len + 1), sizeof(char));
#ifdef TRY1
	c2ptr = cptr = (char *)MatAlloc((len + 1), sizeof(char));
	mxGetString(Tarray, cptr, len + 1);	/* Get the data */
	for (k = 0; k < len / lmax; k++)
	  for (j = 0, c2ptr = cptr + k; j < lmax; j++, c2ptr += len / lmax)
	    *s2trptr++ = *c2ptr;
/*	 printf("Enter with [%s]\n",cptr);
	 printf("Leave with [%s]\n",strptr);*/
	mxFree((void *)cptr);	/* release the memory */
#else				/* TRY1 */
#ifndef TRY2
/* use Matlab To permutate */
	inAr[0] = (mxArray *) Tarray;	/* the data (cast eliminates compile error) */
	inAr[1] = mxCreateDoubleMatrix(ndim + 1, 1, mxREAL);	/* for the dimensions */
	dptr = mxGetPr(inAr[1]);	/* pointer to data */
/*	 printf("Ndim [%d] [%d] [%d] [%d]\n",ndim,ndimP[0],ndimP[1],ndimP[2]);*/
	*dptr++ = 2;		/* last index */
	for (j = 0; j <= ndim; j++) {
	  *dptr++ = j + 1;
	  if (!j)
	    j++;		/* skip the 2 */
	}
	mexCallMATLAB(1, outAr, 2, inAr, "permute");
	mxGetString(outAr[0], strptr, len + 1);	/* Get the data */
/* clear the matricies */
	mxDestroyArray(outAr[0]);
	mxDestroyArray(inAr[1]);
#else				/* TRY2 */
	ndim = 0;
	lmax = len;
	mxGetString(Tarray, strptr, len + 1);	/* Get the data */
#endif				/* TRY2 */
#endif				/* TRY1 */
#endif				/* V4 */
      }
#ifdef V4
#else
      else if (mxIsCell(Tarray)) {
	lmax = 0;		/* find max length of a cell */
	for (j = len; j--;) {
	  if (!mxIsChar(mxGetCell(Tarray, j)) || mxGetM(mxGetCell(Tarray, j)) > 1)
	    mexErrMsgTxt("mdsipmex: Cell array can only contain 1D character Arrays");
	  k = mxGetN(mxGetCell(Tarray, j));
	  if (k > lmax)
	    lmax = k;
	}
/* Allow room for all data and extra space for 0 at the end */
	cptr = strptr = (char *)MatAlloc(lmax * len + 1, sizeof(char));
	memset(strptr, ' ', lmax * len);	/* fill with spaces */
	for (j = 0; j < len; j++) {
	  mxGetString(mxGetCell(Tarray, j), cptr, lmax + 1);
/* put back the spaces */
	  cptr[strlen(cptr)] = ' ';
	  cptr += lmax;		/* point to next string */
	}
	for (j = 0; j < ndim; j++)
	  matdum[j] = ndimP[j];	/* copy dimensions of matrix */
	matdum[MAX_DIMS] = lmax;	/* SPECIAL.... copy w_length into last element */
      }
      /* End of CELL data */
      /* Remove a second dimension if 1 to reduce rank in remote server */
      if (ndim == 2 && matdum[ndim - 1] == 1)
	ndim--;
#endif				/* end V4 */
#ifdef DEBUG
      printf("Send String %d,%d,%d,%d,%d,%d,%d,[%s]\n", i - opt, nrhs - opt, DTYPE_CSTRING, lmax,
	     ndim, matdum[0], matdum[1], strptr);
#endif
      status = SendArg(sock, (unsigned char)(i - opt), DTYPE_CSTRING, (unsigned char)(nrhs - opt)
		       , (short)lmax, (char)ndim, matdum, strptr);
      mxFree((void *)strptr);	/* release the memory */
    }				/* end of text data */
#ifdef V4
#else
    else if (mxIsComplex(Tarray))
      mexErrMsgTxt("mdsipmex: Imaginary numbers not wanted");
#endif
    else
      mexErrMsgTxt("mdsipmex: Untreated data type encountered");
