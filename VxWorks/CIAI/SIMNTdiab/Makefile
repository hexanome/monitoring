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

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = SIMNTdiab
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
PRJ_ROOT_DIR := C:/Documents\ and\ Settings/Administrateur/vxworks/monitoring/VxWorks/CIAI
WS_ROOT_DIR := C:/Documents\ and\ Settings/Administrateur/vxworks



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = simpc
CPU = SIMNT
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tX86LH:vxworks67
VSB_DIR = $(WIND_BASE)/target/lib
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
DEBUGFLAGS_Linker = -XO -Xsize-opt
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif


#Project Targets
PROJECT_TARGETS = CIAI/$(MODE_DIR)/CIAI.out \
	 CIAI_partialImage/$(MODE_DIR)/CIAI_partialImage.o


#Rules

# CIAI
ifeq ($(DEBUG_MODE),1)
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CIAI/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
CIAI/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
CIAI/$(MODE_DIR)/% : IDE_LIBRARIES = 
CIAI/$(MODE_DIR)/% : PROJECT_TYPE = DKM
CIAI/$(MODE_DIR)/% : DEFINES = 
CIAI/$(MODE_DIR)/% : EXPAND_DBG = 0
CIAI/$(MODE_DIR)/% : VX_CPU_FAMILY = simpc
CIAI/$(MODE_DIR)/% : CPU = SIMNT
CIAI/$(MODE_DIR)/% : TOOL_FAMILY = diab
CIAI/$(MODE_DIR)/% : TOOL = diab
CIAI/$(MODE_DIR)/% : TOOL_PATH = 
CIAI/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks67
CIAI/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
CIAI/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
CIAI/$(MODE_DIR)/% : LIBPATH = 
CIAI/$(MODE_DIR)/% : LIBS = 
CIAI/$(MODE_DIR)/% : OBJ_DIR := CIAI/$(MODE_DIR)

OBJECTS_CIAI = CIAI_partialImage/$(MODE_DIR)/CIAI_partialImage.o

CIAI/$(MODE_DIR)/CIAI.out : $(OBJECTS_CIAI)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";ddump -Ng $(OBJECTS_CIAI) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c pentium > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -Xforce-declarations  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dld -tX86LH:vxworks67 -X -r5 -f 0x90,1,1 -r4 -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_CIAI) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

CIAI/$(MODE_DIR)/CIAI_compile_file : $(FILE) ;

_clean :: CIAI/$(MODE_DIR)/CIAI_clean

CIAI/$(MODE_DIR)/CIAI_clean : 
	$(TRACE_FLAG)if [ -d "CIAI" ]; then cd "CIAI"; rm -rf $(MODE_DIR); fi


# CIAI_partialImage
ifeq ($(DEBUG_MODE),1)
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -XO -Xsize-opt
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -XO -Xsize-opt
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -XO -Xsize-opt
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
CIAI_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -XO -Xsize-opt
endif
CIAI_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
CIAI_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = 
CIAI_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
CIAI_partialImage/$(MODE_DIR)/% : DEFINES = 
CIAI_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
CIAI_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = simpc
CIAI_partialImage/$(MODE_DIR)/% : CPU = SIMNT
CIAI_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = diab
CIAI_partialImage/$(MODE_DIR)/% : TOOL = diab
CIAI_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
CIAI_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -tX86LH:vxworks67
CIAI_partialImage/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib
CIAI_partialImage/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
CIAI_partialImage/$(MODE_DIR)/% : LIBPATH = 
CIAI_partialImage/$(MODE_DIR)/% : LIBS = 
CIAI_partialImage/$(MODE_DIR)/% : OBJ_DIR := CIAI_partialImage/$(MODE_DIR)

CIAI_partialImage/$(MODE_DIR)/Objects/CIAI/write.o : C:/Documents\ and\ Settings/Administrateur/vxworks/monitoring/VxWorks/CIAI/write.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -Xforce-declarations   -Xmake-dependency=0xd $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL  -D_VSB_CONFIG_FILE=\"$(VSB_CONFIG_FILE)\"   $(DEFINES) -o "$@" -c "$<"


OBJECTS_CIAI_partialImage = CIAI_partialImage/$(MODE_DIR)/Objects/CIAI/write.o

CIAI_partialImage/$(MODE_DIR)/CIAI_partialImage.o : $(OBJECTS_CIAI_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dld -tX86LH:vxworks67 -X -r5 -f 0x90,1,1  -o "$@" $(OBJECTS_CIAI_partialImage) $(ADDED_OBJECTS) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

CIAI_partialImage/$(MODE_DIR)/CIAI_partialImage_compile_file : $(FILE) ;

_clean :: CIAI_partialImage/$(MODE_DIR)/CIAI_partialImage_clean

CIAI_partialImage/$(MODE_DIR)/CIAI_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "CIAI_partialImage" ]; then cd "CIAI_partialImage"; rm -rf $(MODE_DIR); fi

DEP_FILES := CIAI_partialImage/$(MODE_DIR)/Objects/CIAI/write.d
-include $(DEP_FILES)



-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

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
