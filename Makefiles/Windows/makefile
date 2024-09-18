# ----------------------------
# Makefile Options
# ----------------------------

NAME = MinicraftCE
ICON = icon.png
DESCRIPTION = "A version of minicraft for your calculator"
COMPRESSED = YES
ARCHIVED = YES

COMPRESS_MODE = zx0
PREFER_OS_CRT = YES
HAS_PRINTF = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk
