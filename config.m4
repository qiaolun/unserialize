dnl $Id$
dnl config.m4 for extension unserialize2

PHP_ARG_ENABLE(unserialize2, whether to enable unserialize2 support,
Make sure that the comment is aligned:
[  --enable-unserialize2           Enable unserialize2 support])

if test "$PHP_UNSERIALIZE2" != "no"; then
  PHP_NEW_EXTENSION(unserialize2, unserialize2.c var_unserializer2.c, $ext_shared)
fi
