
# name of your application
APPLICATION = ble_test

# If no BOARD is found in the environment, use this default:
BOARD = seeeduino_xiao-nRF52840

# This has to be the absolute path to the RIOT base directory:
RIOTBASE := $(CURDIR)/../../../RIOT
LADYBUGDIR := $(CURDIR)/../../../ladybug
EXTERNAL_BOARD_DIRS += $(LADYBUGDIR)/boards
EXTERNAL_MODULE_DIRS += $(LADYBUGDIR)/modules

# Bluetooth device info
# Passed through via ladybug_ble.h
CFLAGS += -DCONFIG_NIMBLE_AUTOADV_DEVICE_NAME='"Openshutter Ladybug v0.1"'
CFLAGS += -DCONFIG_DEVINFO_MANUFACTURER_NAME='"Openshutter"'
CFLAGS += -DCONFIG_DEVINFO_MODEL_NUMBER='"Ladybug"'
CFLAGS += -DCONFIG_DEVINFO_SERIAL_NUMBER='"0001-A"'
CFLAGS += -DCONFIG_DEVINFO_FW_VER='"v0.1"'
CFLAGS += -DCONFIG_DEVINFO_HW_VER='"v0.1"'

# Uncomment these lines if you want to use platform support from external
# repositories:
#RIOTCPU ?= $(CURDIR)/../../RIOT/thirdparty_cpu
#EXTERNAL_BOARD_DIRS ?= $(CURDIR)/../../RIOT/thirdparty_boards

# Uncomment this to enable scheduler statistics for ps:
#USEMODULE += schedstatistics

# If you want to use native with valgrind, you should recompile native
# with the target all-valgrind instead of all:
# make -B clean all-valgrind

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# hardware specific
USEMODULE += seeeduino_xiao-nRF52840_battery

# Modules to include:
USEMODULE += shell
USEMODULE += shell_cmds_default
USEMODULE += ps
USEMODULE += random
# include and auto-initialize all available sensors
USEMODULE += saul_default


# shell test commands
USEMODULE += shell_gpio
USEMODULE += shell_adc
USEMODULE += shell_discomode

# ladybug software
USEMODULE += ladybug_ble
USEMODULE += ladybug_triggers

# we're using cpp in a few spots
FEATURES_REQUIRED += cpp

# required for ztimer to work
# it should pull this in on its own
FEATURES_REQUIRED += periph_rtt
FEATURES_REQUIRED += periph_timer

# Use automated advertising
USEMODULE += nimble_autoadv
CFLAGS += -DCONFIG_NIMBLE_AUTOADV_START_MANUALLY=1

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk
