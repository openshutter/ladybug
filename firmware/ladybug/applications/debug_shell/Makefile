
# name of your application
APPLICATION = gpio_debug_shell

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
# RIOTBASE ?= $(CURDIR)/../../../RIOT
# EXTERNAL_BOARD_DIRS ?= $(CURDIR)/../../../ladybug/boards
# EXTERNAL_MODULE_DIRS ?= $(CURDIR)/../../../ladybug/modules

BOARD=seeeduino_xiao-nRF52840
EXTERNAL_BOARD_DIRS=/home/epers/repos/shutterbug/ladybug/firmware/ladybug/boards
EXTERNAL_MODULE_DIRS=/home/epers/repos/shutterbug/ladybug/firmware/ladybug/modules
RIOTBASE=/home/epers/repos/shutterbug/ladybug/firmware/RIOT


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

FEATURES_REQUIRED += cpp

# our board pins
FEATURES_REQUIRED += xiao_nRF52840_pins

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
USEMODULE += shell_battery
USEMODULE += shell_discomode

# application components
USEMODULE += ladybug_triggers
# USEMODULE += ladybug_ble

FEATURES_REQUIRED += periph_rtt
FEATURES_REQUIRED += periph_timer
FEATURES_REQUIRED += periph_gpio
FEATURES_REQUIRED += periph_adc
FEATURES_REQUIRED += periph_timer

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk
