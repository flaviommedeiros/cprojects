if ( bOutType == OUT_TN && !bNonTautIsIdenticalToTaut /* added 2004-10-04 Fix16 */
#ifdef OLD_ITEM_DISCOVERY
                            && bTautomeric && bNonTautomeric
#endif
                            && INChI_SegmentAction( sDifSegs[DIFL_F][DIFS_f_FORMULA] )
                       /* special case: removed isolated H(+): */
                       /* || iCurTautMode == TAUT_YES && num_comp[TAUT_YES] < num_comp[TAUT_NON] &&
                             0 < num_comp[TAUT_NON]*/
       )
    {
        /* add the second (non-tautomeric) output */
        bOutType     = OUT_NONTAUT;    /* pick up only non-tautomeric representation of tautomeric */
        iCurTautMode = TAUT_NON;
        pINChISort    = pINChISortTautAndNonTaut[TAUT_NON];
        bSecondNonTautPass = 1;
        nCurINChISegment   = DIFL_F;
        num_components = num_comp[iCurTautMode]; /* number of components could change due to removal of isolated H(+) from tautomeric */
        bFhTag = IL_FIXH;
        szGetTag( IdentLbl, nTag,  bTag1 = bFhTag, szTag1, &bAlways );
        if ( bXml )
        {
            /* open non-tautomeric */
            str_LineStart( szTag1, NULL, 0, pStr, ind );
            inchi_ios_print( output_file, "%s\n", pStr );
            ind += inc;
        }
        /***** constitution non-taut: dot-disconnected Hill formulas: <formula> -- only if different */
        szGetTag( IdentLbl, nTag,  bTag1 = IL_FMLF | bFhTag, szTag1, &bAlways );
        tot_len = str_LineStart( szTag1, NULL, 0, pStr, ind );
        nSegmAction = INChI_SegmentAction( sDifSegs[nCurINChISegment][DIFS_f_FORMULA] );
        if ( INCHI_SEGM_FILL == nSegmAction )
        {
            tot_len2 = str_HillFormula2(pINChISort, pINChISort2, pStr, nStrLen, tot_len,
                                      &bOverflow, bOutType, num_components, bUseMulipliers);
            bNonTautNonIsoIdentifierNotEmpty += bSecondNonTautPass;
        }
        else
        {
            tot_len2 = tot_len;
        }
        tot_len = tot_len2;
        if ( str_LineEnd( szTag1, tot_len, nStrLen, &bOverflow, pStr, bXml? 0 : -nSegmAction, bPlainTextTags ) )
            goto exit_function;
        inchi_ios_print( output_file, "%s%s", pStr, pLF );

        nSegmAction = INChI_SegmentAction( sDifSegs[nCurINChISegment][DIFS_h_H_ATOMS] );
        if ( INCHI_SEGM_FILL == nSegmAction )
        {
            szGetTag( IdentLbl, nTag,  bTag1 = IL_HFIX | bFhTag, szTag1, &bAlways );
            tot_len = str_LineStart( szTag1, NULL, 0, pStr, ind ); /* open H-fixed */
            /* output the second non-tautomeric item: fixed H -- do not output in xml if empty */
            tot_len2 = str_FixedH_atoms(pINChISort, pStr, nStrLen, tot_len,
                                       &bOverflow, bOutType, ATOM_MODE, num_components, bUseMulipliers);
            tot_len = tot_len2;
            if ( str_LineEnd( szTag1, tot_len, nStrLen, &bOverflow, pStr, bXml? 0 : -nSegmAction, bPlainTextTags ) )
                goto exit_function;
            inchi_ios_print( output_file, "%s%s", pStr, pLF );
            bNonTautNonIsoIdentifierNotEmpty += bSecondNonTautPass;
        }
        goto repeat_INChI_output;
    }
    else
    {
        if ( bOutType == OUT_NONTAUT && bOutputType == OUT_TN && bSecondNonTautPass /* && bTautomeric && bNonTautomeric*/ )
        {
            /* the second (non-taut) output has been done; restore variables */
            bOutType           = OUT_TN;
            iCurTautMode       = TAUT_YES;
            pINChISort         = pINChISortTautAndNonTaut[TAUT_YES];
            bSecondNonTautPass = 0;
            num_components     = num_comp[iCurTautMode];
            if ( !bNonTautNonIsoIdentifierNotEmpty )
            {
                /* Fixed-H layer is empty in the Identifier */
                *pSortPrintINChIFlags |= (INCHI_BAS == iINChI)? FLAG_SORT_PRINT_NO_NFIX_H_BAS :
                                                            FLAG_SORT_PRINT_NO_NFIX_H_REC;
            }
            if ( !bNonTautIsoIdentifierNotEmpty )
            {
                /* Fixed-H layer is empty in the Identifier */
                *pSortPrintINChIFlags |= (INCHI_BAS == iINChI)? FLAG_SORT_PRINT_NO_IFIX_H_BAS :
                                                                FLAG_SORT_PRINT_NO_IFIX_H_REC;
            }
            if ( bXml )
            {
                /*  close non-tautomeric */
                ind -= inc;
                szGetTag( IdentLbl, nTag,  bTag1 = bFhTag, szTag1, &bAlways );
                if ( str_LineEnd( szTag1, 0, nStrLen, &bOverflow, pStr, ind, bPlainTextTags ) )
                    goto exit_function;
                inchi_ios_print( output_file, "%s", pStr );
            }
            bFhTag             = 0;
        }
    }
