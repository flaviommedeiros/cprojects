static int am656in_feopen(struct tvin_frontend_s *fe, enum tvin_port_e port)
{
	struct am656in_dev_s *am656_devp = container_of(fe, am656in_dev_t, frontend);
	struct vdin_parm_s *parm = fe->private_data;
	if((port < TVIN_PORT_BT656)||(port > TVIN_PORT_CAMERA)){
		printk("[bt656..]%s:invaild port %d.\n",__func__, port);
		return -1;
	}
	if( TVIN_PORT_CAMERA == port ){
		am656_devp->skip_vdin_frame_count = parm->skip_count;
	}
	/*copy the param from vdin to bt656*/
	if(!memcpy(&am656_devp->para, parm, sizeof(vdin_parm_t))){
		printk("[bt656..]%s memcpy error.\n",__func__);
		return -1;
	}
	/*avoidint the param port is't equal with port*/
	am656_devp->para.port = port;
        printk("[bt656..] %s color format %s,hsync phase %u,vsync phase %u,"\
                "frame rate %u,hs_bp %u,vs_bp %u.\n", __func__,
                tvin_color_fmt_str(parm->cfmt),parm->hsync_phase,
                parm->vsync_phase,parm->frame_rate,parm->hs_bp,parm->vs_bp);
	#ifdef CONFIG_ARCH_MESON6
	switch_mod_gate_by_name("bt656", 1);
	#endif
	return 0;

}
