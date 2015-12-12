if( psObject->bMeasureIsUsed
            && (psObject->nSHPType == SHPT_POLYGONM
                || psObject->nSHPType == SHPT_ARCM
#ifndef DISABLE_MULTIPATCH_MEASURE            
                || psObject->nSHPType == SHPT_MULTIPATCH
#endif            
                || psObject->nSHPType == SHPT_POLYGONZ
                || psObject->nSHPType == SHPT_ARCZ) )
        {
            ByteCopy( &(psObject->dfMMin), pabyRec + nRecordSize, 8 );
            if( bBigEndian ) SwapWord( 8, pabyRec + nRecordSize );
            nRecordSize += 8;
            
            ByteCopy( &(psObject->dfMMax), pabyRec + nRecordSize, 8 );
            if( bBigEndian ) SwapWord( 8, pabyRec + nRecordSize );
            nRecordSize += 8;

            for( i = 0; i < psObject->nVertices; i++ )
            {
                ByteCopy( psObject->padfM + i, pabyRec + nRecordSize, 8 );
                if( bBigEndian ) SwapWord( 8, pabyRec + nRecordSize );
                nRecordSize += 8;
            }
        }
