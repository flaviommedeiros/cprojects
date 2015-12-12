switch (tuple->TupleCode) {
    case CISTPL_DEVICE:
    case CISTPL_DEVICE_A:
	ret = parse_device(tuple, &parse->device);
	break;
#ifdef CONFIG_CARDBUS
    case CISTPL_BAR:
	ret = parse_bar(tuple, &parse->bar);
	break;
    case CISTPL_CONFIG_CB:
	ret = parse_config_cb(tuple, &parse->config);
	break;
    case CISTPL_CFTABLE_ENTRY_CB:
	ret = parse_cftable_entry_cb(tuple, &parse->cftable_entry_cb);
	break;
#endif
    case CISTPL_CHECKSUM:
	ret = parse_checksum(tuple, &parse->checksum);
	break;
    case CISTPL_LONGLINK_A:
    case CISTPL_LONGLINK_C:
	ret = parse_longlink(tuple, &parse->longlink);
	break;
    case CISTPL_LONGLINK_MFC:
	ret = parse_longlink_mfc(tuple, &parse->longlink_mfc);
	break;
    case CISTPL_VERS_1:
	ret = parse_vers_1(tuple, &parse->version_1);
	break;
    case CISTPL_ALTSTR:
	ret = parse_altstr(tuple, &parse->altstr);
	break;
    case CISTPL_JEDEC_A:
    case CISTPL_JEDEC_C:
	ret = parse_jedec(tuple, &parse->jedec);
	break;
    case CISTPL_MANFID:
	ret = parse_manfid(tuple, &parse->manfid);
	break;
    case CISTPL_FUNCID:
	ret = parse_funcid(tuple, &parse->funcid);
	break;
    case CISTPL_FUNCE:
	ret = parse_funce(tuple, &parse->funce);
	break;
    case CISTPL_CONFIG:
	ret = parse_config(tuple, &parse->config);
	break;
    case CISTPL_CFTABLE_ENTRY:
	ret = parse_cftable_entry(tuple, &parse->cftable_entry);
	break;
    case CISTPL_DEVICE_GEO:
    case CISTPL_DEVICE_GEO_A:
	ret = parse_device_geo(tuple, &parse->device_geo);
	break;
    case CISTPL_VERS_2:
	ret = parse_vers_2(tuple, &parse->vers_2);
	break;
    case CISTPL_ORG:
	ret = parse_org(tuple, &parse->org);
	break;
    case CISTPL_FORMAT:
    case CISTPL_FORMAT_A:
	ret = parse_format(tuple, &parse->format);
	break;
    case CISTPL_NO_LINK:
    case CISTPL_LINKTARGET:
	ret = 0;
	break;
    default:
	ret = -EINVAL;
	break;
    }
