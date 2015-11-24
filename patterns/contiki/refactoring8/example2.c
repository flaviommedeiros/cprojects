unsigned char
ctk_menuitem_add(CC_REGISTER_ARG struct ctk_menu *menu, char *name)
{
#if CTK_CONF_MENUS
  if(menu->nitems == CTK_MAXMENUITEMS) {
    return 0;
  }
  menu->items[menu->nitems].title = name;
  menu->items[menu->nitems].titlelen = (unsigned char)strlen(name);
  return menu->nitems++;
#else
  return 0;
#endif /* CTK_CONF_MENUS */
}
