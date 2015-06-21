#include "git_repo.h"
#include "incl_git2.h"


git_repo::git_repo(std::string name){
	git_libgit2_init();

}

git_repo::~git_repo(){
	git_libgit2_shutdown();

}
