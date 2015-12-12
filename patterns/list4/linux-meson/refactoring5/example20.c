#ifdef CONFIG_V4L_AMLOGIC_VIDEO
if (ppmgr_device.receiver != 0) {
		display_mode_change = VF_POOL_SIZE;
		canvas_width = ppmgr_device.canvas_width;
		canvas_height = ppmgr_device.canvas_height;
		if ((ppmgr_device.receiver_format == (GE2D_FORMAT_M24_NV21|GE2D_LITTLE_ENDIAN)) ||
					(ppmgr_device.receiver_format == (GE2D_FORMAT_M24_NV12|GE2D_LITTLE_ENDIAN))) {
            decbuf_size = (canvas_width * canvas_height * 12)>>3;
            decbuf_size = PAGE_ALIGN(decbuf_size);
			for (i = 0; i < VF_POOL_SIZE; i++) {
				canvas_config(PPMGR_CANVAS_INDEX + i,
					(ulong)(buf_start + i * decbuf_size),
					canvas_width, canvas_height,
					CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_LINEAR);
				canvas_config(PPMGR_CANVAS_INDEX + VF_POOL_SIZE + i,
					(ulong)(buf_start + i * decbuf_size + (canvas_width * canvas_height)),
					canvas_width, canvas_height/2,
					CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_LINEAR);
				ppmgr_canvas_tab[i] = (PPMGR_CANVAS_INDEX + i) | ((PPMGR_CANVAS_INDEX + i + VF_POOL_SIZE)<<8);
				//printk("canvas %x", buf_start + i * decbuf_size);
			}
		} else {
			int bpp = 4;
			if (ppmgr_device.receiver_format == (GE2D_FORMAT_S32_ABGR|GE2D_LITTLE_ENDIAN)) {
				bpp=4;
			}else if(ppmgr_device.receiver_format == (GE2D_FORMAT_S24_BGR|GE2D_LITTLE_ENDIAN)) {
				bpp=3;
			}else if(ppmgr_device.receiver_format == (GE2D_FORMAT_S16_RGB_565|GE2D_LITTLE_ENDIAN)) {
                bpp=2;
            }
			decbuf_size = canvas_width * canvas_height * bpp;
			//decbuf_size = PAGE_ALIGN(decbuf_size);
			for (i = 0; i < VF_POOL_SIZE; i++) {
				canvas_config(PPMGR_CANVAS_INDEX + i,
				 (ulong)(buf_start + i * decbuf_size),
					canvas_width * bpp, canvas_height,
					CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_LINEAR);
				ppmgr_canvas_tab[i] = PPMGR_CANVAS_INDEX + i;
				//printk("canvas %x", buf_start + i * decbuf_size);
			}
		}
	} else
