static unsigned long pmw_base[] = {
    P_PWM_PWM_A,
    P_PWM_PWM_B,
    P_PWM_PWM_C,
    P_PWM_PWM_D,
#if MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8
    P_PWM_PWM_E,
    P_PWM_PWM_F,
#endif
};
