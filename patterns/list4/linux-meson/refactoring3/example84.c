switch (bconf->method) {
        case BL_CTL_GPIO:
            bl_gpio_direction_output(bconf->gpio, bconf->gpio_off);
            break;
        case BL_CTL_PWM_NEGATIVE:
        case BL_CTL_PWM_POSITIVE:
            if (bconf->pwm_gpio_used) {
                if (bconf->gpio)
                    bl_gpio_direction_output(bconf->gpio, bconf->gpio_off);
            }
            switch (bconf->pwm_port) {
                case BL_PWM_A:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 0, 1);  //disable pwm_a
                    break;
                case BL_PWM_B:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 1, 1);  //disable pwm_b
                    break;
                case BL_PWM_C:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 0, 1);  //disable pwm_c
                    break;
                case BL_PWM_D:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 1, 1);  //disable pwm_d
                    break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                case BL_PWM_E:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 0, 1);  //disable pwm_c
                    break;
                case BL_PWM_F:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 1, 1);  //disable pwm_d
                    break;
#endif
                default:
                    break;
            }
            break;
        case BL_CTL_PWM_COMBO:
            switch (bconf->combo_high_port) {
                case BL_PWM_A:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 0, 1);  //disable pwm_a
                    break;
                case BL_PWM_B:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 1, 1);  //disable pwm_b
                    break;
                case BL_PWM_C:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 0, 1);  //disable pwm_c
                    break;
                case BL_PWM_D:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 1, 1);  //disable pwm_d
                    break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                case BL_PWM_E:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 0, 1);  //disable pwm_c
                    break;
                case BL_PWM_F:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 1, 1);  //disable pwm_d
                    break;
#endif
                default:
                    break;
            }
            switch (bconf->combo_low_port) {
                case BL_PWM_A:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 0, 1);  //disable pwm_a
                    break;
                case BL_PWM_B:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 1, 1);  //disable pwm_b
                    break;
                case BL_PWM_C:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 0, 1);  //disable pwm_c
                    break;
                case BL_PWM_D:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 1, 1);  //disable pwm_d
                    break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                case BL_PWM_E:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 0, 1);  //disable pwm_c
                    break;
                case BL_PWM_F:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 1, 1);  //disable pwm_d
                    break;
#endif
                default:
                    break;
            }
            break;
#ifdef CONFIG_AML_BACKLIGHT_EXTERN
        case BL_CTL_EXTERN:
            bl_extern_driver = aml_bl_extern_get_driver();
            if (bl_extern_driver == NULL) {
                printk("no bl_extern driver\n");
            }
            else {
                if (bl_extern_driver->power_off) {
                    ret = bl_extern_driver->power_off();
                    if (ret)
                        printk("[bl_extern] power off error\n");
                }
                else {
                    printk("[bl_extern] power off is null\n");
                }
            }
            break;
#endif
        default:
            break;
    }
