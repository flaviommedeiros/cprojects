switch(ucAudioSampleClock)
                    {
                    case AUDFS_192KHz: ucAudioSampleClock=AUDFS_48KHz;break ;// default: -> 48KHz

                    case AUDFS_48KHz: ucAudioSampleClock=AUDFS_44p1KHz;break ;//
                    case AUDFS_44p1KHz: ucAudioSampleClock=AUDFS_32KHz;break ;//
                    case AUDFS_32KHz: ucAudioSampleClock=AUDFS_96KHz;break ;//

                #ifndef SUPPORT_FORCE_88p2_176p4

                    case AUDFS_96KHz: ucAudioSampleClock=AUDFS_192KHz;break ;//

                #else // SUPPORT_FORCE_88p2_176p4

                    case AUDFS_88p2KHz: ucAudioSampleClock=AUDFS_176p4KHz;break ;//
                    case AUDFS_96KHz: ucAudioSampleClock=AUDFS_88p2KHz;break ;//
                    case AUDFS_176p4KHz: ucAudioSampleClock=AUDFS_192KHz;break ;//

                #endif

                    default: ucAudioSampleClock=AUDFS_48KHz;break;// ? -> 48KHz
                    }
