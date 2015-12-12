void ff_mpv_motion(MpegEncContext *s,
                   uint8_t *dest_y, uint8_t *dest_cb,
                   uint8_t *dest_cr, int dir,
                   uint8_t **ref_picture,
                   op_pixels_func (*pix_op)[4],
                   qpel_mc_func (*qpix_op)[16])
{
#if !CONFIG_SMALL
    if (s->out_format == FMT_MPEG1)
        mpv_motion_internal(s, dest_y, dest_cb, dest_cr, dir,
                            ref_picture, pix_op, qpix_op, 1);
    else
#endif
        mpv_motion_internal(s, dest_y, dest_cb, dest_cr, dir,
                            ref_picture, pix_op, qpix_op, 0);
}
