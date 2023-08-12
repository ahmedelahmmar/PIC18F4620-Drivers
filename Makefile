COMPILER := /mnt/c/Program\ Files/Microchip/xc8/v2.41/bin/xc8-cc.exe
COMPILER_FLAGS := -O0 -std=c99 -fasmfile -mcpu=18f4620 -mdebugger=none -memi=wordwrite -maddrqual=ignore -mdfp=C:\\Program\ Files\\Microchip\\MPLABX\\v6.10\\packs\\Microchip\\PIC18Fxxxx_DFP\\1.4.151\\xc8 -msummary=-psect,-class,+mem,-hex,-file -mstack=compiled:auto:auto:auto -mno-default-config-bits -mwarn=0 -gcoff -ginhx32 -Wa,-a -Wl,--data-init -fno-short-double -fno-short-float

TARGET_FILENAME := pic18f4620

SRC_DIRS := MCAL ECUAL APP
SRC_FILES :=  $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c)) $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/**/*.c))

OBJ_DIR := build
OBJ_FILES := $(patsubst %.c, $(OBJ_DIR)/%.p1, $(SRC_FILES))
OBJ_SUBDIRS := $(sort $(dir $(OBJ_FILES)))

define sort_dirs_by_depth
$(shell for dir in $(1); do echo "$$dir $$(echo $$dir | tr -cd '/' | wc -c)"; done | sort -k2 -t' ' -n | cut -d' ' -f1)
endef
SORTED_OBJ_SUBDIRS := $(call sort_dirs_by_depth,$(OBJ_SUBDIRS))

EXECUTABLE := $(OBJ_DIR)/$(TARGET_FILENAME)

.PHONY: all
all: build

.PHONY: build
build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES) | $(OBJ_DIR)
	$(COMPILER) $(COMPILER_FLAGS) $^ -o $@

$(OBJ_DIR)/%.p1: %.c | $(OBJ_DIR)
	$(COMPILER) $(COMPILER_FLAGS) -c $< -o $@

.PHONY: create_build_directories 
create_build_directories:
	@for dir in $(SORTED_OBJ_SUBDIRS); do \
		mkdir -p $$dir; \
	done

.PHONY: clean 
clean:
	@find $(OBJ_DIR) -type f -exec rm -f {} +