
.SILENT:
include Makefile.flags


objects      = $(patsubst %.c,%.o,$(shell find src -name "*.c")) $(patsubst %.cpp,%.o,$(shell find src -name "*.cpp"))
objects_fasm = $(patsubst %.S,%.o,$(shell find src -name "*.S"))

objects_test = $(patsubst %.c,%.o,$(shell find src -name "test_*.c")) $(patsubst %.cpp,%.o,$(shell find src -name "test_*.cpp"))
objects     := $(filter-out $(objects_test),$(objects))


all: bin/rvvirt


bin/rvvirt: $(objects) $(objects_fasm)
	$(LD) $(LDFLAGS) $(objects) $(objects_fasm) $(LDLIBS) -o $@


clean:
	echo " -RM    bin/rvvirt $(objects)"
	-$(RM) -f bin/rvvirt $(objects) $(objects_fasm)


.PHONY: all clean


