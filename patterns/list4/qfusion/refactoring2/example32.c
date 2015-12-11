#if !defined(OC_COLLECT_METRICS)
if(frame_type!=OC_INTRA_FRAME)
#endif
  {
    /*In retrospect, should we have skipped this block?*/
    oc_enc_frag_sub(_enc,data,src,dst,ystride);
    coded_ssd=coded_dc=0;
    if(borderi<0){
      for(pi=0;pi<64;pi++){
        coded_ssd+=data[pi]*data[pi];
        coded_dc+=data[pi];
      }
    }
    else{
      ogg_int64_t mask;
      mask=_enc->state.borders[borderi].mask;
      for(pi=0;pi<64;pi++,mask>>=1)if(mask&1){
        coded_ssd+=data[pi]*data[pi];
        coded_dc+=data[pi];
      }
    }
    /*Scale to match DCT domain.*/
    coded_ssd<<=4;
    /*We actually only want the AC contribution to the SSD.*/
    coded_ssd-=coded_dc*coded_dc>>2;
#if defined(OC_COLLECT_METRICS)
    _enc->frag_ssd[_fragi]=coded_ssd;
  }
