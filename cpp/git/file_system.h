#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include <string>
#include <exception>


class file_system{
public:
	file_system(std::string);
	file_system();
	virtual ~file_system();
	bool dirExists(std::string);
	bool createDir(std::string);
	bool deleteDir(std::string);
	std::string getWorkingDir();

private:
	bool createDirNoCheck(std::string);
	std::string working_dir_;
	std::string getWorkingDir_();
	void throwErrno();
};

class collision_exception: public std::exception{
public:
	collision_exception(std::string);
	const char* what()const noexcept;
private:
	std::string message;
};



#endif
