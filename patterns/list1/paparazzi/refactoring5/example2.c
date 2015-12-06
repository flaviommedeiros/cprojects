#ifdef IR_MLX_ONE_TIME_CONFIG
if (sys_time.nb_sec > 4) {
#else
  if (sys_time.nb_sec > 1) {
#endif
    if (ir_mlx_status >= IR_MLX_IDLE) {
      /* start two byte case temperature */
      mlx_trans.buf[0] = MLX90614_TA;
      i2c_transceive(&MLX_I2C_DEV, &mlx_trans, MLX90614_ADDR, 1, 2);
      ir_mlx_status = IR_MLX_RD_CASE_TEMP;
      /* send serial number every 30 seconds */
      RunOnceEvery((8 * 30), DOWNLINK_SEND_MLX_SERIAL(DefaultChannel, DefaultDevice, &ir_mlx_id_01, &ir_mlx_id_23));
    } else if (ir_mlx_status == IR_MLX_UNINIT) {
      /* start two byte ID 0 */
      mlx_trans.buf[0] = MLX90614_ID_0;
      i2c_transceive(&MLX_I2C_DEV, &mlx_trans, MLX90614_ADDR, 1, 2);
      ir_mlx_status = IR_MLX_RD_ID_0;
    }
  }
#ifdef IR_MLX_ONE_TIME_CONFIG
  else if ((sys_time.nb_sec > 1) && (ir_mlx_status == IR_MLX_ADDR_CHANGE)) {
    /* erase address by writing zero to SMBus address register */
    ir_mlx_status = IR_MLX_ADDR_ERASE;
    mlx_trans.buf[0] = MLX90614_SADR;
    mlx_trans.buf[1] = 0;
    mlx_trans.buf[2] = 0;
    ir_mlx_crc(MLX90614_GENERAL_ADDR, mlx_trans.buf);
    i2c_transmit(&MLX_I2C_DEV, &mlx_trans, MLX90614_GENERAL_ADDR, 4);
  } else if ((sys_time.nb_sec > 2) && (ir_mlx_status == IR_MLX_ADDR_ERASE)) {
    /* set address by writing it to AMBus address register */
    ir_mlx_status = IR_MLX_ADDR_SET;
    mlx_trans.buf[0] = MLX90614_SADR;
    mlx_trans.buf[1] = MLX90614_ADDR >> 1;
    mlx_trans.buf[2] = 0;
    ir_mlx_crc(MLX90614_GENERAL_ADDR, mlx_trans.buf);
    i2c_transmit(&MLX_I2C_DEV, &mlx_trans, MLX90614_GENERAL_ADDR, 4);
  } else if ((sys_time.nb_sec > 3) && (ir_mlx_status == IR_MLX_ADDR_SET)) {
    ir_mlx_status = IR_MLX_UNINIT;
  }
#endif
}
