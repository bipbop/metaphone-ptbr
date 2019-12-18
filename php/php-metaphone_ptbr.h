/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2019 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: %CREDITS% |
   +----------------------------------------------------------------------+
*/


#ifndef PHP_METAPHONEPTBR_H
# define PHP_METAPHONEPTBR_H

extern zend_module_entry metaphoneptbr_module_entry;
# define phpext_etaphoneptbr_ptr &metaphoneptbr_module_entry

# define PHP_METAPHONEPTBR_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_METAPHONEPTBR)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_METAPHONEPTBR_H */
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
