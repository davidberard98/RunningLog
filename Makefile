#include wxWidgets stuff
WX=`wx-config --libs` `wx-config --cxxflags`

all: RunningLog

RunningLog: main.o MyFrame.o MilesPanel.o WorkoutNotes.o DayOfWeek.o DailyPanel.o WeekInfo.o SeasonsEdit.o WeekBottom.o DayRun.o StoreRun.o Dates.o rlIds.o pugixml.o
	g++ main.o MyFrame.o MilesPanel.o WorkoutNotes.o DayOfWeek.o DailyPanel.o WeekInfo.o SeasonsEdit.o WeekBottom.o DayRun.o StoreRun.o Dates.o rlIds.o pugixml.o $(WX) -o RunningLog

main.o: src/main.cpp
	g++ -c src/main.cpp $(WX)

MyFrame.o: src/MyFrame.cpp
	g++ -c src/MyFrame.cpp $(WX)

MilesPanel.o: src/MilesPanel.cpp
	g++ -c src/MilesPanel.cpp $(WX)

WorkoutNotes.o: src/WorkoutNotes.cpp
	g++ -c src/WorkoutNotes.cpp $(WX)

DayOfWeek.o: src/DayOfWeek.cpp
	g++ -c src/DayOfWeek.cpp $(WX)

DailyPanel.o: src/DailyPanel.cpp
	g++ -c src/DailyPanel.cpp $(WX)

WeekInfo.o: src/WeekInfo.cpp
	g++ -c src/WeekInfo.cpp $(WX)

SeasonsEdit.o: src/SeasonsEdit.cpp
	g++ -c src/SeasonsEdit.cpp $(WX)

WeekBottom.o: src/WeekBottom.cpp
	g++ -c src/WeekBottom.cpp $(WX)

DayRun.o: src/DayRun.cpp
	g++ -c src/DayRun.cpp $(WX)

StoreRun.o: src/StoreRun.cpp
	g++ -c src/StoreRun.cpp $(WX)

Dates.o: src/Dates.cpp
	g++ -c src/Dates.cpp $(WX)

rlIds.o: src/rlIds.cpp
	g++ -c src/rlIds.cpp $(WX)

pugixml.o: src/pugixml/pugixml.cpp
	g++ -c src/pugixml/pugixml.cpp

wxComboBoxTest: src/wxComboBoxTest.cpp
	g++ src/wxComboBoxTest.cpp -o wxComboBoxTest $(WX)

clean:
	rm -rf *.o
