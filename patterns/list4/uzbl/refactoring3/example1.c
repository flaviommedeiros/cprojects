switch (status) {
#ifdef USE_WEBKIT2
    case WEBKIT_LOAD_STARTED:
#else
    case WEBKIT_LOAD_PROVISIONAL:
#endif
        uzbl_events_send (LOAD_START, NULL,
            NULL);
        break;
#ifdef USE_WEBKIT2
    case WEBKIT_LOAD_REDIRECTED:
        event = LOAD_REDIRECTED;
        break;
#else
    case WEBKIT_LOAD_FIRST_VISUALLY_NON_EMPTY_LAYOUT:
        /* TODO: Implement. */
        break;
    case WEBKIT_LOAD_FAILED:
        /* Handled by load_error_cb. */
        break;
#endif
    case WEBKIT_LOAD_COMMITTED:
        event = LOAD_COMMIT;
        break;
    case WEBKIT_LOAD_FINISHED:
#ifdef USE_WEBKIT2
        if (uzbl.gui_->load_failed) {
            uzbl.gui_->load_failed = FALSE;
            break;
        }
#endif
        event = LOAD_FINISH;
        break;
    default:
        uzbl_debug ("Unrecognized load status: %d\n", status);
        break;
    }
