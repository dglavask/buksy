#ifndef GIT_REPO_H
#define GIT_REPO_H

#include <string>
#include "file_system.h"
#include "incl_git2.h"
#include <exception>


class file_system;

class git_repo:public file_system{
public:
	git_repo(std::string);
	~git_repo();
private:
	bool checkForRepo(std::string);
	bool init(std::string);
	void log(std::string);
	git_repository* repo;
};

class git_exception:public std::exception{
public:
	git_exception(std::string);
	const char* what()const noexcept;
private:
	std::string message;
}; 

#endif
