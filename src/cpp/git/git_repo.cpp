#include "git_repo.h"
#include "incl_git2.h"
#include "file_system.h"
#include <iostream>

extern "C"{
	#include <sys/stat.h>
}

git_repo::git_repo(std::string name):file_system(name),repo(nullptr)
{	
	git_libgit2_init();
	if(!checkForRepo(name)){
		log("creating repository "+name);
		init(name);
	}
	log("loading repository " + name);
}

bool git_repo::checkForRepo(std::string path){
	int c = ::git_repository_open_ext(nullptr, path.c_str(), ::GIT_REPOSITORY_OPEN_NO_SEARCH,nullptr);
	if(c == 0){
		return true;	
	}
	return false;
}

bool git_repo::init(std::string path){
	int e = git_repository_init(&repo,path.c_str(),0);
	if (e != GIT_OK){
		const git_error* er = ::giterr_last();
		std::string full_error_message = "error number " + std::to_string(er->klass) + " message: " + er->message;
		throw git_exception(full_error_message);
	}
	return true;
}

git_repo::~git_repo(){
	git_repository_free(repo);
	git_libgit2_shutdown();

}

void git_repo::log(std::string message){
	std::cout<<message<<std::endl;
}

git_exception::git_exception(std::string cause){
	message = cause;
}

const char* git_exception::what()const noexcept{
	return message.c_str();
}

