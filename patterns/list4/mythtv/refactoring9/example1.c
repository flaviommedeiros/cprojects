static int64_t calculate_mode_score(CinepakEncContext *s, int h, strip_info *info, int report, int *training_set_v1_shrunk, int *training_set_v4_shrunk
#ifdef CINEPAK_REPORT_SERR
, int64_t *serr
#endif
)
{
    //score = FF_LAMBDA_SCALE * error + lambda * bits
    int x;
    int entry_size = s->pix_fmt == AV_PIX_FMT_RGB24 ? 6 : 4;
    int mb_count = s->w * h / MB_AREA;
    mb_info *mb;
    int64_t score1, score2, score3;
    int64_t ret = s->lambda * ((info->v1_size ? CHUNK_HEADER_SIZE + info->v1_size * entry_size : 0) +
                   (info->v4_size ? CHUNK_HEADER_SIZE + info->v4_size * entry_size : 0) +
                   CHUNK_HEADER_SIZE) << 3;

    //av_log(s->avctx, AV_LOG_INFO, "sizes %3i %3i -> %9"PRId64" score mb_count %i", info->v1_size, info->v4_size, ret, mb_count);

#ifdef CINEPAK_REPORT_SERR
    *serr = 0;
#endif

    switch(info->mode) {
    case MODE_V1_ONLY:
        //one byte per MB
        ret += s->lambda * 8 * mb_count;

// while calculating we assume all blocks are ENC_V1
        for(x = 0; x < mb_count; x++) {
            mb = &s->mb[x];
            ret += FF_LAMBDA_SCALE * mb->v1_error;
#ifdef CINEPAK_REPORT_SERR
            *serr += mb->v1_error;
#endif
// this function is never called for report in MODE_V1_ONLY
//            if(!report)
            mb->best_encoding = ENC_V1;
        }

        break;
    case MODE_V1_V4:
        //9 or 33 bits per MB
        if(report) {
// no moves between the corresponding training sets are allowed
            *training_set_v1_shrunk = *training_set_v4_shrunk = 0;
            for(x = 0; x < mb_count; x++) {
                int mberr;
                mb = &s->mb[x];
                if(mb->best_encoding == ENC_V1)
                    score1 = s->lambda * 9  + FF_LAMBDA_SCALE * (mberr=mb->v1_error);
                else
                    score1 = s->lambda * 33 + FF_LAMBDA_SCALE * (mberr=mb->v4_error);
                ret += score1;
#ifdef CINEPAK_REPORT_SERR
                *serr += mberr;
#endif
            }
        } else { // find best mode per block
            for(x = 0; x < mb_count; x++) {
                mb = &s->mb[x];
                score1 = s->lambda * 9  + FF_LAMBDA_SCALE * mb->v1_error;
                score2 = s->lambda * 33 + FF_LAMBDA_SCALE * mb->v4_error;

                if(score1 <= score2) {
                    ret += score1;
#ifdef CINEPAK_REPORT_SERR
                    *serr += mb->v1_error;
#endif
                    mb->best_encoding = ENC_V1;
                } else {
                    ret += score2;
#ifdef CINEPAK_REPORT_SERR
                    *serr += mb->v4_error;
#endif
                    mb->best_encoding = ENC_V4;
                }
            }
        }

        break;
    case MODE_MC:
        //1, 10 or 34 bits per MB
        if(report) {
            int v1_shrunk = 0, v4_shrunk = 0;
            for(x = 0; x < mb_count; x++) {
                mb = &s->mb[x];
// it is OK to move blocks to ENC_SKIP here
// but not to any codebook encoding!
                score1 = s->lambda * 1  + FF_LAMBDA_SCALE * mb->skip_error;
                if(mb->best_encoding == ENC_SKIP) {
                    ret += score1;
#ifdef CINEPAK_REPORT_SERR
                    *serr += mb->skip_error;
#endif
                } else if(mb->best_encoding == ENC_V1) {
                    if((score2=s->lambda * 10 + FF_LAMBDA_SCALE * mb->v1_error) >= score1) {
                        mb->best_encoding = ENC_SKIP;
                        ++v1_shrunk;
                        ret += score1;
#ifdef CINEPAK_REPORT_SERR
                        *serr += mb->skip_error;
#endif
                    } else {
                        ret += score2;
#ifdef CINEPAK_REPORT_SERR
                        *serr += mb->v1_error;
#endif
                    }
                } else {
                    if((score3=s->lambda * 34 + FF_LAMBDA_SCALE * mb->v4_error) >= score1) {
                        mb->best_encoding = ENC_SKIP;
                        ++v4_shrunk;
                        ret += score1;
#ifdef CINEPAK_REPORT_SERR
                        *serr += mb->skip_error;
#endif
                    } else {
                        ret += score3;
#ifdef CINEPAK_REPORT_SERR
                        *serr += mb->v4_error;
#endif
                    }
                }
            }
            *training_set_v1_shrunk = v1_shrunk;
            *training_set_v4_shrunk = v4_shrunk;
        } else { // find best mode per block
            for(x = 0; x < mb_count; x++) {
                mb = &s->mb[x];
                score1 = s->lambda * 1  + FF_LAMBDA_SCALE * mb->skip_error;
                score2 = s->lambda * 10 + FF_LAMBDA_SCALE * mb->v1_error;
                score3 = s->lambda * 34 + FF_LAMBDA_SCALE * mb->v4_error;

                if(score1 <= score2 && score1 <= score3) {
                    ret += score1;
#ifdef CINEPAK_REPORT_SERR
                    *serr += mb->skip_error;
#endif
                    mb->best_encoding = ENC_SKIP;
                } else if(score2 <= score3) {
                    ret += score2;
#ifdef CINEPAK_REPORT_SERR
                    *serr += mb->v1_error;
#endif
                    mb->best_encoding = ENC_V1;
                } else {
                    ret += score3;
#ifdef CINEPAK_REPORT_SERR
                    *serr += mb->v4_error;
#endif
                    mb->best_encoding = ENC_V4;
                }
            }
        }

        break;
    }

    return ret;
}
