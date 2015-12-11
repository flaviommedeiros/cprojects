switch(_req){
  case TH_DECCTL_GET_PPLEVEL_MAX:{
    if(_dec==NULL||_buf==NULL)return TH_EFAULT;
    if(_buf_sz!=sizeof(int))return TH_EINVAL;
    (*(int *)_buf)=OC_PP_LEVEL_MAX;
    return 0;
  }break;
  case TH_DECCTL_SET_PPLEVEL:{
    int pp_level;
    if(_dec==NULL||_buf==NULL)return TH_EFAULT;
    if(_buf_sz!=sizeof(int))return TH_EINVAL;
    pp_level=*(int *)_buf;
    if(pp_level<0||pp_level>OC_PP_LEVEL_MAX)return TH_EINVAL;
    _dec->pp_level=pp_level;
    return 0;
  }break;
  case TH_DECCTL_SET_GRANPOS:{
    ogg_int64_t granpos;
    if(_dec==NULL||_buf==NULL)return TH_EFAULT;
    if(_buf_sz!=sizeof(ogg_int64_t))return TH_EINVAL;
    granpos=*(ogg_int64_t *)_buf;
    if(granpos<0)return TH_EINVAL;
    _dec->state.granpos=granpos;
    _dec->state.keyframe_num=(granpos>>_dec->state.info.keyframe_granule_shift)
     -_dec->state.granpos_bias;
    _dec->state.curframe_num=_dec->state.keyframe_num
     +(granpos&(1<<_dec->state.info.keyframe_granule_shift)-1);
    return 0;
  }break;
  case TH_DECCTL_SET_STRIPE_CB:{
    th_stripe_callback *cb;
    if(_dec==NULL||_buf==NULL)return TH_EFAULT;
    if(_buf_sz!=sizeof(th_stripe_callback))return TH_EINVAL;
    cb=(th_stripe_callback *)_buf;
    _dec->stripe_cb.ctx=cb->ctx;
    _dec->stripe_cb.stripe_decoded=cb->stripe_decoded;
    return 0;
  }break;
#ifdef HAVE_CAIRO
  case TH_DECCTL_SET_TELEMETRY_MBMODE:{
    if(_dec==NULL||_buf==NULL)return TH_EFAULT;
    if(_buf_sz!=sizeof(int))return TH_EINVAL;
    _dec->telemetry=1;
    _dec->telemetry_mbmode=*(int *)_buf;
    return 0;
  }break;
  case TH_DECCTL_SET_TELEMETRY_MV:{
    if(_dec==NULL||_buf==NULL)return TH_EFAULT;
    if(_buf_sz!=sizeof(int))return TH_EINVAL;
    _dec->telemetry=1;
    _dec->telemetry_mv=*(int *)_buf;
    return 0;
  }break;
  case TH_DECCTL_SET_TELEMETRY_QI:{
    if(_dec==NULL||_buf==NULL)return TH_EFAULT;
    if(_buf_sz!=sizeof(int))return TH_EINVAL;
    _dec->telemetry=1;
    _dec->telemetry_qi=*(int *)_buf;
    return 0;
  }break;
  case TH_DECCTL_SET_TELEMETRY_BITS:{
    if(_dec==NULL||_buf==NULL)return TH_EFAULT;
    if(_buf_sz!=sizeof(int))return TH_EINVAL;
    _dec->telemetry=1;
    _dec->telemetry_bits=*(int *)_buf;
    return 0;
  }break;
#endif
  default:return TH_EIMPL;
  }
