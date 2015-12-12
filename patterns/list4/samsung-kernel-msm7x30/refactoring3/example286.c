switch (cmd)
    {
#ifdef VIBE_TUNING1
		case 185:
			g_PWM_duty_max = arg; /* set value of g_PWM_duty_max in ImmVibeSPI */
			break;
		case 186:
			g_PWM_ctrl = arg; /* set value of g_PWM_ctrl in ImmVibeSPI */
			break;
		case 187:
			g_PWM_multiplier = arg; /* set value of g_PWM_multiplier in ImmVibeSPI */
			break;
#endif /* VIBE_TUNING */
#ifdef VIBE_TUNING_IMMR
		/*commands from the test app(ChangeFreq.apk)*/
		case TSPDRV_TUNING_ARG1:
			printk("[tspdrv] TSPDRV_TUNING_ARG1 arg : %ld\n", arg);
			g_nLRA_GP_CLK_M = arg;
			break;
		case TSPDRV_TUNING_ARG2:
			printk("[tspdrv] TSPDRV_TUNING_ARG2 arg : %ld\n", arg);
			g_nLRA_GP_CLK_N = arg; 
			g_nLRA_GP_CLK_D = (g_nLRA_GP_CLK_N >> 1);
			break;
#endif /* VIBE_TUNING_IMMR */
        case TSPDRV_STOP_KERNEL_TIMER:
            /* 
            ** As we send one sample ahead of time, we need to finish playing the last sample
            ** before stopping the timer. So we just set a flag here.
            */
            if (true == g_bIsPlaying) g_bStopRequested = true;

#ifdef VIBEOSKERNELPROCESSDATA
            /* Last data processing to disable amp and stop timer */
            VibeOSKernelProcessData(NULL);
#endif

#ifdef QA_TEST
            if (g_nForceLogIndex)
            {
                for (i=0; i<g_nForceLogIndex; i++)
                {
                    printk("<6>%d\t%d\n", g_nTime, g_nForceLog[i]);
                    g_nTime += TIME_INCREMENT;
                }
            }
            g_nTime = 0;
            g_nForceLogIndex = 0;
#endif
            break;

        case TSPDRV_MAGIC_NUMBER:
            file->private_data = (void*)TSPDRV_MAGIC_NUMBER;
            break;

        case TSPDRV_ENABLE_AMP:
            wake_lock(&vib_wake_lock);
            ImmVibeSPI_ForceOut_AmpEnable(arg);
            DbgRecorderReset((arg));
            DbgRecord((arg,";------- TSPDRV_ENABLE_AMP ---------\n"));
            break;

        case TSPDRV_DISABLE_AMP:
            /* Small fix for now to handle proper combination of TSPDRV_STOP_KERNEL_TIMER and TSPDRV_DISABLE_AMP together */
            /* If a stop was requested, ignore the request as the amp will be disabled by the timer proc when it's ready */
            if(!g_bStopRequested)
            {
                ImmVibeSPI_ForceOut_AmpDisable(arg);
            }
            wake_unlock(&vib_wake_lock);
            break;

        case TSPDRV_GET_NUM_ACTUATORS:
            return NUM_ACTUATORS;
    }
