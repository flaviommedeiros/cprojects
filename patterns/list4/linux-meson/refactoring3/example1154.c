switch (dsi_cmd_req.data_type) {//analysis data_type
                case DT_GEN_SHORT_WR_0:
                case DT_GEN_SHORT_WR_1:
                case DT_GEN_SHORT_WR_2:
                    dsi_generic_write_short_packet(&dsi_cmd_req);
                    break;
                case DT_DCS_SHORT_WR_0:
                case DT_DCS_SHORT_WR_1:
                    dsi_dcs_write_short_packet(&dsi_cmd_req);
                    break;
                case DT_DCS_LONG_WR:
                case DT_GEN_LONG_WR:
                    dsi_write_long_packet(&dsi_cmd_req);
                    break;
                case DT_TURN_ON:
                    WRITE_LCD_REG_BITS(MIPI_DSI_TOP_CNTL, 1, 2, 1);
                    mdelay(20); //wait for vsync trigger
                    WRITE_LCD_REG_BITS(MIPI_DSI_TOP_CNTL, 0, 2, 1);
                    mdelay(20); //wait for vsync trigger
                    break;
                case DT_SHUT_DOWN:
                    WRITE_LCD_REG_BITS(MIPI_DSI_TOP_CNTL, 1, 2, 1);
                    mdelay(20); //wait for vsync trigger
                    break;
                case DT_SET_MAX_RET_PKT_SIZE:
                    dsi_set_max_return_pkt_size(&dsi_cmd_req);
                    break;
#ifdef DSI_CMD_READ_VALID
                case DT_GEN_RD_0:
                case DT_GEN_RD_1:
                case DT_GEN_RD_2:
                    dsi_cmd_req.req_ack = MIPI_DSI_DCS_REQ_ACK; //need BTA ack
                    dsi_cmd_req.pld_count = (dsi_cmd_req.pld_count > 2) ? 2 : dsi_cmd_req.pld_count;
                    n = dsi_generic_read_packet(&dsi_cmd_req, &rd_data[0]);
                    DPRINT("generic read data");
                    for (k=0; k<dsi_cmd_req.pld_count; k++) {
                        DPRINT(" 0x%02x", dsi_cmd_req.payload[k+2]);
                    }
                    DPRINT(":\n");
                    for (k=0; k<n; k++) {
                        DPRINT("0x%02x ", rd_data[k]);
                    }
                    DPRINT("\n");
                    break;
                case DT_DCS_RD_0:
                    dsi_cmd_req.req_ack = MIPI_DSI_DCS_REQ_ACK; //need BTA ack
                    n = dsi_dcs_read_packet(&dsi_cmd_req, &rd_data[0]);
                    DPRINT("dcs read data 0x%02x:\n", dsi_cmd_req.payload[2]);
                    for (k=0; k<n; k++) {
                        DPRINT("0x%02x ", rd_data[k]);
                    }
                    DPRINT("\n");
                    break;
#endif
                default:
                    DPRINT("[warning]dsi un-support data_type: 0x%02x\n", dsi_cmd_req.data_type);
                    break;
            }
