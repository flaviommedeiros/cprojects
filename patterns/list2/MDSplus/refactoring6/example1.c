if (mxIsNumeric(Tarray)
#ifdef V4
	&& !mxIsChar(Tarray)
#endif
	) {
/* Check if scalar */
      if (len == 1) {
#ifdef DEBUG
	printf("converting scalar %d,%d\n", mxGetM(Tarray), mxGetN(Tarray));
#endif
	ndim = 0;
	ndimP = matdum;
      } else {			/* Treat Scalar */
#ifdef V4
	ndim = 2;
	matdum[0] = mxGetM(Tarray);
	matdum[1] = mxGetN(Tarray);
	ndimP = matdum;
/* Special case to reduce a matrix (3,1) or (1,3) to a vector */
	if (MIN(ndimP[0], ndimP[1]) == 1) {
	  matdum[0] = MAX(ndimP[0], ndimP[1]);
	  matdum[1] = 0;
	  ndim--;
	}
#else
/* Special case to reduce a matrix (3,1) or (1,3) to a vector */
	if (ndim == 2)
	  if (MIN(ndimP[0], ndimP[1]) == 1) {
	    matdum[0] = MAX(ndimP[0], ndimP[1]);
	    matdum[1] = 0;
	    ndimP = matdum;
	    ndim--;
	  }
#endif				/* end of V4 */
      }				/* End Treat Scalar */
#ifdef DEBUG
      printf("ndim %d, point %lx", ndim, ndimP);
      if (ndim > 1)
	printf("  vals %d %d", ndimP[0], ndimP[1]);
      printf("\n");
#endif

/* Find out what type the variable has */
#ifdef V4
#else				/* get class and data type from matlab */
      if (conv) {
/* if not a normal matlab variable and conv was specified, signal alarm */
	if (!mxIsClass(Tarray, "double"))
	  mexErrMsgTxt("mdsipmex: mdscvt specified but data was not double precision");
      } else if (mxIsClass(Tarray, "double")) {
	conv = -DTYPE_DOUBLE;
#ifdef DEBUG
	printf("Got type 'double'\n");
#endif
      } else if (mxIsClass(Tarray, "char")) {
	conv = -DTYPE_CHAR;
#ifdef DEBUG
	printf("Got type 'char'\n");
#endif
      } else if (mxIsClass(Tarray, "int8")) {
#ifdef DEBUG
	printf("Got type 'int8'\n");
#endif
	conv = -DTYPE_CHAR;
      } else if (mxIsClass(Tarray, "uint8")) {
	conv = -DTYPE_UCHAR;
#ifdef DEBUG
	printf("Got type 'uint8'\n");
#endif
      } else if (mxIsClass(Tarray, "int16")) {
	conv = -DTYPE_SHORT;
#ifdef DEBUG
	printf("Got type 'int16'\n");
#endif
      } else if (mxIsClass(Tarray, "uint16")) {
#ifdef DEBUG
	printf("Got type 'uint16'\n");
#endif
	conv = -DTYPE_USHORT;
      } else if (mxIsClass(Tarray, "int32")) {
#ifdef DEBUG
	printf("Got type 'int32'\n");
#endif
	conv = -DTYPE_LONG;
      } else if (mxIsClass(Tarray, "uint32")) {
#ifdef DEBUG
	printf("Got type 'uint32'\n");
#endif
	conv = -DTYPE_ULONG;
      } else
	mexErrMsgTxt("mdsipmex: Can not handle this matlab data type, YET!");
#endif				/* V4 mdscvt class */
      dptr = mxGetPr(Tarray);	/* pointer to original data */
      strptr = (char *)dptr;	/* default output value */
      alloc = 0;
      llen = len;
      switch (abs(conv)) {
      case DTYPE_UCHAR:
	alloc = sizeof(unsigned char);
	if (conv < 0)
	  break;
	ucptr = (unsigned char *)MatAlloc(len, alloc);
	strptr = (char *)ucptr;
	while (len--)
	  *ucptr++ = (unsigned char)*dptr++;
	break;
      case DTYPE_CHAR:
	alloc = sizeof(char);
	if (conv < 0)
	  break;
	cptr = (char *)MatAlloc(len, alloc);
	strptr = (char *)cptr;
	while (len--)
	  *cptr++ = (char)*dptr++;
	break;
      case DTYPE_USHORT:
	alloc = sizeof(unsigned short);
	if (conv < 0)
	  break;
	usptr = (unsigned short *)MatAlloc(len, alloc);
	strptr = (char *)usptr;
	while (len--)
	  *usptr++ = (unsigned short)*dptr++;
	break;
      case DTYPE_SHORT:
	alloc = sizeof(short);
	if (conv < 0)
	  break;
	sptr = (short *)MatAlloc(len, alloc);
	strptr = (char *)sptr;
	while (len--)
	  *sptr++ = (short)*dptr++;
	break;
#ifdef DTYPE_LONGLONG
      case DTYPE_ULONGLONG:
	alloc = sizeof(uint64_t);
	if (conv < 0)
	  break;
	uqptr = (uint64_t *) MatAlloc(len, alloc);
	strptr = (char *)uqptr;
	while (len--)
	  *uqptr++ = (uint64_t) * dptr++;
	break;
      case DTYPE_LONGLONG:
	alloc = sizeof(int64_t);
	if (conv < 0)
	  break;
	qptr = (int64_t *) MatAlloc(len, alloc);
	strptr = (char *)qptr;
	while (len--)
	  *qptr++ = (int64_t) * dptr++;
	break;
#endif
      case DTYPE_ULONG:
	alloc = sizeof(unsigned int);
	if (conv < 0)
	  break;
	uiptr = (unsigned int *)MatAlloc(len, alloc);
	strptr = (char *)uiptr;
	while (len--)
	  *uiptr++ = (unsigned int)*dptr++;
	break;
      case DTYPE_LONG:
	alloc = sizeof(int);
	if (conv < 0)
	  break;
	iptr = (int *)MatAlloc(len, alloc);
	strptr = (char *)iptr;
	while (len--)
	  *iptr++ = (int)*dptr++;
	break;
      case DTYPE_FLOAT:
	alloc = sizeof(float);
	if (conv < 0)
	  break;
	fptr = (float *)MatAlloc(len, alloc);
	strptr = (char *)fptr;
	while (len--)
	  *fptr++ = (float)*dptr++;
	break;
      case DTYPE_DOUBLE:
	alloc = sizeof(double);
	if (conv < 0)
	  break;
	strptr = (char *)dptr;
/* assume that this does not need conversion */
	break;
      default:
	alloc = sizeof(double);
	conv = DTYPE_DOUBLE;
	break;
      }
#ifdef DEBUG
      {
	int ii;
	for (ii = 0; ii < (llen * alloc); ii++)
	  printf("Byte(%d) = 0x%x\n", ii, strptr[ii]);
      }
#endif
      status = SendArg(sock, (unsigned char)(i - opt), (char)abs(conv), (char)(nrhs - opt)
		       , (short)alloc, (char)ndim, ndimP, strptr);
/* check to see if it points to the original data */
      if (dptr != mxGetPr(Tarray))
	mxFree((void *)strptr);	/* release the memory */

/*      status = SendArg(sock, (unsigned char)(i-opt), DTYPE_DOUBLE, (unsigned char)(nrhs-opt)
		       ,(short)sizeof(double), (char)ndim, ndimP, (char *)mxGetPr(Tarray));*/
    }
    /* End Treat numbers */
    /* text data */
    else if (mxIsChar(Tarray)
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
