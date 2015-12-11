if(pa_channel_map_equal(&info->channel_map, &map)
#if PA_CHECK_VERSION(0,9,15)
           || (pa_channel_map_superset &&
               pa_channel_map_superset(&info->channel_map, &map))
#endif
            )
        {
            device->FmtChans = chanmaps[i].chans;
            return;
        }
