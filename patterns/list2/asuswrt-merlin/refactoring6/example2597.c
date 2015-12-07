if (dsp->fdct == fdct_ifast
#ifndef FAAN_POSTSCALE
                   || dsp->fdct == ff_faandct
#endif
                   ) {
            for(i=0;i<64;i++) {
                const int j= dsp->idct_permutation[i];
                /* 16 <= qscale * quant_matrix[i] <= 7905 */
                /* 19952             <= ff_aanscales[i] * qscale * quant_matrix[i]               <= 249205026 */
                /* (1 << 36) / 19952 >= (1 << 36) / (ff_aanscales[i] * qscale * quant_matrix[i]) >= (1<<36)/249205026 */
                /* 3444240           >= (1 << 36) / (ff_aanscales[i] * qscale * quant_matrix[i]) >= 275 */

                qmat[qscale][i] = (int)((UINT64_C(1) << (QMAT_SHIFT + 14)) /
                                (ff_aanscales[i] * qscale * quant_matrix[j]));
            }
        } else {
            for(i=0;i<64;i++) {
                const int j= dsp->idct_permutation[i];
                /* We can safely suppose that 16 <= quant_matrix[i] <= 255
                   So 16           <= qscale * quant_matrix[i]             <= 7905
                   so (1<<19) / 16 >= (1<<19) / (qscale * quant_matrix[i]) >= (1<<19) / 7905
                   so 32768        >= (1<<19) / (qscale * quant_matrix[i]) >= 67
                */
                qmat[qscale][i] = (int)((UINT64_C(1) << QMAT_SHIFT) / (qscale * quant_matrix[j]));
//                qmat  [qscale][i] = (1 << QMAT_SHIFT_MMX) / (qscale * quant_matrix[i]);
                qmat16[qscale][0][i] = (1 << QMAT_SHIFT_MMX) / (qscale * quant_matrix[j]);

                if(qmat16[qscale][0][i]==0 || qmat16[qscale][0][i]==128*256) qmat16[qscale][0][i]=128*256-1;
                qmat16[qscale][1][i]= ROUNDED_DIV(bias<<(16-QUANT_BIAS_SHIFT), qmat16[qscale][0][i]);
            }
        }
