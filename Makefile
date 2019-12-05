AGA_MOD=ex01 ex02 ex03
AGA_FILES=$(addprefix aga_,$(AGA_MOD))
AGA_KO=$(addsuffix .ko,$(AGA_FILES))

obj-m+=$(addsuffix .o,$(AGA_FILES))

RELEASE=$(shell uname -r)
KERNELDIR=/lib/modules/$(RELEASE)/build

all: $(AGA_KO)

%.ko: %.c
	@$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	@$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
