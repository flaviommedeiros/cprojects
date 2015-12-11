switch (OBJ_obj2nid(cms->contentType)) {

    case NID_pkcs7_data:
        return cont;

    case NID_pkcs7_signed:
        cmsbio = cms_SignedData_init_bio(cms);
        break;

    case NID_pkcs7_digest:
        cmsbio = cms_DigestedData_init_bio(cms);
        break;
#ifdef ZLIB
    case NID_id_smime_ct_compressedData:
        cmsbio = cms_CompressedData_init_bio(cms);
        break;
#endif

    case NID_pkcs7_encrypted:
        cmsbio = cms_EncryptedData_init_bio(cms);
        break;

    case NID_pkcs7_enveloped:
        cmsbio = cms_EnvelopedData_init_bio(cms);
        break;

    default:
        CMSerr(CMS_F_CMS_DATAINIT, CMS_R_UNSUPPORTED_TYPE);
        return NULL;
    }
