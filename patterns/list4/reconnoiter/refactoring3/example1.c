switch(vars->type) {
        case ASN_OCTET_STR:
          sp = malloc(1 + vars->val_len);
          memcpy(sp, vars->val.string, vars->val_len);
          sp[vars->val_len] = '\0';
          SETM(METRIC_STRING, sp);
          free(sp);
          break;
        case ASN_INTEGER:
        case ASN_GAUGE:
          SETM(METRIC_INT32, vars->val.integer);
          break;
        case ASN_TIMETICKS:
        case ASN_COUNTER:
          SETM(METRIC_UINT32, vars->val.integer);
          break;
#ifdef ASN_OPAQUE_I64
        case ASN_OPAQUE_I64:
#endif
        case ASN_INTEGER64:
          printI64(varbuff, vars->val.counter64);
          i64 = strtoll(varbuff, &endptr, 10);
          SETM(METRIC_INT64, (varbuff == endptr) ? NULL : &i64);
          break;
#ifdef ASN_OPAQUE_U64
        case ASN_OPAQUE_U64:
#endif
#ifdef ASN_OPAQUE_COUNTER64
        case ASN_OPAQUE_COUNTER64:
#endif
        case ASN_COUNTER64:
          printU64(varbuff, vars->val.counter64);
          u64 = strtoull(varbuff, &endptr, 10);
          SETM(METRIC_UINT64, (varbuff == endptr) ? NULL : &u64);
          break;
#ifdef ASN_OPAQUE_FLOAT
        case ASN_OPAQUE_FLOAT:
#endif
        case ASN_FLOAT:
          if(vars->val.floatVal) float_conv = *(vars->val.floatVal);
          SETM(METRIC_DOUBLE, vars->val.floatVal ? &float_conv : NULL);
          break;
#ifdef ASN_OPAQUE_DOUBLE
        case ASN_OPAQUE_DOUBLE:
#endif
        case ASN_DOUBLE:
          SETM(METRIC_DOUBLE, vars->val.doubleVal);
          break;
        case ASN_NULL:
          mtevL(nldeb, "snmp[null]: %s\n", varbuff);
        case SNMP_NOSUCHOBJECT:
        case SNMP_NOSUCHINSTANCE:
          SETM(METRIC_STRING, NULL);
          break;
        default:
          /* Advance passed the first space and use that unless there
           * is no space or we have no more string left.
           */
          sp = strchr(varbuff, ' ');
          if(sp) sp++;
          SETM(METRIC_STRING, (sp && *sp) ? sp : NULL);
          mtevL(nlerr, "snmp: unknown type[%d] %s\n", vars->type, varbuff);
      }
