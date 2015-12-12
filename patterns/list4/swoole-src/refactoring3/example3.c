switch(size)
        {
        case 1:
            col->size = 1;
            col->type = SW_TABLE_INT8;
            break;
        case 2:
            col->size = 2;
            col->type = SW_TABLE_INT16;
            break;
#ifdef __x86_64__
        case 8:
            col->size = 8;
            col->type = SW_TABLE_INT64;
            break;
#endif
        default:
            col->size = 4;
            col->type = SW_TABLE_INT32;
            break;
        }
