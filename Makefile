AGA_MOD=01 02 03 04 09
AGA_FILES=$(addprefix aga_ex,$(AGA_MOD))
AGA_KO=$(addsuffix .ko,$(AGA_FILES))

obj-m+=$(addsuffix .o,$(AGA_FILES))

RELEASE=$(shell uname -r)
KERNELDIR=/lib/modules/$(RELEASE)/build

all: $(AGA_KO)

%.ko: %.c
	@$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	@$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