#endif
    if(vout_mode == 0){
	    ppmgr_device.vinfo = get_current_vinfo();

	    if (ppmgr_device.disp_width == 0) {
	        if (ppmgr_device.vinfo->width <= 1280) {
	            ppmgr_device.disp_width = ppmgr_device.vinfo->width;
	        } else {
	            ppmgr_device.disp_width = 1280;
	        }
	    }

	    if (ppmgr_device.disp_height == 0) {
	        if (ppmgr_device.vinfo->height <= 736) {
	            ppmgr_device.disp_height = ppmgr_device.vinfo->height;
	        } else {
	            ppmgr_device.disp_height = 736;
	        }
	    }
            if (get_platform_type() == PLATFORM_MID_VERTICAL) {
                int DISP_SIZE = ppmgr_device.disp_width > ppmgr_device.disp_height ?
                        ppmgr_device.disp_width : ppmgr_device.disp_height;
                canvas_width = (DISP_SIZE + 0x1f) & ~0x1f;
                canvas_height = (DISP_SIZE + 0x1f) & ~0x1f;
            } else {
                canvas_width = (ppmgr_device.disp_width + 0x1f) & ~0x1f;
                canvas_height = (ppmgr_device.disp_height + 0x1f) & ~0x1f;
            }
	    decbuf_size = canvas_width * canvas_height * 3;

	    ppmgr_device.canvas_width = canvas_width;
	    ppmgr_device.canvas_height = canvas_height;
		for (i = 0; i < VF_POOL_SIZE; i++) {
			canvas_config(PPMGR_CANVAS_INDEX + i,
				(ulong)(buf_start + i * decbuf_size),
				canvas_width*3, canvas_height,
				CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_32X32);
		}
	    for(j = 0 ; j< ASS_POOL_SIZE;j++){
	        canvas_config(PPMGR_CANVAS_INDEX + VF_POOL_SIZE + j,
	                      (ulong)(buf_start + (VF_POOL_SIZE + j) * decbuf_size),
	                      canvas_width*3, canvas_height,
	                      CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_32X32);
	    }

	    ass_index =  PPMGR_CANVAS_INDEX + VF_POOL_SIZE ;   /*for rotate while pause status*/


	#ifdef CONFIG_POST_PROCESS_MANAGER_PPSCALER
	    backup_index = PPMGR_CANVAS_INDEX + VF_POOL_SIZE + 1;               /*for hdmi output*/
	#endif

	#ifdef CONFIG_POST_PROCESS_MANAGER_3D_PROCESS
	    // canvas mask buff
	    canvas_config(PPMGR_CANVAS_INDEX + VF_POOL_SIZE + ASS_POOL_SIZE,
	                      (ulong)(buf_start + (VF_POOL_SIZE + ASS_POOL_SIZE) * decbuf_size),
	                      canvas_width, canvas_height,
	                      CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_LINEAR);
	    Init3DBuff(PPMGR_CANVAS_INDEX + VF_POOL_SIZE + ASS_POOL_SIZE);
	#endif

	    //add a canvas to use as deinterlace buff for progressive mjpeg
	    canvas_config(PPMGR_DEINTERLACE_BUF_CANVAS,
	           (ulong)(buf_start + (VF_POOL_SIZE + ASS_POOL_SIZE) * decbuf_size + canvas_width * canvas_height * MASK_POOL_SIZE),
	           canvas_width, canvas_height,
	           CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_32X32);
	    canvas_config(PPMGR_DEINTERLACE_BUF_CANVAS + 1,
	           (ulong)(buf_start + (VF_POOL_SIZE + ASS_POOL_SIZE) * decbuf_size + canvas_width * canvas_height * MASK_POOL_SIZE + canvas_width * canvas_height),
	           canvas_width>>1, canvas_height>>1,
	           CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_32X32);
	    canvas_config(PPMGR_DEINTERLACE_BUF_CANVAS + 2,
	           (ulong)(buf_start + (VF_POOL_SIZE + ASS_POOL_SIZE) * decbuf_size + canvas_width * canvas_height * MASK_POOL_SIZE + (canvas_width * canvas_height*5)/4),
	           canvas_width>>1, canvas_height>>1,
	           CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_32X32);

	    canvas_config(PPMGR_DEINTERLACE_BUF_NV21_CANVAS,
	           (ulong)(buf_start + (VF_POOL_SIZE + ASS_POOL_SIZE) * decbuf_size + canvas_width * canvas_height * MASK_POOL_SIZE),
	           canvas_width*3, canvas_height,
	           CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_32X32);
   }else{

        canvas_width = 1920;
	    canvas_height = 1088;
	    decbuf_size = 0x600000;

	    if(decbuf_size*VF_POOL_SIZE>buf_size) {
	        amlog_level(LOG_LEVEL_HIGH, "size of ppmgr memory resource too small.\n");
	        return -1;
	    }

	    for (i = 0; i < VF_POOL_SIZE; i++){
	        canvas_config(PPMGR_CANVAS_INDEX+i/**3*/+0,
	                      (ulong)(buf_start + i * decbuf_size),
	                      canvas_width*3, canvas_height,
	                      CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_32X32);
	        canvas_config(PPMGR_DOUBLE_CANVAS_INDEX+ i,
	                      (ulong)(buf_start + (2*i) * decbuf_size/2),
	                      canvas_width*3, canvas_height/2,
	                      CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_32X32);
	        canvas_config(PPMGR_DOUBLE_CANVAS_INDEX+ 4+ i,
	                      (ulong)(buf_start + (2*i+1) * decbuf_size/2),
	                      canvas_width*3, canvas_height/2,
	                      CANVAS_ADDR_NOWRAP, CANVAS_BLKMODE_32X32);
	    }

   }
