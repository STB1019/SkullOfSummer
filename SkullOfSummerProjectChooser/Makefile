BIN_NAME = SkullOfSummerProjectChooser
CDIR = src/main/c
IDIR = src/main/include
RDIR = src/main/resources
ODIR = build

CC = gcc
CFLAGS = -I$(IDIR) -Werror
CFILES = $(wildcard $(CDIR)/*.c)
OFILES = $(addprefix $(ODIR)/, $(notdir $(patsubst %.c,%.o,$(CFILES))))

.DEFAULT_GOAL := all
.PHONY: clean makeoutdir copyresources all

$(ODIR)/%.o: $(CDIR)/%.c | makeoutdir
	@echo "compiling $<..."
	$(CC) -c -o $@ $(CFLAGS) $<

$(ODIR)/$(BIN_NAME): $(OFILES) | makeoutdir
	$(CC) -o $@ $(CFLAGS) $(LIBS) $^

all: makeoutdir copyresources $(ODIR)/$(BIN_NAME)
	@echo "DONE"

copyresources: makeoutdir
	@echo "copying resources..."
	cp -rv $(RDIR)/* $(ODIR)/

makeoutdir:
	mkdir -pv $(ODIR)

clean:
	rm -rfv $(ODIR)/