build:
	g++ -o subtask1 Subtask1.cpp HashTable.cpp LinkedList.cpp Node.cpp
	g++ -o subtask2 Subtask2.cpp
	g++ -o subtask3 Subtask3.cpp
run:
	./subtask1 log1.txt > output1.txt
	./subtask2 log2.txt > output2.txt
	./subtask3 log3.txt > output3.txt
	./subtask3 log4.txt > output4.txt