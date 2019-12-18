#include <stdio.h>
#include <time.h>

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "zend_exceptions.h"

#include "../lib/metaphone_ptbr.h"
#include "php-metaphone_ptbr.h"


/* {{{ string metaphoneptbr( [ string $var ] )
 */
PHP_FUNCTION(metaphoneptbr)
{

    char *payload;
	char *nullptr;
	char *ret;
	wchar_t *payload_wide;
	size_t payload_len;
	size_t payload_wide_len;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(payload, payload_len)
    ZEND_PARSE_PARAMETERS_END();

	payload_wide_len = payload_len  * sizeof(wchar_t);
	payload_wide = malloc(payload_wide_len);
	if (payload_wide == NULL) {
		RETURN_NULL();
	}

	bzero(payload_wide, payload_wide_len);
	mbstowcs(payload_wide, payload, payload_len);

	ret = metaphone_ptbr(payload_wide, payload_len);
	if (ret == NULL) {
		RETURN_NULL();
		return;
	}

	RETURN_STRING(ret);
	free(ret);
}
/* }}}*/


/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(metaphoneptbr)
{
#if defined(ZTS) && defined(COMPILE_DL_METAPHONEPTBR)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */



/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(metaphoneptbr)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(metaphoneptbr)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(metaphoneptbr)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "metaphoneptbr support", "enabled");
	php_info_print_table_end();
	
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_metaphoneptbr, 0)
    ZEND_ARG_INFO(0, _payload)
ZEND_END_ARG_INFO()

/* }}} */

/* {{{ metaphoneptbr_functions[]
 */
const zend_function_entry metaphoneptbr_functions[] = {
    PHP_FE(metaphoneptbr, arginfo_metaphoneptbr)
	PHP_FE_END
};

/* }}} */

/* {{{ metaphoneptbr_module_entry
 */
zend_module_entry metaphoneptbr_module_entry = {
	STANDARD_MODULE_HEADER,
	"metaphoneptbr",						/* Extension name */
	metaphoneptbr_functions,				/* zend_function_entry */
	PHP_MINIT(metaphoneptbr),		/* PHP_MINIT - Module initialization */
	PHP_MSHUTDOWN(metaphoneptbr),	/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(metaphoneptbr),				/* PHP_RINIT - Request initialization */
	NULL,								/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(metaphoneptbr),				/* PHP_MINFO - Module info */
	PHP_METAPHONEPTBR_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_METAPHONEPTBR
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(metaphoneptbr)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */