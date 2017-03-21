#
# Copyright (c) 2009,2013 Kustaa Nyholm
# Changes 2017 by Kamil Cukrowski
#

.SUFFIXES:

# default target is 18f2550. To compile with 18f4550 run make TARGET=18f4550
TARGET := 18f2550
HEX = cdcacm.hex
SRCS = $(patsubst %.c,%.o,$(wildcard *.c))
LIBS = libc18f.lib libm18f.lib libsdcc.lib libio$(TARGET).lib 
SDCC = sdcc
SDCCFLAGS = -V --use-non-free -Wl,-m,-s$(TARGET).lkr,-O2,--no-cinit-warnings -mpic16 -p$(TARGET) --disable-warning 85 --std-sdcc99 --obanksel=3 --use-non-free
OBJDIR = .obj

.SECONDEXPANSION: 
# Uses a .f file as a flag file in each directory   
%/.f: 
	mkdir -p $(dir $@) 
	touch $@ 
# dont' let make remove the flag files automatically  
.PRECIOUS: %/.f 

# pretty standard default target
all:    $(OBJDIR)/$(HEX)

# Compile the C-files
$(OBJDIR)/%.o: %.c $$(@D)/.f  
	$(SDCC) -c $(SDCCFLAGS) $< -o $@

# Link the compiled files and libraries    
$(OBJDIR)/$(HEX): $(addprefix $(OBJDIR)/, $(SRCS:.c=.o)) 
	$(SDCC) $(SDCCFLAGS) -o $(OBJDIR)/$(HEX) $(addprefix $(OBJDIR)/, $(SRCS:.c=.o)) $(LIBS)

# pretty standard clean that attempts to delete all that this Makefile may left behind
clean:
	rm -f $(OBJDIR)/*.rel
	rm -f $(OBJDIR)/*.lnk
	rm -f $(OBJDIR)/*.S19
	rm -f $(OBJDIR)/*.map
	rm -f $(OBJDIR)/*.mem
	rm -f $(OBJDIR)/*.asm
	rm -f $(OBJDIR)/*.rst
	rm -f $(OBJDIR)/*.sym
	rm -f $(OBJDIR)/*.lst
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.dep
	rm -f $(OBJDIR)/*.hex
	rm -f $(OBJDIR)/*.cod
	rm -f $(OBJDIR)/.f
	rm -f $(OBJDIR)/$(TARGET)

distclean: clean
	rmdir $(OBJDIR)

