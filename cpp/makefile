include gmsl 
	     #sudo apt-get install gmsl on linux
SHELL = /bin/sh

include make.conf

ifdef exp
	override macro_vars += $(call uc,$(exp)) EXPERIMENT
	srcs += $(experimental_dir)/$(exp)E.cpp
endif
src_dir:=$(sort $(dir $(srcs)))

VPATH+=$(subst ' ',:,$(src_dir))
include_dir_flag:= $(src_dir:%=-I%)
odat = $(srcs:%.cpp=$(build_dir)/%.o)
odirs = $(src_dir:%=$(build_dir)/%) 
mflags = $(macro_vars:%=-D%)
dflags := $(CXXFLAGS) $(cpp_version) $(include_dir_flag)
lib_dirs_include := $(lib_dirs:%=-L%)
static_lib_linking := $(static_libs:%=-l%)
lib_flags:= $(lib_dirs_include) $(static_lib_linking)

override CXXFLAGS += $(include_dir_flag) $(mflags) $(cpp_version) $(default_options)


$(program_name) : compilation
	@echo linkam u program: $@
	$(CXX) $(lib_flags) $(CXXFLAGS) -o $@ $(odat) 

compilation : $(odat)

.PHONY : opti
opti : opti_opt $(program_name)

opti_opt : FORCE
	@echo optimisation -O2
	$(eval default_options:=-O2)

FORCE:

ifneq ($(MAKECMDGOALS),clean)
include $(srcs:%.cpp=$(build_dir)/%.d)
endif

$(build_dir)/%.o : %.cpp 
	@echo compiling $<
	$(CXX) -c $(CXXFLAGS) -o $@ $<;


$(build_dir) : 
	@echo creating root build dir: $@	
	mkdir $@;

$(odirs) : | $(build_dir)
	@echo creating build dir: $@	
	mkdir $@;


$(build_dir)/%.d : %.cpp | $(build_dir) $(odirs)
	$(eval tmp_put=$(subst /,\/,$*))
	@echo regenerating .d file $@
	@set -e; rm -f $@; \
	$(CXX) -MM $(dflags) $< > $@.$$$$; \
	sed 's@\($(*F)\)\.o[ :]*@$(@D)/\1.o $@ : @g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


.PHONY: clean
clean:
	rm -fR $(build_dir)
#endif
