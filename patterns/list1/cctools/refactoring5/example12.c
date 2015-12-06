#ifndef SQLITE_OMIT_VIRTUALTABLE
if( IsVirtual(pItem->pTab) ){
          rc = whereLoopAddVirtual(&sSubBuild, mExtra);
        }else
#endif
        {
          rc = whereLoopAddBtree(&sSubBuild, mExtra);
        }
