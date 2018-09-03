OBJDIR:=bin

PKG_CONFIG_LIBS:=gtk+-3.0

CFLAGS:=-gdwarf-2 $(shell pkg-config --cflags $(PKG_CONFIG_LIBS))
LDFLAGS:=$(shell pkg-config --libs $(PKG_CONFIG_LIBS)) -lm
LDCCFLAGS:=$(LDFLAGS)

CC:=gcc
LDCC:=gcc

TARGET:=widget_demo
OBJS := \
	lwgled.o \
	widget_demo.o

.PHONY: all
all: $(OBJDIR)/$(TARGET)

.PHONY: run valgrind
run: all
	@$(OBJDIR)/$(TARGET)

valgrind: all
	@valgrind $(OBJDIR)/$(TARGET)

$(OBJDIR)/$(TARGET): $(OBJS:%=$(OBJDIR)/%) | $(OBJDIR)
	$(LDCC) $(LDCCFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJS:%=$(OBJDIR)/%): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
