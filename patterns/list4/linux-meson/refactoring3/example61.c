switch (cmd)
    {
#if 0
        case PPMGR_IOC_CONFIG_FRAME:
            copy_from_user(&frame_info,argp,sizeof(frame_info_t));
            break;
#endif
        case PPMGR_IOC_GET_ANGLE:
            put_user(ppmgr_device.angle,(unsigned int *)argp);
            break;
        case PPMGR_IOC_SET_ANGLE:
            ret = _ppmgr_angle_write(args);
            break;
#ifdef CONFIG_POST_PROCESS_MANAGER_3D_PROCESS
        case PPMGR_IOC_ENABLE_PP:
            mode=(int)argp;
            platform_type_t plarform_type;
            plarform_type = get_platform_type();
            if( plarform_type == PLATFORM_TV){
            	set_ppmgr_status(mode);
            }else{
          	  set_ppmgr_3dmode(mode);
         	}
            break;
        case PPMGR_IOC_VIEW_MODE:
            mode=(int)argp;
            set_ppmgr_viewmode(mode);
            break;
        case PPMGR_IOC_HOR_VER_DOUBLE:
            flag = (int)argp;
            mode = get_ppmgr_3dmode();
            mode = (mode & (~PPMGR_3D_PROCESS_DOUBLE_TYPE))|((flag<<PPMGR_3D_PROCESS_DOUBLE_TYPE_SHIFT)&(PPMGR_3D_PROCESS_DOUBLE_TYPE));
            set_ppmgr_3dmode(mode);
            break;
        case PPMGR_IOC_SWITCHMODE:
            flag = (int)argp;
            mode = get_ppmgr_3dmode();
            if(flag)
                mode = mode & PPMGR_3D_PROCESS_SWITCH_FLAG ;
            else
                mode = mode & (~PPMGR_3D_PROCESS_SWITCH_FLAG);
            set_ppmgr_3dmode(mode);
            break;
        case PPMGR_IOC_3D_DIRECTION:
            flag = (int)argp;
            //mode = get_ppmgr_3dmode();
            //mode = (mode & (~PPMGR_3D_PROCESS_3D_ROTATE_DIRECTION_MASK))|((flag<<PPMGR_3D_PROCESS_3D_ROTATE_DIRECTION_VAULE_SHIFT)&(PPMGR_3D_PROCESS_3D_ROTATE_DIRECTION_MASK));
            //set_ppmgr_3dmode(mode);
            set_ppmgr_direction3d(flag);
            break;
        case PPMGR_IOC_3D_SCALE_DOWN:
            mode=(int)argp;
            set_ppmgr_scaledown(mode);
            break;
#endif
        default :
            return -ENOIOCTLCMD;

    }
