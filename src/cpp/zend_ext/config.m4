AC_DEFUN([PATH_WITHOUT_EXT],[
dnl remove extension
	ac_obj=[$]{$1%.*} 
])

AC_DEFUN([PATH_REMORE_RELATIVE_PREFIX],[
dnl remove relative path prefix 
	ac_obj=[$]{$1#../}
])

AC_DEFUN([PHP_ADD_SOURCES_X],[
dnl relative to source- or build-directory?
dnl ac_srcdir/ac_bdir include trailing slash
case $1 in
  ""[)] ac_srcdir="$abs_srcdir/"; unset ac_bdir; ac_inc="-I. -I$abs_srcdir" ;;
  /*[)] ac_srcdir=`echo "$1"|cut -c 2-`"/"; ac_bdir=$ac_srcdir; ac_inc="-I$ac_bdir -I$abs_srcdir/$ac_bdir" ;;
  *[)] ac_srcdir="$abs_srcdir/$1/"; ac_bdir="$1/"; ac_inc="-I$ac_bdir -I$ac_srcdir" ;;
esac
  
dnl how to build .. shared or static?
  ifelse($5,yes,_PHP_ASSIGN_BUILD_VARS(shared),_PHP_ASSIGN_BUILD_VARS(php))

dnl iterate over the sources
  old_IFS=[$]IFS
  for ac_src in $2; do
  
dnl remove the suffix
dnl      IFS=.
dnl      set $ac_src
dnl      ac_obj=[$]1
dnl      IFS=$old_IFS
dnl
dnl      make ac_object
	PATH_WITHOUT_EXT(ac_src)
echo "-----ac_obj="$ac_obj
	PATH_REMORE_RELATIVE_PREFIX(ac_obj)
echo "-----ac_obj="$ac_obj
      

dnl choose the right compiler/flags/etc. for the source-file
      case $ac_src in
        *.c[)] ac_comp="$b_c_pre $3 $ac_inc $b_c_meta -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.$b_lo $6$b_c_post" ;;
        *.s[)] ac_comp="$b_c_pre $3 $ac_inc $b_c_meta -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.$b_lo $6$b_c_post" ;;
        *.S[)] ac_comp="$b_c_pre $3 $ac_inc $b_c_meta -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.$b_lo $6$b_c_post" ;;
        *.cpp|*.cc|*.cxx[)] ac_comp="$b_cxx_pre $3 $ac_inc $b_cxx_meta -c $ac_srcdir$ac_src -o $ac_bdir$ac_obj.$b_lo $6$b_cxx_post" ;;
      esac


dnl append to the array which has been dynamically chosen at m4 time
      $4="[$]$4 [$]ac_bdir[$]ac_obj.lo"

dnl create a rule for the object/source combo
    cat >>Makefile.objects<<EOF
$ac_bdir[$]ac_obj.lo: $ac_srcdir[$]ac_src
	$ac_comp
EOF
  done
])

PHP_ARG_ENABLE(git_repo_mod,
		[Whether to enable the "git_repo_mod" extension],
		[  --enable-git_repo_mod      Enable "git_repo_mod" extension support])


if test $PHP_GIT_REPO_MOD != "no"; then
	AC_PROG_CXX(clang++-3.5)
	AC_PROG_CPP(clang++-3.5)
	CC="clang++-3.5"
	CXXFLAGS="$CXXFLAGS -std=c++14"
	CXXFLAGS="$CXXFLAGS -I../git"
	CXXFLAGS="$CXXFLAGS -DLIB_GIT_HEADER=/var/libgit2/include/git2.h"
	PHP_REQUIRE_CXX()
	PHP_SUBST(GIT_REPO_MOD_SHARED_LIBADD)
	PHP_ADD_LIBRARY(stdc++, 1, GIT_REPO_MOD_SHARED_LIBADD)
	PHP_ADD_LIBRARY(git2,1,GIT_REPO_MOD_SHARED_LIBADD)
	PHP_NEW_EXTENSION(git_repo_mod,php_git_repo.cpp ../git/git_repo.cpp ../git/file_system.cpp,
		 $ext_shared)
fi
