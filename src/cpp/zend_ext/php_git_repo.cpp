#include "git_repo.h"
#include "php_git_repo.h"

#include <string>
#include <system_error>

extern "C"{
#include "zend_exceptions.h"
}
zend_object_handlers git_repo_objet_handlers;

struct git_repo_object{
	zend_object std;
	git_repo* repo;
};

zend_class_entry* repo_ce;

void git_repo_free_storage(void* object TSRMLS_DC){
	
	git_repo_object* obj = (git_repo_object*)object;
	delete obj->repo;

	zend_hash_destroy(obj->std.properties);
	FREE_HASHTABLE(obj->std.properties);
	efree(obj);
}

zend_object_value git_repo_create_handler(zend_class_entry* type TSRMLS_DC){
	
	zval* tmp;
	zend_object_value return_;

	git_repo_object* obj =(git_repo_object*)emalloc(sizeof(git_repo_object));
	memset(obj,0,sizeof(git_repo_object));	
	obj->std.ce = type;

	ALLOC_HASHTABLE(obj->std.properties);
	zend_hash_init(obj->std.properties,0,NULL,ZVAL_PTR_DTOR,0);
	zend_hash_copy(obj->std.properties, &type->properties_info,
			(copy_ctor_func_t)zval_add_ref, (void*)&tmp, sizeof(zval*));

	return_.handle = zend_objects_store_put(obj,NULL,git_repo_free_storage,NULL TSRMLS_CC);
	return_.handlers = &git_repo_objet_handlers;

	return return_;
}

PHP_METHOD(git_repo, __construct){
	
	char* repo_path;
	int path_size;
	git_repo* repo = nullptr;
	zval* this_ = getThis();
	
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", 
			       &repo_path, &path_size) == FAILURE){
		RETURN_NULL();
	}	
	try{
		repo = new git_repo(std::string(repo_path));	
		git_repo_object* obj = (git_repo_object*)zend_object_store_get_object(this_ TSRMLS_CC);
		obj->repo = repo;
	}catch(std::system_error &e){
		zend_throw_exception(zend_exception_get_default(), e.what(),e.code().value() TSRMLS_DC);
	}catch(git_exception &e){
		zend_throw_exception(zend_exception_get_default(), e.what(),0 TSRMLS_DC);
	}
}


zend_function_entry git_repo_methods[] = {
	PHP_ME(git_repo, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	{NULL,NULL,NULL}
};



PHP_MINIT_FUNCTION(git_repo_mod){

	zend_class_entry zc;
	INIT_CLASS_ENTRY(zc, "git_repo", git_repo_methods);
	repo_ce = zend_register_internal_class(&zc TSRMLS_CC);
	repo_ce->create_object = git_repo_create_handler;
	memcpy(&git_repo_objet_handlers, zend_get_std_object_handlers(),sizeof(zend_object_handlers));	
	git_repo_objet_handlers.clone_obj = NULL;
	return SUCCESS;
}


zend_module_entry git_repo_mod_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_GIT_REPO_MOD_EXTNAME,
	NULL,                  /* Functions */
	PHP_MINIT(git_repo_mod),   /*MINIT*/
	NULL,                  /* MSHUTDOWN */
	NULL,                  /* RINIT */
	NULL,                  /* RSHUTDOWN */
	NULL,                  /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
	PHP_GIT_REPO_MOD_EXTVER,
#endif
	STANDARD_MODULE_PROPERTIES
};
#ifdef COMPILE_DL_GIT_REPO_MOD
extern "C" {
	ZEND_GET_MODULE(git_repo_mod)
}
#endif



