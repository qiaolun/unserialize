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

#ifndef PHP_UNSERIALIZE2_H
#define PHP_UNSERIALIZE2_H

extern zend_module_entry unserialize2_module_entry;
#define phpext_unserialize2_ptr &unserialize2_module_entry

#define PHP_UNSERIALIZE2_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_UNSERIALIZE2_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_UNSERIALIZE2_API __attribute__ ((visibility("default")))
#else
#	define PHP_UNSERIALIZE2_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(unserialize2);
PHP_MSHUTDOWN_FUNCTION(unserialize2);
PHP_RINIT_FUNCTION(unserialize2);
PHP_RSHUTDOWN_FUNCTION(unserialize2);
PHP_MINFO_FUNCTION(unserialize2);

PHP_FUNCTION(confirm_unserialize2_compiled);	/* For testing, remove later. */

PHP_FUNCTION(unserialize2_decode);


ZEND_BEGIN_MODULE_GLOBALS(unserialize2)
	unsigned serialize_lock;
ZEND_END_MODULE_GLOBALS(unserialize2)


#ifdef ZTS
#define UNSERIALIZE2_G(v) TSRMG(unserialize2_globals_id, zend_unserialize2_globals *, v)
#else
#define UNSERIALIZE2_G(v) (unserialize2_globals.v)
#endif

#endif	/* PHP_UNSERIALIZE2_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
