prog=wam

ccflags=-pthread
ldflags=-pthread -lX11 -lfltk

ld=g++

$(prog): $(objs) libdeq.so
	$(ld) -o $@ $(objs) $(ldflags) -L. -ldeq -Wl,-rpath=.

include ../GNUmakefile
