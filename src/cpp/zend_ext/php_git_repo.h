#ifndef PHP_GIT_REPO_H
#define PHP_GIT_REPO_H

#define PHP_GIT_REPO_MOD_EXTNAME "git_repo_mod"
#define PHP_GIT_REPO_MOD_EXTVER	 "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C"{
#include "php.h"
}

extern  zend_module_entry git_repo_mod_module_entry;
#define phpext_git_repo_mod_ptr &git_repo_mod_module_entry;

#endif
