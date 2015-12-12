#ifndef SQLITE_OMIT_VIRTUALTABLE
if( IsVirtual(pItem->pTab) ){
          rc = whereLoopAddVirtual(&sSubBuild);
          for(i=0; i<sCur.n; i++) sCur.a[i].prereq |= mExtra;
        }else
#endif
        {
          rc = whereLoopAddBtree(&sSubBuild, mExtra);
        }
