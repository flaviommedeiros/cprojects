char *perl_weechat_code =
{
#ifndef MULTIPLICITY
    "package %s;"
#endif /* MULTIPLICITY */
    "$SIG{__WARN__} = sub { weechat::print('', 'perl\twarning: '.$_[0]) };"
    "$SIG{__DIE__} = sub { weechat::print('', 'perl\terror: '.$_[0]) };"
    "do '%s';"
};
