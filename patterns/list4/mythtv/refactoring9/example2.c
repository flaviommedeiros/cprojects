static int rd_strip(CinepakEncContext *s, int y, int h, int keyframe, AVPicture *last_pict, AVPicture *pict, AVPicture *scratch_pict, unsigned char *buf, int64_t *best_score
#ifdef CINEPAK_REPORT_SERR
, int64_t *best_serr
#endif
)
{
    int64_t score = 0;
#ifdef CINEPAK_REPORT_SERR
    int64_t serr;
#endif
    int best_size = 0;
    strip_info info;
// for codebook optimization:
    int v1enough, v1_size, v4enough, v4_size;
    int new_v1_size, new_v4_size;
    int v1shrunk, v4shrunk;

    if(!keyframe)
        calculate_skip_errors(s, h, last_pict, pict, &info);

    //try some powers of 4 for the size of the codebooks
    //constraint the v4 codebook to be no bigger than v1 one,
    //(and no less than v1_size/4)
    //thus making v1 preferable and possibly losing small details? should be ok
#define SMALLEST_CODEBOOK 1
    for(v1enough = 0, v1_size = SMALLEST_CODEBOOK; v1_size <= CODEBOOK_MAX && !v1enough; v1_size <<= 2) {
        for(v4enough = 0, v4_size = 0; v4_size <= v1_size && !v4enough; v4_size = v4_size ? v4_size << 2 : v1_size >= SMALLEST_CODEBOOK << 2 ? v1_size >> 2 : SMALLEST_CODEBOOK) {
            //try all modes
            for(CinepakMode mode = 0; mode < MODE_COUNT; mode++) {
                //don't allow MODE_MC in intra frames
                if(keyframe && mode == MODE_MC)
                    continue;

                if(mode == MODE_V1_ONLY) {
                    info.v1_size = v1_size;
// the size may shrink even before optimizations if the input is short:
                    info.v1_size = quantize(s, h, pict, 1, &info, ENC_UNCERTAIN);
                    if(info.v1_size < v1_size)
// too few eligible blocks, no sense in trying bigger sizes
                        v1enough = 1;

                    info.v4_size = 0;
                } else { // mode != MODE_V1_ONLY
                    // if v4 codebook is empty then only allow V1-only mode
                    if(!v4_size)
                        continue;

                    if(mode == MODE_V1_V4) {
                        info.v4_size = v4_size;
                        info.v4_size = quantize(s, h, pict, 0, &info, ENC_UNCERTAIN);
                        if(info.v4_size < v4_size)
// too few eligible blocks, no sense in trying bigger sizes
                            v4enough = 1;
                    }
                }

                info.mode = mode;
// choose the best encoding per block, based on current experience
                score = calculate_mode_score(s, h, &info, 0,
                                             &v1shrunk, &v4shrunk
#ifdef CINEPAK_REPORT_SERR
, &serr
#endif
);

                if(mode != MODE_V1_ONLY){
                    int extra_iterations_limit = s->max_extra_cb_iterations;
// recompute the codebooks, omitting the extra blocks
// we assume we _may_ come here with more blocks to encode than before
                    info.v1_size = v1_size;
                    new_v1_size = quantize(s, h, pict, 1, &info, ENC_V1);
                    if(new_v1_size < info.v1_size){
                        //av_log(s->avctx, AV_LOG_INFO, "mode %i, %3i, %3i: cut v1 codebook to %i entries\n", mode, v1_size, v4_size, new_v1_size);
                        info.v1_size = new_v1_size;
                    }
// we assume we _may_ come here with more blocks to encode than before
                    info.v4_size = v4_size;
                    new_v4_size = quantize(s, h, pict, 0, &info, ENC_V4);
                    if(new_v4_size < info.v4_size) {
                        //av_log(s->avctx, AV_LOG_INFO, "mode %i, %3i, %3i: cut v4 codebook to %i entries at first iteration\n", mode, v1_size, v4_size, new_v4_size);
                        info.v4_size = new_v4_size;
                    }
// calculate the resulting score
// (do not move blocks to codebook encodings now, as some blocks may have
// got bigger errors despite a smaller training set - but we do not
// ever grow the training sets back)
                    for(;;) {
                        score = calculate_mode_score(s, h, &info, 1,
                                                     &v1shrunk, &v4shrunk
#ifdef CINEPAK_REPORT_SERR
, &serr
#endif
);
// do we have a reason to reiterate? if so, have we reached the limit?
                        if((!v1shrunk && !v4shrunk) || !extra_iterations_limit--) break;
// recompute the codebooks, omitting the extra blocks
                        if(v1shrunk) {
                            info.v1_size = v1_size;
                            new_v1_size = quantize(s, h, pict, 1, &info, ENC_V1);
                            if(new_v1_size < info.v1_size){
                                //av_log(s->avctx, AV_LOG_INFO, "mode %i, %3i, %3i: cut v1 codebook to %i entries\n", mode, v1_size, v4_size, new_v1_size);
                                info.v1_size = new_v1_size;
                            }
                        }
                        if(v4shrunk) {
                            info.v4_size = v4_size;
                            new_v4_size = quantize(s, h, pict, 0, &info, ENC_V4);
                            if(new_v4_size < info.v4_size) {
                                //av_log(s->avctx, AV_LOG_INFO, "mode %i, %3i, %3i: cut v4 codebook to %i entries\n", mode, v1_size, v4_size, new_v4_size);
                                info.v4_size = new_v4_size;
                            }
                        }
                    }
                }

                //av_log(s->avctx, AV_LOG_INFO, "%3i %3i score = %"PRId64"\n", v1_size, v4_size, score);

                if(best_size == 0 || score < *best_score) {

                    *best_score = score;
#ifdef CINEPAK_REPORT_SERR
                    *best_serr = serr;
#endif
                    best_size = encode_mode(s, h, scratch_pict, last_pict, &info, s->strip_buf + STRIP_HEADER_SIZE);

                    //av_log(s->avctx, AV_LOG_INFO, "mode %i, %3i, %3i: %18"PRId64" %i B", mode, info.v1_size, info.v4_size, score, best_size);
                    //av_log(s->avctx, AV_LOG_INFO, "\n");
#ifdef CINEPAK_REPORT_SERR
                    av_log(s->avctx, AV_LOG_INFO, "mode %i, %3i, %3i: %18"PRId64" %i B\n", mode, v1_size, v4_size, serr, best_size);
#endif

#ifdef CINEPAKENC_DEBUG
                    //save MB encoding choices
                    memcpy(s->best_mb, s->mb, mb_count*sizeof(mb_info));
#endif

                    //memcpy(strip_temp + STRIP_HEADER_SIZE, strip_temp, best_size);
                    write_strip_header(s, y, h, keyframe, s->strip_buf, best_size);

                }
            }
        }
    }

#ifdef CINEPAKENC_DEBUG
    //gather stats. this will only work properly of MAX_STRIPS == 1
    if(best_info.mode == MODE_V1_ONLY) {
        s->num_v1_mode++;
        s->num_v1_encs += s->w*h/MB_AREA;
    } else {
        if(best_info.mode == MODE_V1_V4)
            s->num_v4_mode++;
        else
            s->num_mc_mode++;

        int x;
        for(x = 0; x < s->w*h/MB_AREA; x++)
            if(s->best_mb[x].best_encoding == ENC_V1)
                s->num_v1_encs++;
            else if(s->best_mb[x].best_encoding == ENC_V4)
                s->num_v4_encs++;
            else
                s->num_skips++;
    }
#endif

    best_size += STRIP_HEADER_SIZE;
    memcpy(buf, s->strip_buf, best_size);

    return best_size;
}
