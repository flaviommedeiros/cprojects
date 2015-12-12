switch (bconf->method) {
        case BL_CTL_GPIO:
#if (MESON_CPU_TYPE == MESON_CPU_TYPE_MESON6)
            aml_set_reg32_bits(P_LED_PWM_REG0, 1, 12, 2);
#endif
            mdelay(20);
            bl_gpio_direction_output(bconf->gpio, bconf->gpio_on);
            break;
        case BL_CTL_PWM_NEGATIVE:
        case BL_CTL_PWM_POSITIVE:
            switch (bconf->pwm_port) {
                case BL_PWM_A:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, bconf->pwm_pre_div, 8, 7);  //pwm_a_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 4, 2);  //pwm_a_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 15, 1);  //pwm_a_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 0, 1);  //enable pwm_a
                    break;
                case BL_PWM_B:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, bconf->pwm_pre_div, 16, 7);  //pwm_b_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 6, 2);  //pwm_b_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 23, 1);  //pwm_b_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 1, 1);  //enable pwm_b
                    break;
                case BL_PWM_C:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, bconf->pwm_pre_div, 8, 7);  //pwm_c_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 4, 2);  //pwm_c_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 15, 1);  //pwm_c_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 0, 1);  //enable pwm_c
                    break;
                case BL_PWM_D:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, bconf->pwm_pre_div, 16, 7);  //pwm_d_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 6, 2);  //pwm_d_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 23, 1);  //pwm_d_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 1, 1);  //enable pwm_d
                    break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                case BL_PWM_E:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, bconf->pwm_pre_div, 8, 7);  //pwm_c_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 4, 2);  //pwm_c_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 15, 1);  //pwm_c_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 0, 1);  //enable pwm_c
                    break;
                case BL_PWM_F:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, bconf->pwm_pre_div, 16, 7);  //pwm_d_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 6, 2);  //pwm_d_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 23, 1);  //pwm_d_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 1, 1);  //enable pwm_d
                    break;
#endif
                default:
                    break;
            }

            if (IS_ERR(bconf->p)) {
                printk("set backlight pinmux error.\n");
                goto exit_power_on_bl;
            }
            s = pinctrl_lookup_state(bconf->p, "default"); //select pinctrl
            if (IS_ERR(s)) {
                printk("set backlight pinmux error.\n");
                devm_pinctrl_put(bconf->p);
                goto exit_power_on_bl;
            }

            ret = pinctrl_select_state(bconf->p, s); //set pinmux and lock pins
            if (ret < 0) {
                printk("set backlight pinmux error.\n");
                devm_pinctrl_put(bconf->p);
                goto exit_power_on_bl;
            }
            mdelay(20);
            if (bconf->pwm_gpio_used) {
                if (bconf->gpio)
                    bl_gpio_direction_output(bconf->gpio, bconf->gpio_on);
            }
            break;
        case BL_CTL_PWM_COMBO:
            switch (bconf->combo_high_port) {
                case BL_PWM_A:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, bconf->combo_high_pre_div, 8, 7);  //pwm_a_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 4, 2);  //pwm_a_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 15, 1);  //pwm_a_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 0, 1);  //enable pwm_a
                    break;
                case BL_PWM_B:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, bconf->combo_high_pre_div, 16, 7);  //pwm_b_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 6, 2);  //pwm_b_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 23, 1);  //pwm_b_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 1, 1);  //enable pwm_b
                    break;
                case BL_PWM_C:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, bconf->combo_high_pre_div, 8, 7);  //pwm_c_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 4, 2);  //pwm_c_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 15, 1);  //pwm_c_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 0, 1);  //enable pwm_c
                    break;
                case BL_PWM_D:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, bconf->combo_high_pre_div, 16, 7);  //pwm_d_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 6, 2);  //pwm_d_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 23, 1);  //pwm_d_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 1, 1);  //enable pwm_d
                    break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                case BL_PWM_E:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, bconf->combo_high_pre_div, 8, 7);  //pwm_c_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 4, 2);  //pwm_c_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 15, 1);  //pwm_c_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 0, 1);  //enable pwm_c
                    break;
                case BL_PWM_F:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, bconf->combo_high_pre_div, 16, 7);  //pwm_d_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 6, 2);  //pwm_d_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 23, 1);  //pwm_d_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 1, 1);  //enable pwm_d
                    break;
#endif
                default:
                    break;
            }
            switch (bconf->combo_low_port) {
                case BL_PWM_A:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, bconf->combo_low_pre_div, 8, 7);  //pwm_a_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 4, 2);  //pwm_a_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 15, 1);  //pwm_a_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 0, 1);  //enable pwm_a
                    break;
                case BL_PWM_B:
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, bconf->combo_low_pre_div, 16, 7);  //pwm_b_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 0, 6, 2);  //pwm_b_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 23, 1);  //pwm_b_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_AB, 1, 1, 1);  //enable pwm_b
                    break;
                case BL_PWM_C:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, bconf->combo_low_pre_div, 8, 7);  //pwm_c_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 4, 2);  //pwm_c_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 15, 1);  //pwm_c_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 0, 1);  //enable pwm_c
                    break;
                case BL_PWM_D:
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, bconf->combo_low_pre_div, 16, 7);  //pwm_d_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 0, 6, 2);  //pwm_d_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 23, 1);  //pwm_d_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_CD, 1, 1, 1);  //enable pwm_d
                    break;
#if (MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8)
                case BL_PWM_E:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, bconf->combo_low_pre_div, 8, 7);  //pwm_c_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 4, 2);  //pwm_c_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 15, 1);  //pwm_c_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 0, 1);  //enable pwm_c
                    break;
                case BL_PWM_F:
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, bconf->combo_low_pre_div, 16, 7);  //pwm_d_clk_div
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 0, 6, 2);  //pwm_d_clk_sel
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 23, 1);  //pwm_d_clk_en
                    aml_set_reg32_bits(P_PWM_MISC_REG_EF, 1, 1, 1);  //enable pwm_d
                    break;
#endif
                default:
                    break;
            }

            if (IS_ERR(bconf->p)) {
                printk("set backlight pinmux error.\n");
                goto exit_power_on_bl;
            }
            s = pinctrl_lookup_state(bconf->p, "pwm_combo");  //select pinctrl
            if (IS_ERR(s)) {
                printk("set backlight pinmux error.\n");
                devm_pinctrl_put(bconf->p);
                goto exit_power_on_bl;
            }

            ret = pinctrl_select_state(bconf->p, s);  //set pinmux and lock pins
            if (ret < 0) {
                printk("set backlight pinmux error.\n");
                devm_pinctrl_put(bconf->p);
                goto exit_power_on_bl;
            }
            break;
#ifdef CONFIG_AML_BACKLIGHT_EXTERN
        case BL_CTL_EXTERN:
            bl_extern_driver = aml_bl_extern_get_driver();
            if (bl_extern_driver == NULL) {
                printk("no bl_extern driver\n");
            }
            else {
                if (bl_extern_driver->power_on) {
                    ret = bl_extern_driver->power_on();
                    if (ret) {
                        printk("[bl_extern] power on error\n");
                        goto exit_power_on_bl;
                    }
                }
                else {
                    printk("[bl_extern] power on is null\n");
                }
            }
            break;
#endif
        default:
            printk("wrong backlight control method\n");
            goto exit_power_on_bl;
            break;
    }
