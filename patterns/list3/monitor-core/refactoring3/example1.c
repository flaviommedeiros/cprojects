switch ( xt->tag )
      {
         case GRID_TAG:
            rc = endElement_GRID(data, el);
            break;

         case CLUSTER_TAG:
            rc = endElement_CLUSTER(data, el);
            break;

#ifdef WITH_RIEMANN
         case HOST_TAG:
            rc = endElement_HOST(data, el);
            break;
#endif /* WITH_RIEMANN */

         default:
               break;
      }
