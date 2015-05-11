/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/php_var.h"
#include "php_unserialize2.h"

ZEND_DECLARE_MODULE_GLOBALS(unserialize2)

/* True global resources - no need for thread safety here */
static int le_unserialize2;

PHP_FUNCTION(unserialize2_decode);


/* {{{ unserialize2_functions[]
 *
 * Every user visible function must have an entry in unserialize2_functions[].
 */
const zend_function_entry unserialize2_functions[] = {
	PHP_FE(unserialize2_decode,	NULL)
	PHP_FE(confirm_unserialize2_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in unserialize2_functions[] */
};
/* }}} */

/* {{{ unserialize2_module_entry
 */
zend_module_entry unserialize2_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"unserialize2",
	unserialize2_functions,
	PHP_MINIT(unserialize2),
	PHP_MSHUTDOWN(unserialize2),
	PHP_RINIT(unserialize2),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(unserialize2),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(unserialize2),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_UNSERIALIZE2_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_UNSERIALIZE2
ZEND_GET_MODULE(unserialize2)
#endif

/* {{{ php_unserialize2_init_globals
 */

static void php_unserialize2_init_globals(zend_unserialize2_globals *unserialize2_globals)
{
	unserialize2_globals->serialize_lock = 0;
}

/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(unserialize2)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(unserialize2)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(unserialize2)
{
	UNSERIALIZE2_G(serialize_lock) = 0;
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(unserialize2)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(unserialize2)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "unserialize2 support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_unserialize2_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_unserialize2_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "unserialize2", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

PHP_FUNCTION(unserialize2_decode)
{
    char *buf = NULL;
    int buf_len;
    const unsigned char *p;
    php_unserialize_data_t var_hash;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &buf, &buf_len) == FAILURE) {
        RETURN_FALSE;
    }    

    if (buf_len == 0) { 
        RETURN_FALSE;
    }    

    p = (const unsigned char*) buf; 
    PHP_VAR_UNSERIALIZE_INIT(var_hash);
    if (!php_var_unserialize2(&return_value, &p, p + buf_len, &var_hash TSRMLS_CC)) {
        PHP_VAR_UNSERIALIZE_DESTROY(var_hash);
        zval_dtor(return_value);
        if (!EG(exception)) {
            php_error_docref(NULL TSRMLS_CC, E_NOTICE, "Error at offset %ld of %d bytes", (long)((char*)p - buf), buf_len); 
        }    
        RETURN_FALSE;
    }    
    PHP_VAR_UNSERIALIZE_DESTROY(var_hash);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
