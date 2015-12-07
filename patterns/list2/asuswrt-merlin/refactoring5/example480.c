#ifndef HAVE_EAFD
if (ad->ad_vers == AD_VERSION_EA && size == 0)
        EC_NEG1( unlink(ad->ad_ops->ad_path(uname, 0)) );
    else
#endif
        EC_NEG1( sys_ftruncate(ad_reso_fileno(ad), size + ad->ad_eid[ ADEID_RFORK ].ade_off) );
