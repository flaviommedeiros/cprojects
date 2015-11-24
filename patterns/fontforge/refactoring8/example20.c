static SplineFont *IsResourceInFile(char *filename,int flags,enum openflags openflags,
	SplineFont *into, EncMap *map) {
    FILE *f;
    char *spt, *pt;
    SplineFont *sf;
    char *temp=filename, *lparen;

    if (( pt=strrchr(filename,'/'))==NULL ) pt = filename;
    if ( (lparen = strchr(pt,'('))!=NULL && strchr(lparen,')')!=NULL ) {
	temp = copy(filename);
	temp[lparen-filename] = '\0';
    }
    f = fopen(temp,"rb");
    if ( temp!=filename ) free(temp);
    if ( f==NULL )
return( NULL );
    spt = strrchr(filename,'/');
    if ( spt==NULL ) spt = filename;
    pt = strrchr(spt,'.');
    if ( pt!=NULL && (pt[1]=='b' || pt[1]=='B') && (pt[2]=='i' || pt[2]=='I') &&
	    (pt[3]=='n' || pt[3]=='N') && (pt[4]=='\0' || pt[4]=='(') ) {
	if ( (sf = IsResourceInBinary(f,filename,flags,openflags,into,map))) {
	    fclose(f);
return( sf );
	}
    } else if ( pt!=NULL && (pt[1]=='h' || pt[1]=='H') && (pt[2]=='q' || pt[2]=='Q') &&
	    (pt[3]=='x' || pt[3]=='X') && (pt[4]=='\0' || pt[4]=='(')) {
	if ( (sf = IsResourceInHex(f,filename,flags,openflags,into,map))) {
	    fclose(f);
return( sf );
	}
    }

    sf = IsResourceFork(f,0,filename,flags,openflags,into,map);
    fclose(f);
#if __Mac
    if ( sf==NULL )
	sf = HasResourceFork(filename,flags,openflags,into,map);
#endif
return( sf );
}
