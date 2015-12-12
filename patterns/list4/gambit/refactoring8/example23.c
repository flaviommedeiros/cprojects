___HIDDEN void init_symkey_glo2
   ___P((___mod_or_lnk mol),
        (mol)
___mod_or_lnk mol;)
{
  if (mol->module.kind == ___LINKFILE_KIND)
    {
      ___linkinfo *p1 = mol->linkfile.linkertbl;
      ___FAKEWORD *p2 = mol->linkfile.sym_list;
      ___FAKEWORD *p3 = mol->linkfile.key_list;

      while (p1->mol != 0)
        {
          init_symkey_glo2 (p1->mol);
          p1++;
        }

      while (p2 != 0)
        {
          ___SCMOBJ sym;
          ___SCMOBJ str;
          ___SCMOBJ *sym_ptr;
          ___glo_struct *glo;

          sym_ptr = ___CAST(___SCMOBJ*,p2);

          p2 = ___CAST(___FAKEWORD*,sym_ptr[0]);
          str = align_subtyped (___CAST(___SCMOBJ*,sym_ptr[1+___SYMKEY_NAME]));
          glo = ___CAST(___glo_struct*,sym_ptr[1+___SYMBOL_GLOBAL]);

#ifndef ___SINGLE_VM

          glo->val = ___GSTATE->mem.nb_glo_vars++;

#endif

          glo->next = 0;
          if (___GSTATE->mem.glo_list_head == 0)
            ___GSTATE->mem.glo_list_head = glo;
          else
            ___GSTATE->mem.glo_list_tail->next = glo;
          ___GSTATE->mem.glo_list_tail = glo;

          *sym_ptr = ___MAKE_HD((___SYMBOL_SIZE<<___LWS),___sSYMBOL,___PERM);

          sym = align_subtyped (sym_ptr);

          ___FIELD(sym,___SYMKEY_NAME) = str;
          ___FIELD(sym,___SYMBOL_GLOBAL) = ___CAST(___SCMOBJ,glo);

          ___intern_symkey (sym);
        }

      while (p3 != 0)
        {
          ___SCMOBJ key, str;
          ___SCMOBJ *key_ptr;

          key_ptr = ___CAST(___SCMOBJ*,p3);

          p3 = ___CAST(___FAKEWORD*,key_ptr[0]);
          str = align_subtyped (___CAST(___SCMOBJ*,key_ptr[1+___SYMKEY_NAME]));

          *key_ptr = ___MAKE_HD((___KEYWORD_SIZE<<___LWS),___sKEYWORD,___PERM);

          key = align_subtyped (key_ptr);

          ___FIELD(key,___SYMKEY_NAME) = str;
          ___FIELD(key,___SYMKEY_HASH) = ___hash_scheme_string (str);

          ___intern_symkey (key);
        }
    }
}
