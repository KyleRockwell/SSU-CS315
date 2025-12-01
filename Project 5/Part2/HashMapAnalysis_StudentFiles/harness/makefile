CXX=c++
CXXFLAGS= -std=c++20 -Wall
IMPL_PATH=../implementations
BHIV=/BinaryHeapInVector
#VPATH = ../../utils:../implementations/BinomialQueues:../implemntations/LinearBaseLine/:..implmentations/BinaryHeapInVector/
harness: ./*.cpp bh.o lbl.o qo.o  cmp.o lbl.o bq.o bqN.o
	$(CXX) $(CXXFLAGS) *.cpp cmp.o  bh.o bq.o  lbl.o qo.o bqN.o -o harness

#	../implementations/BinaryHeapInVector/BinaryHeapInVector.cpp
#	../../utils/comparator.cpp
#	../implementations/BinomialQueues/BinomialQueue.cpp
#	../implementations/LinearBaseLine/LinearBaseLine.cpp
#	../implementations/Oracle/QuadraticOracle.cpp
	

bh.o: $(IMPL_PATH)/$(BHIV)/BinaryHeapInVector.cpp cmp.o
	$(CXX) $(CXXFLAGS) -c $(IMPL_PATH)/BinaryHeapInVector/BinaryHeapInVector.cpp -o bh.o

cmp.o: ../../utils/comparator.cpp 
	$(CXX) $(CXXFLAGS) -c ../../utils/comparator.cpp -o cmp.o

bqN.o: $(IMPL_PATH)/BinomialQueues/BQnode.cpp 
	$(CXX) $(CXXFLAGS) -c $(IMPL_PATH)/BinomialQueues/BQnode.cpp -o bqN.o


bq.o: $(IMPL_PATH)/BinomialQueues/BinomialQueue.cpp bqN.o
	$(CXX) $(CXXFLAGS) -c $(IMPL_PATH)/BinomialQueues/BinomialQueue.cpp -o bq.o

	
lbl.o: $(IMPL_PATH)/LinearBaseLine/LinearBaseLine.cpp cmp.o
		$(CXX) $(CXXFLAGS) -c $(IMPL_PATH)/LinearBaseLine/*.cpp -o lbl.o

qo.o: $(IMPL_PATH)/Oracle/QuadraticOracle.cpp
		$(CXX) $(CXXFLAGS) -c $(IMPL_PATH)/Oracle/QuadraticOracle.cpp -o qo.o

clean: 
		rm *.o *.so

