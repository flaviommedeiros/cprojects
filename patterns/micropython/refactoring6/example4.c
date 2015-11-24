if (self->tim.Instance != TIM1
            &&  self->tim.Instance != TIM2
            &&  self->tim.Instance != TIM3
            &&  self->tim.Instance != TIM4
            &&  self->tim.Instance != TIM5
            #if defined(TIM8)
            &&  self->tim.Instance != TIM8
            #endif
            ) {
                nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError, "encoder not supported on timer %d", self->tim_id));
            }
