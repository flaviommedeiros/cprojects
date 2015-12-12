double const_values[] = {
        M_PI,
        M_E,
        rce->i_tex_bits * rce->qscale,
        rce->p_tex_bits * rce->qscale,
        (rce->i_tex_bits + rce->p_tex_bits) * (double)rce->qscale,
        rce->mv_bits / mb_num,
        rce->pict_type == AV_PICTURE_TYPE_B ? (rce->f_code + rce->b_code) * 0.5 : rce->f_code,
        rce->i_count / mb_num,
        rce->mc_mb_var_sum / mb_num,
        rce->mb_var_sum / mb_num,
        rce->pict_type == AV_PICTURE_TYPE_I,
        rce->pict_type == AV_PICTURE_TYPE_P,
        rce->pict_type == AV_PICTURE_TYPE_B,
        rcc->qscale_sum[pict_type] / (double)rcc->frame_count[pict_type],
        a->qcompress,
#if 0
        rcc->last_qscale_for[AV_PICTURE_TYPE_I],
        rcc->last_qscale_for[AV_PICTURE_TYPE_P],
        rcc->last_qscale_for[AV_PICTURE_TYPE_B],
        rcc->next_non_b_qscale,
#endif
        rcc->i_cplx_sum[AV_PICTURE_TYPE_I] / (double)rcc->frame_count[AV_PICTURE_TYPE_I],
        rcc->i_cplx_sum[AV_PICTURE_TYPE_P] / (double)rcc->frame_count[AV_PICTURE_TYPE_P],
        rcc->p_cplx_sum[AV_PICTURE_TYPE_P] / (double)rcc->frame_count[AV_PICTURE_TYPE_P],
        rcc->p_cplx_sum[AV_PICTURE_TYPE_B] / (double)rcc->frame_count[AV_PICTURE_TYPE_B],
        (rcc->i_cplx_sum[pict_type] + rcc->p_cplx_sum[pict_type]) / (double)rcc->frame_count[pict_type],
        0
    };
