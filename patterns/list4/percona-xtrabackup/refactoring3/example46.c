switch (keyseg->type) {
    case HA_KEYTYPE_BINARY:
      if (!(keyseg->flag & HA_SPACE_PACK) && keyseg->length == 1)
      {						/* packed binary digit */
	(void) fprintf(stream,"%d",(uint) *key++);
	break;
      }
      /* fall through */
    case HA_KEYTYPE_TEXT:
    case HA_KEYTYPE_NUM:
      if (keyseg->flag & HA_SPACE_PACK)
      {
	(void) fprintf(stream,"%.*s",(int) *key,key+1);
	key+= (int) *key+1;
      }
      else
      {
	(void) fprintf(stream,"%.*s",(int) keyseg->length,key);
	key=end;
      }
      break;
    case HA_KEYTYPE_INT8:
      (void) fprintf(stream,"%d",(int) *((signed char*) key));
      key=end;
      break;
    case HA_KEYTYPE_SHORT_INT:
      s_1= mi_sint2korr(key);
      (void) fprintf(stream,"%d",(int) s_1);
      key=end;
      break;
    case HA_KEYTYPE_USHORT_INT:
      {
	ushort u_1;
	u_1= mi_uint2korr(key);
	(void) fprintf(stream,"%u",(uint) u_1);
	key=end;
	break;
      }
    case HA_KEYTYPE_LONG_INT:
      l_1=mi_sint4korr(key);
      (void) fprintf(stream,"%ld",l_1);
      key=end;
      break;
    case HA_KEYTYPE_ULONG_INT:
      l_1=mi_sint4korr(key);
      (void) fprintf(stream,"%lu",(ulong) l_1);
      key=end;
      break;
    case HA_KEYTYPE_INT24:
      (void) fprintf(stream,"%ld",(long) mi_sint3korr(key));
      key=end;
      break;
    case HA_KEYTYPE_UINT24:
      (void) fprintf(stream,"%lu",(ulong) mi_uint3korr(key));
      key=end;
      break;
    case HA_KEYTYPE_FLOAT:
      mi_float4get(f_1,key);
      (void) fprintf(stream,"%g",(double) f_1);
      key=end;
      break;
    case HA_KEYTYPE_DOUBLE:
      mi_float8get(d_1,key);
      (void) fprintf(stream,"%g",d_1);
      key=end;
      break;
#ifdef HAVE_LONG_LONG
    case HA_KEYTYPE_LONGLONG:
    {
      char buff[21];
      longlong2str(mi_sint8korr(key),buff,-10);
      (void) fprintf(stream,"%s",buff);
      key=end;
      break;
    }
    case HA_KEYTYPE_ULONGLONG:
    {
      char buff[21];
      longlong2str(mi_sint8korr(key),buff,10);
      (void) fprintf(stream,"%s",buff);
      key=end;
      break;
    }
    case HA_KEYTYPE_BIT:
    {
      uint i;
      fputs("0x",stream);
      for (i=0 ; i < keyseg->length ; i++)
        fprintf(stream, "%02x", (uint) *key++);
      key= end;
      break;
    }

#endif
    case HA_KEYTYPE_VARTEXT1:                   /* VARCHAR and TEXT */
    case HA_KEYTYPE_VARTEXT2:                   /* VARCHAR and TEXT */
    case HA_KEYTYPE_VARBINARY1:                 /* VARBINARY and BLOB */
    case HA_KEYTYPE_VARBINARY2:                 /* VARBINARY and BLOB */
    {
      uint tmp_length;
      get_key_length(tmp_length,key);
      /*
	The following command sometimes gives a warning from valgrind.
	Not yet sure if the bug is in valgrind, glibc or mysqld
      */
      (void) fprintf(stream,"%.*s",(int) tmp_length,key);
      key+=tmp_length;
      break;
    }
    default: break;			/* This never happens */
    }
