# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

JOBS?=1
TARGET_JOBS?=$(JOBS)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = SIMLINUXgnu
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := /home.nfs/morhumyk/WindRiver/workspace_new
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/test_project



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = simlinux
CPU = SIMLINUX
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mtune=i486 -march=i486 -nostdlib -fno-builtin
VSB_DIR = $(WIND_BASE)/target/lib
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 

IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   -DIP_PORT_VXWORKS=69 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler =  -O2  -fno-defer-pop
DEBUGFLAGS_C++-Compiler =  -O2  -fno-defer-pop
DEBUGFLAGS_Linker =  -O2  -fno-defer-pop
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler =  -O2  -fno-defer-pop
endif


#Project Targets
PROJECT_TARGETS = test_project/$(MODE_DIR)/test_project.out \
	 test_project_partialImage/$(MODE_DIR)/test_project_partialImage.o


#Rules

# test_project
ifeq ($(DEBUG_MODE),1)
test_project/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
test_project/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
test_project/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
test_project/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
test_project/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
test_project/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
test_project/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -O2  -fno-defer-pop
test_project/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -O2  -fno-defer-pop
test_project/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -O2  -fno-defer-pop
test_project/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
test_project/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
test_project/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -O2  -fno-defer-pop
endif
test_project/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
test_project/$(MODE_DIR)/% : IDE_LIBRARIES = 
test_project/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   -DIP_PORT_VXWORKS=69 
test_project/$(MODE_DIR)/% : PROJECT_TYPE = DKM
test_project/$(MODE_DIR)/% : DEFINES = 
test_project/$(MODE_DIR)/% : EXPAND_DBG = 0
test_project/$(MODE_DIR)/% : VX_CPU_FAMILY = simlinux
test_project/$(MODE_DIR)/% : CPU = SIMLINUX
test_project/$(MODE_DIR)/% : TOOL_FAMILY = gnu
test_project/$(MODE_DIR)/% : TOOL = gnu
test_project/$(MODE_DIR)/% : TOOL_PATH = 
test_project/$(MODE_DIR)/% : CC_ARCH_SPEC = -mtune=i486 -march=i486 -nostdlib -fno-builtin
test_project/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
test_project/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
test_project/$(MODE_DIR)/% : LIBPATH = 
test_project/$(MODE_DIR)/% : LIBS = 
test_project/$(MODE_DIR)/% : OBJ_DIR := test_project/$(MODE_DIR)

OBJECTS_test_project = test_project_partialImage/$(MODE_DIR)/test_project_partialImage.o

ifeq ($(TARGET_JOBS),1)
test_project/$(MODE_DIR)/test_project.out : $(OBJECTS_test_project)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmpentium $(OBJECTS_test_project) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c pentium -tags $(VSB_DIR)/tags/simlinux/SIMLINUX/common/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall   $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccpentium -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_test_project) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
test_project/$(MODE_DIR)/test_project.out : test_project/$(MODE_DIR)/test_project.out_jobs

endif
test_project/$(MODE_DIR)/test_project_compile_file : $(FILE) ;

_clean :: test_project/$(MODE_DIR)/test_project_clean

test_project/$(MODE_DIR)/test_project_clean : 
	$(TRACE_FLAG)if [ -d "test_project" ]; then cd "test_project"; rm -rf $(MODE_DIR); fi


# test_project_partialImage
ifeq ($(DEBUG_MODE),1)
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -O2  -fno-defer-pop
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -O2  -fno-defer-pop
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -O2  -fno-defer-pop
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
test_project_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -O2  -fno-defer-pop
endif
test_project_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
test_project_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
test_project_partialImage/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   -DIP_PORT_VXWORKS=69 
test_project_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
test_project_partialImage/$(MODE_DIR)/% : DEFINES = 
test_project_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
test_project_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = simlinux
test_project_partialImage/$(MODE_DIR)/% : CPU = SIMLINUX
test_project_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = gnu
test_project_partialImage/$(MODE_DIR)/% : TOOL = gnu
test_project_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
test_project_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -mtune=i486 -march=i486 -nostdlib -fno-builtin
test_project_partialImage/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
test_project_partialImage/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
test_project_partialImage/$(MODE_DIR)/% : LIBPATH = 
test_project_partialImage/$(MODE_DIR)/% : LIBS = 
test_project_partialImage/$(MODE_DIR)/% : OBJ_DIR := test_project_partialImage/$(MODE_DIR)

test_project_partialImage/$(MODE_DIR)/Objects/test_project/test.o : $(PRJ_ROOT_DIR)/test.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


OBJECTS_test_project_partialImage = test_project_partialImage/$(MODE_DIR)/Objects/test_project/test.o

ifeq ($(TARGET_JOBS),1)
test_project_partialImage/$(MODE_DIR)/test_project_partialImage.o : $(OBJECTS_test_project_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccpentium -r -nostdlib -Wl,-X  -o "$@" $(OBJECTS_test_project_partialImage) $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
test_project_partialImage/$(MODE_DIR)/test_project_partialImage.o : test_project_partialImage/$(MODE_DIR)/test_project_partialImage.o_jobs

endif
test_project_partialImage/$(MODE_DIR)/test_project_partialImage_compile_file : $(FILE) ;

_clean :: test_project_partialImage/$(MODE_DIR)/test_project_partialImage_clean

test_project_partialImage/$(MODE_DIR)/test_project_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "test_project_partialImage" ]; then cd "test_project_partialImage"; rm -rf $(MODE_DIR); fi

force : 

TARGET_JOBS_RULE?=echo "Update the makefile template via File > Import > Build Settings : Update makefile template";exit 1
%_jobs : 
	$(TRACE_FLAG)$(TARGET_JOBS_RULE)

DEP_FILES := test_project_partialImage/$(MODE_DIR)/Objects/test_project/test.d
-include $(DEP_FILES)


WIND_SCOPETOOLS_BASE := $(subst \,/,$(WIND_SCOPETOOLS_BASE))

clean_scopetools :
	$(TRACE_FLAG)rm -rf $(PRJ_ROOT_DIR)/.coveragescope/db

CLEAN_STEP := clean_scopetools


-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

TARGET_JOBS_RULE=$(MAKE) -f $(MAKEFILE) --jobs $(TARGET_JOBS) $(MFLAGS) $* TARGET_JOBS=1
ifeq ($(JOBS),1)
main_all : external_build  $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"
else
main_all : external_build 
	@$(MAKE) -f $(MAKEFILE) --jobs $(JOBS) $(MFLAGS) $(PROJECT_TARGETS) TARGET_JOBS=1 &&\
	echo "make: built targets of `pwd`"
endif 

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
