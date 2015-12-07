if (actives[i].active && !actives[i].looping
                #ifdef BOX_NOTIFY
                    && !actives[i].box
                #endif
            ) {
                if(actives[i].id_indicator)
                    *actives[i].id_indicator = -1;    /* reset indicator value */

                if (!is_playing(actives[i].source)) {
                /* Close */
                    alSourceStop(actives[i].source);
                    alDeleteSources(1, &actives[i].source);
                    alDeleteBuffers(1, &actives[i].buffer);
                    memset(&actives[i], 0, sizeof(struct _ActiveNotifications));
                }
            }
        #ifdef BOX_NOTIFY
            else if (actives[i].box && time(NULL) >= actives[i].n_timeout)
            {
                GError* ignore;
                notify_notification_close(actives[i].box, &ignore);
                actives[i].box = NULL;
                if(actives[i].id_indicator)
                    *actives[i].id_indicator = -1;    /* reset indicator value */

                if (!actives[i].looping && !is_playing(actives[i].source)) {
                /* stop source if not looping or playing, just terminate box */
                    alSourceStop(actives[i].source);
                    alDeleteSources(1, &actives[i].source);
                    alDeleteBuffers(1, &actives[i].buffer);
                    memset(&actives[i], 0, sizeof(struct _ActiveNotifications));
                }
            }
