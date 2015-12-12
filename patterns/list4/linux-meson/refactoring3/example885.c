switch( port ) {
#ifdef USE_WDS
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    skb->dev = lp->wds_port[port-1].dev;
                    break;
#endif  /* USE_WDS */

                case 0:
                default:
                    skb->dev = dev;
                    break;
                }
