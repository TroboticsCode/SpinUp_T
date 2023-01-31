# VEXcode makefile 2019_03_26_01

# show compiler output
VERBOSE = 0

# include toolchain options
include vex/mkenv.mk

# location of the project source cpp and c files
SRC_C  = $(wildcard src/*.cpp) 
SRC_C += $(wildcard src/*.c)
SRC_C += $(wildcard src/*/*.cpp) 
SRC_C += $(wildcard src/*/*.c)
SRC_C += $(wildcard Graphing/*.c) 
SRC_C += $(wildcard Graphing/*/*/*/*.c) 

OBJ = $(addprefix $(BUILD)/, $(addsuffix .o, $(basename $(SRC_C))) )

# location of include files that c and cpp files depend on
SRC_H  = $(wildcard include/*.h)
SRC_H  += $(wildcard Graphing/*.h)
SRC_H  += $(wildcard Graphing/lvgl/*.h)
SRC_H  += $(wildcard Graphing/*.c)

# additional dependancies
SRC_A  = makefile

# project header file locations
INC_F  = include . lvgl lvgl/src Graphing/lvgl Graphing/

# headers needed to use library
LV_SRC_H = $(wildcard Graphing/lvgl/*.h) 
LV_SRC_H += $(wildcard Graphing/lvgl/src/*.h) 
LV_SRC_H += $(wildcard Graphing/lvgl/src/*/*.h)
LV_SRC_H += $(wildcard Graphing/*.h)

LV_DST_H = $(addprefix $(BUILD)/include/, $(LV_SRC_H) )
#LV_DST_H += $(BUILD)/Graphing/lv_conf.h $(BUILD)/Graphing/v5lvgl.h


$(BUILD)/include/%: %
	$(Q)$(MKDIR)
	$(Q) $(call copyfile,$^, $@)

vpath %.h Graphing/ lvgl/ include/

# override default library name
PROJECTLIB = libv5lvgl

# build targets
all: $(BUILD)/$(PROJECT).bin $(BUILD)/$(PROJECTLIB).a inc

# copy lvgl header files
.PHONY: inc
inc: $(LV_DST_H)
	$(ECHO) "Copy headers to build folder"

# include build rules
include vex/mkrules.mk
