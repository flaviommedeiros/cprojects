#ifdef ADMIN_GRP
if (admin)
        obj->uid = 0;
    else
#endif /* ADMIN_GRP */
        obj->uid = geteuid();
