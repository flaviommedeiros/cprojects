switch (bitdepth)
  {
#ifndef MNG_NO_1_2_4BIT_SUPPORT
    case 1:
    {
      png_imgtype imgtype[]={png_g1,png_none,png_none,png_idx1};
      ret=imgtype[colortype];
      break;
    }
    case 2:
    {
      png_imgtype imgtype[]={png_g2,png_none,png_none,png_idx2};
      ret=imgtype[colortype];
      break;
    }
    case 4:
    {
      png_imgtype imgtype[]={png_g4,png_none,png_none,png_idx4};
      ret=imgtype[colortype];
      break;
    }
#endif
    case 8:
    {
      png_imgtype imgtype[]={png_g8,png_none,png_rgb8,png_idx8,png_ga8,
          png_none,png_rgba8};
      ret=imgtype[colortype];
      break;
    }
#ifndef MNG_NO_16BIT_SUPPORT
    case 16:
    {
      png_imgtype imgtype[]={png_g16,png_none,png_rgb16,png_none,png_ga16,
          png_none,png_rgba16};
      ret=imgtype[colortype];
      break;
    }
#endif
    default:
      ret=png_none;
      break;
  }
