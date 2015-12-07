#ifndef PBS_MOM
if (strncmp(pn, pj->ji_qs.ji_fileprefix, strlen(pj->ji_qs.ji_fileprefix)) != 0)
#else
  if(multi_mom != 0)
    {
    sprintf(fileid,"%s%d",pj->ji_qs.ji_fileprefix,pbs_rm_port);
    }
  else
    {
    strcpy(fileid,pj->ji_qs.ji_fileprefix);
    }
