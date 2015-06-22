#include "file_system.h"
#include <cerrno>
#include <system_error>
#include <climits>
#include <iostream>

extern "C"{
	#include <sys/stat.h>
	#include <sys/unistd.h>
}

typedef struct stat path_info;

file_system::file_system(){
	working_dir_ = getWorkingDir_();
}

file_system::file_system(std::string working_dir){
	if(working_dir.empty()){
		file_system();
	}else{
		int i = working_dir.compare(0,1,"/");
		int j = working_dir.compare(0,2,"~/"); // conversion to absolute path required
		if(i == 0){ 
			working_dir_ = working_dir; 
		}else{ 
			working_dir_ = getWorkingDir_()+ "/" + working_dir;	
		}
		createDir(working_dir_);		
	}

} 

file_system::~file_system(){
}

std::string file_system::getWorkingDir_(){
	char path[PATH_MAX];
       	if(!getcwd(path,PATH_MAX)){
		throwErrno();
	} 	
	std::string rp(path);
	return rp;
}

std::string file_system::getWorkingDir(){
	return working_dir_;
}

bool file_system::dirExists(std::string path){
	path_info pi;	
	if(stat(path.c_str(),&pi)){
		if(errno == ENOENT){
			return false;
		}else{
			throwErrno();
		}
	}
	if(S_ISDIR(pi.st_mode)){
		return true;
	}else{
		throw collision_exception(path); 
	}
}

void file_system::throwErrno(){
		throw std::system_error(std::error_code(errno,std::system_category()));  	
}

bool file_system::createDir(std::string path){
	if(!dirExists(path)){
		return createDirNoCheck(path);
		
	}
	return false;
}

bool file_system::createDirNoCheck(std::string path){
	if(0!=mkdir(path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)){
		if(errno == EEXIST){
			return false;
		}else{
			throwErrno();
		}
	}
	return true;
}

bool file_system::deleteDir(std::string path){
	return true;
}

collision_exception::collision_exception(std::string cause){
	message = cause;
}

const char* collision_exception::what()const noexcept{
	return message.c_str();
}

