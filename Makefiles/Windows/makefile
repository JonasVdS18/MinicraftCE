# ----------------------------
# Makefile Options
# ----------------------------

NAME = MiniCE
ICON = icon.png
DESCRIPTION = "A version of minicraft for your calculator"
COMPRESSED = YES
ARCHIVED = YES

COMPRESS_MODE = zx0
PREFER_OS_CRT = YES
HAS_PRINTF = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

## fonts.c depends on testfont.inc, which is built from testfont.fnt
FONTDIR = $(SRCDIR)/fonts
FONT = $(FONTDIR)/FONT.fnt
FONT_INC = $(FONTDIR)/FONT.inc

DEPS = $(FONT_INC)

$(FONT_INC): $(FONT)
	convfont -o carray -f $(FONTDIR)/FONT.fnt $(FONTDIR)/FONT.inc

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk
