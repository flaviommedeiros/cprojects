static inline void vdin_set_color_matrix1(unsigned int offset, tvin_format_t *tvin_fmt_p, enum vdin_format_convert_e format_convert)
{
#if defined(VDIN_V1)
	//    unsigned int offset = devp->addr_offset;
	enum vdin_matrix_csc_e    matrix_csc = VDIN_MATRIX_NULL;
	struct vdin_matrix_lup_s *matrix_tbl;
	struct tvin_format_s *fmt_info = tvin_fmt_p;

	switch (format_convert)
	{
		case VDIN_MATRIX_XXX_YUV_BLACK:
			matrix_csc = VDIN_MATRIX_XXX_YUV601_BLACK;
			break;
		case VDIN_FORMAT_CONVERT_RGB_YUV422:
		case VDIN_FORMAT_CONVERT_RGB_NV12:
		case VDIN_FORMAT_CONVERT_RGB_NV21:
			matrix_csc = VDIN_MATRIX_RGBS_YUV601;
			break;
		case VDIN_FORMAT_CONVERT_BRG_YUV422:
			matrix_csc = VDIN_MATRIX_BRG_YUV601;
			break;
		case VDIN_FORMAT_CONVERT_GBR_YUV422:
			matrix_csc = VDIN_MATRIX_GBR_YUV601;
			break;
		case VDIN_FORMAT_CONVERT_RGB_YUV444:
			matrix_csc = VDIN_MATRIX_RGB_YUV601;
			break;
		case VDIN_FORMAT_CONVERT_YUV_RGB:
			if (
		              ((fmt_info->scan_mode == TVIN_SCAN_MODE_PROGRESSIVE) && (fmt_info->v_active >= 720)) || //  720p & above
		       	      ((fmt_info->scan_mode == TVIN_SCAN_MODE_INTERLACED)  && (fmt_info->v_active >= 540))    // 1080i & above
			   )
				matrix_csc = VDIN_MATRIX_YUV709_RGB;
			else
				matrix_csc = VDIN_MATRIX_YUV601_RGB;
			break;
		case VDIN_FORMAT_CONVERT_YUV_GBR:
			if (((fmt_info->scan_mode == TVIN_SCAN_MODE_PROGRESSIVE) && (fmt_info->v_active >= 720)) || //  720p & above
			    ((fmt_info->scan_mode == TVIN_SCAN_MODE_INTERLACED)  && (fmt_info->v_active >= 540))    // 1080i & above
			   )
				matrix_csc = VDIN_MATRIX_YUV709_GBR;
			else
				matrix_csc = VDIN_MATRIX_YUV601_GBR;
			break;
		case VDIN_FORMAT_CONVERT_YUV_BRG:
			if (((fmt_info->scan_mode == TVIN_SCAN_MODE_PROGRESSIVE) && (fmt_info->v_active >= 720)) || //  720p & above
			    ((fmt_info->scan_mode == TVIN_SCAN_MODE_INTERLACED)  && (fmt_info->v_active >= 540))    // 1080i & above
			   )
				matrix_csc = VDIN_MATRIX_YUV709_BRG;
			else
				matrix_csc = VDIN_MATRIX_YUV601_BRG;
			break;
		case VDIN_FORMAT_CONVERT_YUV_YUV422:
		case VDIN_FORMAT_CONVERT_YUV_YUV444:
		case VDIN_FORMAT_CONVERT_YUV_NV12:
		case VDIN_FORMAT_CONVERT_YUV_NV21:
			if (((fmt_info->scan_mode == TVIN_SCAN_MODE_PROGRESSIVE) && (fmt_info->v_active >= 720)) || //  720p & above
         		    ((fmt_info->scan_mode == TVIN_SCAN_MODE_INTERLACED)  && (fmt_info->v_active >= 540))    // 1080i & above
			   )
			{
				if (color_convert == 0)
					matrix_csc = VDIN_MATRIX_YUV709_YUV601;
				else if (color_convert == 1)
					matrix_csc = VDIN_MATRIX_YUV709_YUV601F;
				else if (color_convert == 2)
					matrix_csc = VDIN_MATRIX_YUV709_YUV709F;
				else if (color_convert == 3)
					matrix_csc = VDIN_MATRIX_YUV709F_YUV601;
				else if (color_convert == 4)
					matrix_csc = VDIN_MATRIX_YUV709F_YUV601F;
				else
					matrix_csc = VDIN_MATRIX_YUV709_YUV601;
			}
			break;
		default:
			matrix_csc = VDIN_MATRIX_NULL;
			break;
	}

	if (matrix_csc == VDIN_MATRIX_NULL)
	{
		WR_BITS(VDIN_MATRIX_CTRL, 0, VDIN_MATRIX1_EN_BIT, VDIN_MATRIX1_EN_WID);
	}
	else
	{
		matrix_tbl = &vdin_matrix_lup[matrix_csc - 1];
		/*select matrix1 post probe and postion(200,100)*/
		WR_BITS(VDIN_MATRIX_CTRL, 1, VDIN_PROBE_POST_BIT, VDIN_PROBE_POST_WID);
		WR_BITS(VDIN_MATRIX_CTRL, 1, VDIN_PROBE_SEL_BIT, VDIN_PROBE_SEL_WID);
		WR(VDIN_MATRIX_PROBE_POS, 0xc812);
		/*coefficient index select matrix1*/
		WR_BITS(VDIN_MATRIX_CTRL, 1, VDIN_MATRIX_COEF_INDEX_BIT, VDIN_MATRIX_COEF_INDEX_WID);
		WR(VDIN_MATRIX_PRE_OFFSET0_1,matrix_tbl->pre_offset0_1);
		WR(VDIN_MATRIX_PRE_OFFSET2, matrix_tbl->pre_offset2);
		WR(VDIN_MATRIX_COEF00_01, matrix_tbl->coef00_01);
		WR(VDIN_MATRIX_COEF02_10, matrix_tbl->coef02_10);
		WR(VDIN_MATRIX_COEF11_12, matrix_tbl->coef11_12);
		WR(VDIN_MATRIX_COEF20_21, matrix_tbl->coef20_21);
		WR(VDIN_MATRIX_COEF22, matrix_tbl->coef22);
		WR(VDIN_MATRIX_OFFSET0_1, matrix_tbl->post_offset0_1);
		WR(VDIN_MATRIX_OFFSET2, matrix_tbl->post_offset2);
                WR_BITS(VDIN_MATRIX_CTRL, 0, VDIN_MATRIX1_BYPASS_BIT, VDIN_MATRIX1_BYPASS_WID);
		WR_BITS(VDIN_MATRIX_CTRL, 1, VDIN_MATRIX1_EN_BIT, VDIN_MATRIX1_EN_WID);
	}
        #endif
}
