#include "git_repo.h"
#include <iostream>
#include <exception>

int main(){

	try{
		//reate repo if it doesnt exist and initialize it as bare
		git_repo rep("ja");
	}catch(std::exception &e){
		std::cout<< e.what() <<std::endl;

	}

	return 0;

}

