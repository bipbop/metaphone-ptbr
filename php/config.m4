PHP_ARG_ENABLE(metaphoneptbr, whether to enable metaphoneptbr support,
[  --enable-metaphoneptbr          Enable metaphoneptbr support])

if test "$PHP_metaphoneptbr" != "no"; then
  AC_DEFINE(HAVE_metaphoneptbr, 1, [ Have metaphoneptbr support ])
  PHP_NEW_EXTENSION(metaphoneptbr, php-metaphone_ptbr.c ../lib/metaphone_ptbr.c, $ext_shared)
fi