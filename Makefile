EXECS = Driver
OBJS = Driver.o VehicleBase.o Random.o Parameters.o Section.o TrafficLight.o Road.o Lane.o Animator.o
OBJS2 = VehicleBase.o Random.o Parameters.o Section.o TrafficLight.o Road.o Lane.o

#### use next two lines for Mac
#CC = clang++
#CCFLAGS = -std=c++11 -stdlib=libc++

#### use next two lines for mathcs* machines:
CC = g++
CCFLAGS = -g -std=c++11

all: $(EXECS)

Driver: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp *.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)

driver: $(OBJS2) Driver.o
	$(CC) $(CCFLAGS) $^ -o $@

