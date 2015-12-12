static void mpeg_motion(MpegEncContext *s,
                        uint8_t *dest_y, uint8_t *dest_cb, uint8_t *dest_cr,
                        int field_select, uint8_t **ref_picture,
                        op_pixels_func (*pix_op)[4],
                        int motion_x, int motion_y, int h, int mb_y)
{
#if !CONFIG_SMALL
    if (s->out_format == FMT_MPEG1)
        mpeg_motion_internal(s, dest_y, dest_cb, dest_cr, 0, 0,
                             field_select, ref_picture, pix_op,
                             motion_x, motion_y, h, 1, mb_y);
    else
#endif
        mpeg_motion_internal(s, dest_y, dest_cb, dest_cr, 0, 0,
                             field_select, ref_picture, pix_op,
                             motion_x, motion_y, h, 0, mb_y);
}
