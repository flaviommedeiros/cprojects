pointer error(enum errorcode ec, ...)
#else
pointer error(va_alist)
va_dcl
#endif
{ 
  va_list args;
  pointer errhandler;
  register char *errstr;
  register int argc;
  register context *ctx;
  pointer msg;

#ifdef USE_STDARG
  va_start(args,ec);
#else
  enum errorcode ec;

  va_start(args);
  ec = va_arg(args, enum errorcode);
#endif

  ctx=euscontexts[thr_self()];

  /* error(errstr) must be error(E_USER,errstr) */
  if ((int)ec < E_END) errstr=errmsg[(int)ec];
  else {
      fprintf( stderr, "Internal warning: error: ec will be string.(%lx)\n",
	      (long)ec );
      errstr=(char *)ec;
  }

  /*fatal error?  allocation failed or stack overflow? */
  if ((unsigned int)ec<=E_FATAL) {
    fprintf(stderr,"%s fatal error: th=%d %s\n",progname,thr_self(),errstr);
    if (speval(FATALERROR) != NIL) {
	fprintf(stderr, "exiting\n"); exit(ec);}
    else throw(ctx,makeint(0),NIL);}

  /* get extra message */
    switch((unsigned int)ec) {
      case E_UNBOUND: case E_UNDEF: case E_NOCLASS: case E_PKGNAME:
      case E_NOOBJ: case E_NOOBJVAR: case E_NOPACKAGE: case E_NOMETHOD:
      case E_NOKEYPARAM: case E_READLABEL: case E_ILLCH: case E_NOCATCHER:
      case E_NOVARIABLE: case E_EXTSYMBOL: case E_SYMBOLCONFLICT:
      case E_USER:
	msg = va_arg(args,pointer);	break;
    }

  /* call user's error handler function */
  errhandler=ctx->errhandler;
  if (errhandler==NIL || errhandler==NULL)  errhandler=Spevalof(ERRHANDLER);
  Spevalof(QEVALHOOK)=NIL;	/* reset eval hook */
  if (errhandler!=NIL) {
    vpush(makeint((unsigned int)ec));
    vpush(makestring(errstr,strlen(errstr)));
    if (ctx->callfp) vpush(ctx->callfp->form); else vpush(NIL);
    switch((unsigned int)ec) {
      case E_UNBOUND: case E_UNDEF: case E_NOCLASS: case E_PKGNAME:
      case E_NOOBJ: case E_NOOBJVAR: case E_NOPACKAGE: case E_NOMETHOD:
      case E_NOKEYPARAM: case E_READLABEL: case E_ILLCH: case E_NOCATCHER:
      case E_NOVARIABLE: case E_EXTSYMBOL: case E_SYMBOLCONFLICT:
	vpush(msg); argc=4; break;
      case E_USER:
	vpush(makestring((char*)msg,strlen((char*)msg))); argc=4; break;
    default: argc=3; break;}
    ufuncall(ctx,errhandler,errhandler,(pointer)(ctx->vsp-argc),ctx->bindfp,argc);
    ctx->vsp-=argc;
    }

  /*default error handler*/
  flushstream(ERROUT);
  fprintf(stderr,"%s: ERROR th=%d %s ",progname,thr_self(),errstr);
  switch((int)ec) {
      case E_UNBOUND: case E_UNDEF: case E_NOCLASS: case E_PKGNAME:
      case E_NOOBJ: case E_NOOBJVAR: case E_NOPACKAGE: case E_NOMETHOD:
      case E_NOKEYPARAM: case E_READLABEL: case E_ILLCH: case E_NOCATCHER:
      case E_NOVARIABLE: case E_EXTSYMBOL: case E_SYMBOLCONFLICT:
	prinx(ctx,msg,ERROUT); flushstream(ERROUT); break;
    }
  if( ec == E_USER ) {
      fprintf( stderr,"%p",msg ); flushstream(ERROUT); }
  else if (ispointer(msg)) {prinx(ctx,msg,ERROUT); flushstream(ERROUT); }
  if (ctx->callfp) {
    fprintf(stderr," in ");
    prinx(ctx,ctx->callfp->form,ERROUT);
    flushstream(ERROUT);}
  /*enter break loop*/
  brkloop(ctx,"E: ");
  throw(ctx,makeint(0),T);	/*throw to toplevel*/
  }
