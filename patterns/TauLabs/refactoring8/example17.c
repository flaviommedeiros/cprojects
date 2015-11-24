void PIOS_Servo_SetMode(const uint16_t * speeds, const enum pwm_mode *pwm_mode, uint8_t banks)
{
	if (!servo_cfg) {
		return;
	}

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = servo_cfg->tim_base_init;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	uint8_t set = 0;

	for (uint8_t i = 0; (i < servo_cfg->num_channels) && (set < banks); i++) {
		bool new = true;
		const struct pios_tim_channel * chan = &servo_cfg->channels[i];

		/* See if any previous channels use that same timer */
		for (uint8_t j = 0; (j < i) && new; j++) {
			new = new && (chan->timer != servo_cfg->channels[j].timer);
		}

		if (new) {

			uint32_t clk_rate = 0;

			// Based on PWM mode determine the desired output period (which sets the
			// channel resolution)
			if (pwm_mode[set] == PWM_MODE_1MHZ) {
				clk_rate = PWM_MODE_1MHZ_RATE; // Default output timer frequency in hertz
			} else if (pwm_mode[set] == PWM_MODE_12MHZ) {
				clk_rate = PWM_MODE_12MHZ_RATE; // Default output timer frequency in hertz
			}

			if (speeds[set] == 0) {
				// Use a maximally long period because we don't want pulses actually repeating
				// without new data arriving.
				TIM_TimeBaseStructure.TIM_Period = 0xFFFFFFFF;

			} else {
				// Note: this can be extended with a new PWM mode that is lower resolution
				// for very long periods
				TIM_TimeBaseStructure.TIM_Period = (clk_rate / speeds[set]) - 1;
			}

			/* Choose the correct prescaler value for the APB to which the timer is attached */
			if (chan->timer==TIM6 || chan->timer==TIM7) {
				// These timers cannot be used here.
				return;
			} else if (chan->timer==TIM2 || chan->timer==TIM3 || chan->timer==TIM4) {
				//those timers run at double APB1 speed if APB1 prescaler is != 1 which is usually the case
				TIM_TimeBaseStructure.TIM_Prescaler = (PIOS_PERIPHERAL_APB1_CLOCK / clk_rate * 2) - 1;
			} else {
				TIM_TimeBaseStructure.TIM_Prescaler = (PIOS_PERIPHERAL_APB2_CLOCK / clk_rate) - 1;
			}

			// Configure this timer appropriately.
			TIM_TimeBaseInit(chan->timer, &TIM_TimeBaseStructure);	

			/* Configure frequency scaler for all channels that use the same timer */
			for (uint8_t j=0; (j < servo_cfg->num_channels); j++) {
				if (chan->timer == servo_cfg->channels[j].timer) {
#if defined(PIOS_INCLUDE_HPWM)
					/* save the frequency for these channels */
					output_channel_mode[j] = (speeds[set] == 0) ? SYNC_PWM_TRUE : SYNC_PWM_FALSE;
					output_channel_resolution[j] = pwm_mode[set];
#endif
				}
			}

			set++;
		}
	}
}
