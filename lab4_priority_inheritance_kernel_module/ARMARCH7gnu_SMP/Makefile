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

BUILD_SPEC = ARMARCH7gnu_SMP
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := /home.nfs/morhumyk/WindRiver
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/lab4_priority_inheritance_kernel_module



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = arm
CPU = ARMARCH7
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -fno-builtin -t7 -mfpu=vfp -mfloat-abi=softfp
VSB_DIR = $(WIND_BASE)/target/lib_smp
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 

IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler =  -O2 
DEBUGFLAGS_C++-Compiler =  -O2 
DEBUGFLAGS_Linker =  -O2 
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler =  -O2 
endif


#Project Targets
PROJECT_TARGETS = lab4_priority_inheritance_kernel_module/$(MODE_DIR)/lab4_priority_inheritance_kernel_module.out \
	 lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_partialImage.o \
	 zynq/$(MODE_DIR)/zynq.out


#Rules

# lab4_priority_inheritance_kernel_module
ifeq ($(DEBUG_MODE),1)
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -O2 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -O2 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -O2 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -O2 
endif
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : IDE_LIBRARIES = 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : PROJECT_TYPE = DKM
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : DEFINES = 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : EXPAND_DBG = 0
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : VX_CPU_FAMILY = arm
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : CPU = ARMARCH7
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : TOOL_FAMILY = gnu
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : TOOL = gnu
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : TOOL_PATH = 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : CC_ARCH_SPEC = -fno-builtin -t7 -mfpu=vfp -mfloat-abi=softfp
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib_smp
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : LIBPATH = 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : LIBS = 
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/% : OBJ_DIR := lab4_priority_inheritance_kernel_module/$(MODE_DIR)

OBJECTS_lab4_priority_inheritance_kernel_module = lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_partialImage.o

ifeq ($(TARGET_JOBS),1)
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/lab4_priority_inheritance_kernel_module.out : $(OBJECTS_lab4_priority_inheritance_kernel_module)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmarm $(OBJECTS_lab4_priority_inheritance_kernel_module) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c arm -tags $(VSB_DIR)/tags/arm/ARMARCH7/common/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall   $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccarm -r -nostdlib -Wl,-X -Wl,-EL -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_lab4_priority_inheritance_kernel_module) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/lab4_priority_inheritance_kernel_module.out : lab4_priority_inheritance_kernel_module/$(MODE_DIR)/lab4_priority_inheritance_kernel_module.out_jobs

endif
lab4_priority_inheritance_kernel_module/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_compile_file : $(FILE) ;

_clean :: lab4_priority_inheritance_kernel_module/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_clean

lab4_priority_inheritance_kernel_module/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_clean : 
	$(TRACE_FLAG)if [ -d "lab4_priority_inheritance_kernel_module" ]; then cd "lab4_priority_inheritance_kernel_module"; rm -rf $(MODE_DIR); fi


# lab4_priority_inheritance_kernel_module_partialImage
ifeq ($(DEBUG_MODE),1)
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -O2 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -O2 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -O2 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -O2 
endif
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : DEFINES = 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = arm
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : CPU = ARMARCH7
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = gnu
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : TOOL = gnu
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -fno-builtin -t7 -mfpu=vfp -mfloat-abi=softfp
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib_smp
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : LIBPATH = 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : LIBS = 
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/% : OBJ_DIR := lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)

lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/main.o : $(PRJ_ROOT_DIR)/main.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/utils.o : $(PRJ_ROOT_DIR)/utils.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


OBJECTS_lab4_priority_inheritance_kernel_module_partialImage = lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/main.o \
	 lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/utils.o

ifeq ($(TARGET_JOBS),1)
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_partialImage.o : $(OBJECTS_lab4_priority_inheritance_kernel_module_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm -r -nostdlib -Wl,-X -Wl,-EL  -o "$@" $(OBJECTS_lab4_priority_inheritance_kernel_module_partialImage) $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_partialImage.o : lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_partialImage.o_jobs

endif
lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_partialImage_compile_file : $(FILE) ;

_clean :: lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_partialImage_clean

lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/lab4_priority_inheritance_kernel_module_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "lab4_priority_inheritance_kernel_module_partialImage" ]; then cd "lab4_priority_inheritance_kernel_module_partialImage"; rm -rf $(MODE_DIR); fi


# zynq
ifeq ($(DEBUG_MODE),1)
zynq/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
zynq/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
zynq/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
zynq/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
zynq/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
zynq/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
zynq/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -O2 
zynq/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -O2 
zynq/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -O2 
zynq/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
zynq/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
zynq/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -O2 
endif
zynq/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
zynq/$(MODE_DIR)/% : IDE_LIBRARIES = 
zynq/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL -DARMEL  -DARM_USE_VFP -DARM_USE_VFP -DIP_PORT_VXWORKS=69 
zynq/$(MODE_DIR)/% : PROJECT_TYPE = DKM
zynq/$(MODE_DIR)/% : DEFINES = 
zynq/$(MODE_DIR)/% : EXPAND_DBG = 0
zynq/$(MODE_DIR)/% : VX_CPU_FAMILY = arm
zynq/$(MODE_DIR)/% : CPU = ARMARCH7
zynq/$(MODE_DIR)/% : TOOL_FAMILY = gnu
zynq/$(MODE_DIR)/% : TOOL = gnu
zynq/$(MODE_DIR)/% : TOOL_PATH = 
zynq/$(MODE_DIR)/% : CC_ARCH_SPEC = -fno-builtin -t7 -mfpu=vfp -mfloat-abi=softfp
zynq/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib_smp
zynq/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
zynq/$(MODE_DIR)/% : LIBPATH = 
zynq/$(MODE_DIR)/% : LIBS = 
zynq/$(MODE_DIR)/% : OBJ_DIR := zynq/$(MODE_DIR)

zynq/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/main.o : $(PRJ_ROOT_DIR)/main.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


zynq/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/utils.o : $(PRJ_ROOT_DIR)/utils.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -fno-zero-initialized-in-bss  -Wall    -MD -MP $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


OBJECTS_zynq = zynq/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/main.o \
	 zynq/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/utils.o

ifeq ($(TARGET_JOBS),1)
zynq/$(MODE_DIR)/zynq.out : $(OBJECTS_zynq)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmarm $(OBJECTS_zynq) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c arm -tags $(VSB_DIR)/tags/arm/ARMARCH7/common/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall   $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccarm -r -nostdlib -Wl,-X -Wl,-EL -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_zynq) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
zynq/$(MODE_DIR)/zynq.out : zynq/$(MODE_DIR)/zynq.out_jobs

endif
zynq/$(MODE_DIR)/zynq_compile_file : $(FILE) ;

_clean :: zynq/$(MODE_DIR)/zynq_clean

zynq/$(MODE_DIR)/zynq_clean : 
	$(TRACE_FLAG)if [ -d "zynq" ]; then cd "zynq"; rm -rf $(MODE_DIR); fi

force : 

TARGET_JOBS_RULE?=echo "Update the makefile template via File > Import > Build Settings : Update makefile template";exit 1
%_jobs : 
	$(TRACE_FLAG)$(TARGET_JOBS_RULE)

DEP_FILES := lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/main.d lab4_priority_inheritance_kernel_module_partialImage/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/utils.d zynq/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/main.d \
	 zynq/$(MODE_DIR)/Objects/lab4_priority_inheritance_kernel_module/utils.d
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
