static  struct  class_attribute   *tv_attr[]={
&class_TV_attr_vdac_setting,
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
&class_TV_attr_policy_fr_auto,
&class_TV_attr_policy_fr_auto_switch,
#endif
};
