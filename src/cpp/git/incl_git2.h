#ifndef INCL_GIT2_H
#define INCL_GIT2_H
#define TS(A) # A
#define STRING(A) TS(A)
extern "C" {
#ifdef LIB_GIT_HEADER
	#include STRING(LIB_GIT_HEADER)
#endif
}
#endif
