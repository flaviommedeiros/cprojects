#ifndef SQLITE_OMIT_QUICKBALANCE
if( pPage->hasData
         && pPage->nOverflow==1
         && pPage->aOvfl[0].idx==pPage->nCell
         && pParent->pgno!=1
         && pParent->nCell==iIdx
        ){
          /* Call balance_quick() to create a new sibling of pPage on which
          ** to store the overflow cell. balance_quick() inserts a new cell
          ** into pParent, which may cause pParent overflow. If this
          ** happens, the next interation of the do-loop will balance pParent 
          ** use either balance_nonroot() or balance_deeper(). Until this
          ** happens, the overflow cell is stored in the aBalanceQuickSpace[]
          ** buffer. 
          **
          ** The purpose of the following assert() is to check that only a
          ** single call to balance_quick() is made for each call to this
          ** function. If this were not verified, a subtle bug involving reuse
          ** of the aBalanceQuickSpace[] might sneak in.
          */
          assert( (balance_quick_called++)==0 );
          rc = balance_quick(pParent, pPage, aBalanceQuickSpace);
        }else
#endif
        {
          /* In this case, call balance_nonroot() to redistribute cells
          ** between pPage and up to 2 of its sibling pages. This involves
          ** modifying the contents of pParent, which may cause pParent to
          ** become overfull or underfull. The next iteration of the do-loop
          ** will balance the parent page to correct this.
          ** 
          ** If the parent page becomes overfull, the overflow cell or cells
          ** are stored in the pSpace buffer allocated immediately below. 
          ** A subsequent iteration of the do-loop will deal with this by
          ** calling balance_nonroot() (balance_deeper() may be called first,
          ** but it doesn't deal with overflow cells - just moves them to a
          ** different page). Once this subsequent call to balance_nonroot() 
          ** has completed, it is safe to release the pSpace buffer used by
          ** the previous call, as the overflow cell data will have been 
          ** copied either into the body of a database page or into the new
          ** pSpace buffer passed to the latter call to balance_nonroot().
          */
          u8 *pSpace = sqlite3PageMalloc(pCur->pBt->pageSize);
          rc = balance_nonroot(pParent, iIdx, pSpace, iPage==1);
          if( pFree ){
            /* If pFree is not NULL, it points to the pSpace buffer used 
            ** by a previous call to balance_nonroot(). Its contents are
            ** now stored either on real database pages or within the 
            ** new pSpace buffer, so it may be safely freed here. */
            sqlite3PageFree(pFree);
          }

          /* The pSpace buffer will be freed after the next call to
          ** balance_nonroot(), or just before this function returns, whichever
          ** comes first. */
          pFree = pSpace;
        }
