#include "git_repo.h"
#include "file_system.h"
#include <iostream>
#include <exception>

int main(){

	try{
		git_repo rep("ja");
	}catch(std::exception &e){
		std::cout<< e.what() <<std::endl;

	}
	//file_system fs("ja");
	//fs.dirExists("ja");
	//file_system fs2("ja/bla");
	//file_system fs3("/ja");
	//std::cout<<fs.getWorkingDir()<<std::endl;
	//std::cout<<fs2.getWorkingDir()<<std::endl;
	//std::cout<<fs3.getWorkingDir()<<std::endl;

	return 0;

}

