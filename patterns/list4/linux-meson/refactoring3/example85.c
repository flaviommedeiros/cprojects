switch (bconf->method) {
            case BL_CTL_GPIO:
                level = bconf->dim_min - ((level - bconf->level_min) * (bconf->dim_min - bconf->dim_max)) / (bconf->level_max - bconf->level_min);
#if (MESON_CPU_TYPE == MESON_CPU_TYPE_MESON6)
                aml_set_reg32_bits(P_LED_PWM_REG0, level, 0, 4);
#endif
                break;
            case BL_CTL_PWM_NEGATIVE:
            case BL_CTL_PWM_POSITIVE:
                level = (bconf->pwm_max - bconf->pwm_min) * (level - bconf->level_min) / (bconf->level_max - bconf->level_min) + bconf->pwm_min;
                if (bconf->method == BL_CTL_PWM_NEGATIVE) {
                    pwm_hi = bconf->pwm_cnt - level;
                    pwm_lo = level;
                }
                else {
                    pwm_hi = level;
                    pwm_lo = bconf->pwm_cnt - level;
                }
                switch (bconf->pwm_port) {
                    case BL_PWM_A:
                        aml_write_reg32(P_PWM_PWM_A, (pwm_hi << 16) | (pwm_lo));
                        break;
                    case BL_PWM_B:
                        aml_write_reg32(P_PWM_PWM_B, (pwm_hi << 16) | (pwm_lo));
                        break;
                    case BL_PWM_C:
                        aml_write_reg32(P_PWM_PWM_C, (pwm_hi << 16) | (pwm_lo));
                        break;
                    case BL_PWM_D:
                        aml_write_reg32(P_PWM_PWM_D, (pwm_hi << 16) | (pwm_lo));
                        break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                    case BL_PWM_E:
                        aml_write_reg32(P_PWM_PWM_E, (pwm_hi << 16) | (pwm_lo));
                        break;
                    case BL_PWM_F:
                        aml_write_reg32(P_PWM_PWM_F, (pwm_hi << 16) | (pwm_lo));
                        break;
#endif
                    default:
                        break;
                }
                break;
            case BL_CTL_PWM_COMBO:
                if (level >= bconf->combo_level_switch) {
                    //pre_set combo_low duty max
                    if (bconf->combo_low_method == BL_CTL_PWM_NEGATIVE) {
                        pwm_hi = bconf->combo_low_cnt - bconf->combo_low_duty_max;
                        pwm_lo = bconf->combo_low_duty_max;
                    }
                    else {
                        pwm_hi = bconf->combo_low_duty_max;
                        pwm_lo = bconf->combo_low_cnt - bconf->combo_low_duty_max;
                    }
                    switch (bconf->combo_low_port) {
                        case BL_PWM_A:
                            aml_write_reg32(P_PWM_PWM_A, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_B:
                            aml_write_reg32(P_PWM_PWM_B, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_C:
                            aml_write_reg32(P_PWM_PWM_C, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_D:
                            aml_write_reg32(P_PWM_PWM_D, (pwm_hi << 16) | (pwm_lo));
                            break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                        case BL_PWM_E:
                            aml_write_reg32(P_PWM_PWM_E, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_F:
                            aml_write_reg32(P_PWM_PWM_F, (pwm_hi << 16) | (pwm_lo));
                            break;
#endif
                        default:
                            break;
                    }

                    //set combo_high duty
                    level = (bconf->combo_high_duty_max - bconf->combo_high_duty_min) * (level - bconf->combo_level_switch) / (bconf->level_max - bconf->combo_level_switch) + bconf->combo_high_duty_min;
                    if (bconf->combo_high_method == BL_CTL_PWM_NEGATIVE) {
                        pwm_hi = bconf->combo_high_cnt - level;
                        pwm_lo = level;
                    }
                    else {
                        pwm_hi = level;
                        pwm_lo = bconf->combo_high_cnt - level;
                    }
                    switch (bconf->combo_high_port) {
                        case BL_PWM_A:
                            aml_write_reg32(P_PWM_PWM_A, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_B:
                            aml_write_reg32(P_PWM_PWM_B, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_C:
                            aml_write_reg32(P_PWM_PWM_C, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_D:
                            aml_write_reg32(P_PWM_PWM_D, (pwm_hi << 16) | (pwm_lo));
                            break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                        case BL_PWM_E:
                            aml_write_reg32(P_PWM_PWM_E, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_F:
                            aml_write_reg32(P_PWM_PWM_F, (pwm_hi << 16) | (pwm_lo));
                            break;
#endif
                        default:
                            break;
                    }
                }
                else {
                    //pre_set combo_high duty min
                    if (bconf->combo_high_method == BL_CTL_PWM_NEGATIVE) {
                        pwm_hi = bconf->combo_high_cnt - bconf->combo_high_duty_min;
                        pwm_lo = bconf->combo_high_duty_min;
                    }
                    else {
                        pwm_hi = bconf->combo_high_duty_min;;
                        pwm_lo = bconf->combo_high_cnt - bconf->combo_high_duty_min;
                    }
                    switch (bconf->combo_high_port) {
                        case BL_PWM_A:
                            aml_write_reg32(P_PWM_PWM_A, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_B:
                            aml_write_reg32(P_PWM_PWM_B, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_C:
                            aml_write_reg32(P_PWM_PWM_C, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_D:
                            aml_write_reg32(P_PWM_PWM_D, (pwm_hi << 16) | (pwm_lo));
                            break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                        case BL_PWM_E:
                            aml_write_reg32(P_PWM_PWM_E, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_F:
                            aml_write_reg32(P_PWM_PWM_F, (pwm_hi << 16) | (pwm_lo));
                            break;
#endif
                        default:
                            break;
                    }

                    //set combo_low duty
                    level = (bconf->combo_low_duty_max - bconf->combo_low_duty_min) * (level - bconf->level_min) / (bconf->combo_level_switch - bconf->level_min) + bconf->combo_low_duty_min;
                    if (bconf->combo_low_method == BL_CTL_PWM_NEGATIVE) {
                        pwm_hi = bconf->combo_low_cnt - level;
                        pwm_lo = level;
                    }
                    else {
                        pwm_hi = level;
                        pwm_lo = bconf->combo_low_cnt - level;
                    }
                    switch (bconf->combo_low_port) {
                        case BL_PWM_A:
                            aml_write_reg32(P_PWM_PWM_A, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_B:
                            aml_write_reg32(P_PWM_PWM_B, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_C:
                            aml_write_reg32(P_PWM_PWM_C, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_D:
                            aml_write_reg32(P_PWM_PWM_D, (pwm_hi << 16) | (pwm_lo));
                            break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                        case BL_PWM_E:
                            aml_write_reg32(P_PWM_PWM_E, (pwm_hi << 16) | (pwm_lo));
                            break;
                        case BL_PWM_F:
                            aml_write_reg32(P_PWM_PWM_F, (pwm_hi << 16) | (pwm_lo));
                            break;
#endif
                        default:
                            break;
                    }
                }
                break;
#ifdef CONFIG_AML_BACKLIGHT_EXTERN
            case BL_CTL_EXTERN:
                bl_extern_driver = aml_bl_extern_get_driver();
                if (bl_extern_driver == NULL) {
                    printk("no bl_extern driver\n");
                }
                else {
                    if (bl_extern_driver->set_level) {
                        ret = bl_extern_driver->set_level(level);
                        if (ret)
                            printk("[bl_extern] set_level error\n");
                    }
                    else {
                        printk("[bl_extern] set_level is null\n");
                    }
                }
                break;
#endif
            default:
                break;
        }
