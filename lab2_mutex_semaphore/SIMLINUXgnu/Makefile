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
WS_ROOT_DIR := /home.nfs/morhumyk/WindRiver
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/lab2_mutex_semaphore



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
PROJECT_TARGETS = lab2_mutex_semaphore/$(MODE_DIR)/lab2_mutex_semaphore.out \
	 lab2_mutex_semaphore_partialImage/$(MODE_DIR)/lab2_mutex_semaphore_partialImage.o


#Rules

# lab2_mutex_semaphore
ifeq ($(DEBUG_MODE),1)
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -O2  -fno-defer-pop
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -O2  -fno-defer-pop
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -O2  -fno-defer-pop
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
lab2_mutex_semaphore/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -O2  -fno-defer-pop
endif
lab2_mutex_semaphore/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
lab2_mutex_semaphore/$(MODE_DIR)/% : IDE_LIBRARIES = 
lab2_mutex_semaphore/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   -DIP_PORT_VXWORKS=69 
lab2_mutex_semaphore/$(MODE_DIR)/% : PROJECT_TYPE = DKM
lab2_mutex_semaphore/$(MODE_DIR)/% : DEFINES = 
lab2_mutex_semaphore/$(MODE_DIR)/% : EXPAND_DBG = 0
lab2_mutex_semaphore/$(MODE_DIR)/% : VX_CPU_FAMILY = simlinux
lab2_mutex_semaphore/$(MODE_DIR)/% : CPU = SIMLINUX
lab2_mutex_semaphore/$(MODE_DIR)/% : TOOL_FAMILY = gnu
lab2_mutex_semaphore/$(MODE_DIR)/% : TOOL = gnu
lab2_mutex_semaphore/$(MODE_DIR)/% : TOOL_PATH = 
lab2_mutex_semaphore/$(MODE_DIR)/% : CC_ARCH_SPEC = -mtune=i486 -march=i486 -nostdlib -fno-builtin
lab2_mutex_semaphore/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
lab2_mutex_semaphore/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
lab2_mutex_semaphore/$(MODE_DIR)/% : LIBPATH = 
lab2_mutex_semaphore/$(MODE_DIR)/% : LIBS = 
lab2_mutex_semaphore/$(MODE_DIR)/% : OBJ_DIR := lab2_mutex_semaphore/$(MODE_DIR)

OBJECTS_lab2_mutex_semaphore = lab2_mutex_semaphore_partialImage/$(MODE_DIR)/lab2_mutex_semaphore_partialImage.o

ifeq ($(TARGET_JOBS),1)
lab2_mutex_semaphore/$(MODE_DIR)/lab2_mutex_semaphore.out : $(OBJECTS_lab2_mutex_semaphore)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmpentium $(OBJECTS_lab2_mutex_semaphore) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c pentium -tags $(VSB_DIR)/tags/simlinux/SIMLINUX/common/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall   $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccpentium -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_lab2_mutex_semaphore) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
lab2_mutex_semaphore/$(MODE_DIR)/lab2_mutex_semaphore.out : lab2_mutex_semaphore/$(MODE_DIR)/lab2_mutex_semaphore.out_jobs

endif
lab2_mutex_semaphore/$(MODE_DIR)/lab2_mutex_semaphore_compile_file : $(FILE) ;

_clean :: lab2_mutex_semaphore/$(MODE_DIR)/lab2_mutex_semaphore_clean

lab2_mutex_semaphore/$(MODE_DIR)/lab2_mutex_semaphore_clean : 
	$(TRACE_FLAG)if [ -d "lab2_mutex_semaphore" ]; then cd "lab2_mutex_semaphore"; rm -rf $(MODE_DIR); fi


# lab2_mutex_semaphore_partialImage
ifeq ($(DEBUG_MODE),1)
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -O2  -fno-defer-pop
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -O2  -fno-defer-pop
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -O2  -fno-defer-pop
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -O2  -fno-defer-pop
endif
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   -DIP_PORT_VXWORKS=69 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : DEFINES = 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = simlinux
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : CPU = SIMLINUX
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = gnu
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : TOOL = gnu
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -mtune=i486 -march=i486 -nostdlib -fno-builtin
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : LIBPATH = 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : LIBS = 
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/% : OBJ_DIR := lab2_mutex_semaphore_partialImage/$(MODE_DIR)

lab2_mutex_semaphore_partialImage/$(MODE_DIR)/Objects/lab2_mutex_semaphore/task2.o : $(PRJ_ROOT_DIR)/task2.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


OBJECTS_lab2_mutex_semaphore_partialImage = lab2_mutex_semaphore_partialImage/$(MODE_DIR)/Objects/lab2_mutex_semaphore/task2.o

ifeq ($(TARGET_JOBS),1)
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/lab2_mutex_semaphore_partialImage.o : $(OBJECTS_lab2_mutex_semaphore_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccpentium -r -nostdlib -Wl,-X  -o "$@" $(OBJECTS_lab2_mutex_semaphore_partialImage) $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/lab2_mutex_semaphore_partialImage.o : lab2_mutex_semaphore_partialImage/$(MODE_DIR)/lab2_mutex_semaphore_partialImage.o_jobs

endif
lab2_mutex_semaphore_partialImage/$(MODE_DIR)/lab2_mutex_semaphore_partialImage_compile_file : $(FILE) ;

_clean :: lab2_mutex_semaphore_partialImage/$(MODE_DIR)/lab2_mutex_semaphore_partialImage_clean

lab2_mutex_semaphore_partialImage/$(MODE_DIR)/lab2_mutex_semaphore_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "lab2_mutex_semaphore_partialImage" ]; then cd "lab2_mutex_semaphore_partialImage"; rm -rf $(MODE_DIR); fi

force : 

TARGET_JOBS_RULE?=echo "Update the makefile template via File > Import > Build Settings : Update makefile template";exit 1
%_jobs : 
	$(TRACE_FLAG)$(TARGET_JOBS_RULE)

DEP_FILES := lab2_mutex_semaphore_partialImage/$(MODE_DIR)/Objects/lab2_mutex_semaphore/task2.d
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
