if((temp_size = rd_strip(s, y, strip_height, isakeyframe, &last_pict, &pict, &scratch_pict, s->frame_buf + size + CVID_HEADER_SIZE, &score_temp
#ifdef CINEPAK_REPORT_SERR
, &serr_temp
#endif
)) < 0)
                return temp_size;
