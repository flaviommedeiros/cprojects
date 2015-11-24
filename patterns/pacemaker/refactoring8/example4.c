static bool
__xml_acl_check(xmlNode *xml, const char *name, enum xml_private_flags mode)
{
    CRM_ASSERT(xml);
    CRM_ASSERT(xml->doc);
    CRM_ASSERT(xml->doc->_private);

#if ENABLE_ACL
    {
        if(TRACKING_CHANGES(xml) && xml_acl_enabled(xml)) {
            int offset = 0;
            xmlNode *parent = xml;
            char buffer[XML_BUFFER_SIZE];
            xml_private_t *docp = xml->doc->_private;

            if(docp->acls == NULL) {
                crm_trace("Ordinary user %s cannot access the CIB without any defined ACLs", docp->user);
                set_doc_flag(xml, xpf_acl_denied);
                return FALSE;
            }

            offset = __get_prefix(NULL, xml, buffer, offset);
            if(name) {
                offset += snprintf(buffer + offset, XML_BUFFER_SIZE - offset, "[@%s]", name);
            }
            CRM_LOG_ASSERT(offset > 0);

            /* Walk the tree upwards looking for xml_acl_* flags
             * - Creating an attribute requires write permissions for the node
             * - Creating a child requires write permissions for the parent
             */

            if(name) {
                xmlAttr *attr = xmlHasProp(xml, (const xmlChar *)name);

                if(attr && mode == xpf_acl_create) {
                    mode = xpf_acl_write;
                }
            }

            while(parent && parent->_private) {
                xml_private_t *p = parent->_private;
                if(__xml_acl_mode_test(p->flags, mode)) {
                    return TRUE;

                } else if(is_set(p->flags, xpf_acl_deny)) {
                    crm_trace("%x access denied to %s: parent", mode, buffer);
                    set_doc_flag(xml, xpf_acl_denied);
                    return FALSE;
                }
                parent = parent->parent;
            }

            crm_trace("%x access denied to %s: default", mode, buffer);
            set_doc_flag(xml, xpf_acl_denied);
            return FALSE;
        }
    }
#endif

    return TRUE;
}
