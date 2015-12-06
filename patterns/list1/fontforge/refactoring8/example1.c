static void GIOdispatch(GIOControl *gc, enum giofuncs gf) {
    unichar_t *temp, *pt, *tpt;
    int i;

    gc->gf = gf;

    if ( _GIO_stdfuncs.useragent == NULL )
	_GIO_stdfuncs.useragent = copy("someone@somewhere.com");

    temp = _GIO_translateURL(gc->path,gf);
    if ( temp!=NULL ) {
	if ( gc->origpath==NULL )
	    gc->origpath = gc->path;
	else
	    free(gc->path);
	gc->path = temp;
    }
    if ( gc->topath!=NULL ) {
	temp = _GIO_translateURL(gc->topath,gf);
	if ( temp!=NULL ) {
	    free(gc->topath);
	    gc->topath = temp;
	}
	if ( gf==gf_renamefile ) {
	    if (( pt = uc_strstr(gc->path,"://"))== NULL )
		pt = gc->path;
	    else {
		pt=u_strchr(pt+3,'/');
		if ( pt==NULL ) pt = gc->path+u_strlen(gc->path);
	    }
	    if (( tpt = uc_strstr(gc->topath,"://"))== NULL )
		tpt = gc->topath;
	    else {
		tpt=u_strchr(tpt+3,'/');
		if ( tpt==NULL ) tpt = gc->topath+u_strlen(gc->topath);
	    }
	    if ( tpt-gc->topath!=pt-gc->path ||
		    u_strnmatch(gc->path,gc->topath,pt-gc->path)!=0 ) {
		_GIO_reporterror(gc,EXDEV);
return;
	    }
	}
    }

    pt = uc_strstr(gc->path,"://");
    if ( pt!=NULL ) {
	for ( i=0; i<plen; ++i )
	    if ( u_strnmatch(protocols[i].proto,gc->path,pt-gc->path)==0 )
	break;
	if ( i>=plen && !AddProtocol(gc->path,pt-gc->path) ) {
	    gc->protocol_index = -2;
	    gc->return_code = 501;
	    gc->error = err501;
	    uc_strcpy(gc->status,"No support for browsing: ");
	    u_strncpy(gc->status+u_strlen(gc->status), gc->path, pt-gc->path );
	    gc->done = true;
	    (gc->receiveerror)(gc);
return;
	}
	gc->protocol_index = i;
	if ( !protocols[i].dothread )
	    (protocols[i].dispatcher)(gc);
	else {
#ifndef HAVE_PTHREAD_H
	    gc->return_code = 501;
	    gc->error = err501;
	    uc_strcpy(gc->status,"No support for protocol");
	    gc->done = true;
	    (gc->receiveerror)(gc);
return;
#else
	    static pthread_cond_t initcond = PTHREAD_COND_INITIALIZER;
	    static pthread_mutex_t initmutex = PTHREAD_MUTEX_INITIALIZER;
	    /* could put stuff here to queue functions if we get too many */
	    /*  threads, or perhaps even a thread pool */
	    uc_strcpy(gc->status,"Queued");
	    gc->threaddata = (struct gio_threaddata *) malloc(sizeof(struct gio_threaddata));
	    gc->threaddata->mutex = initmutex;
	    gc->threaddata->cond = initcond;
	    if ( _GIO_stdfuncs.gdraw_sync_thread!=NULL )
		(_GIO_stdfuncs.gdraw_sync_thread)(NULL,NULL,NULL);
	    pthread_create(&gc->threaddata->thread,NULL,
		    (ptread_startfunc_t *) (protocols[i].dispatcher), gc);
#endif
	}
    } else {
	gc->protocol_index = -1;
	_GIO_localDispatch(gc);
    }
}
