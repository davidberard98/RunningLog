#include wxWidgets stuff
WX=`wx-config --libs` `wx-config --cxxflags`

all: RunningLog

RunningLog: main.o MyFrame.o MilesPanel.o WorkoutNotes.o DayOfWeek.o DailyPanel.o WeekInfo.o SeasonsEdit.o WeekBottom.o DayRun.o StoreRun.o Dates.o rlIds.o pugixml.o
	g++ main.o MyFrame.o MilesPanel.o WorkoutNotes.o DayOfWeek.o DailyPanel.o WeekInfo.o SeasonsEdit.o WeekBottom.o DayRun.o StoreRun.o Dates.o rlIds.o pugixml.o $(WX) -o RunningLog

main.o: main.cpp
	g++ -c main.cpp $(WX)

MyFrame.o: MyFrame.cpp
	g++ -c MyFrame.cpp $(WX)

MilesPanel.o: MilesPanel.cpp
	g++ -c MilesPanel.cpp $(WX)

WorkoutNotes.o: WorkoutNotes.cpp
	g++ -c WorkoutNotes.cpp $(WX)

DayOfWeek.o: DayOfWeek.cpp
	g++ -c DayOfWeek.cpp $(WX)

DailyPanel.o: DailyPanel.cpp
	g++ -c DailyPanel.cpp $(WX)

WeekInfo.o: WeekInfo.cpp
	g++ -c WeekInfo.cpp $(WX)

SeasonsEdit.o: SeasonsEdit.cpp
	g++ -c SeasonsEdit.cpp $(WX)

WeekBottom.o: WeekBottom.cpp
	g++ -c WeekBottom.cpp $(WX)

DayRun.o: DayRun.cpp
	g++ -c DayRun.cpp $(WX)

StoreRun.o: StoreRun.cpp
	g++ -c StoreRun.cpp $(WX)

Dates.o: Dates.cpp
	g++ -c Dates.cpp $(WX)

rlIds.o: rlIds.cpp
	g++ -c rlIds.cpp $(WX)

pugixml.o: pugixml/pugixml.cpp
	g++ -c pugixml/pugixml.cpp

wxComboBoxTest: wxComboBoxTest.cpp
	g++ wxComboBoxTest.cpp -o wxComboBoxTest $(WX)

clean:
	rm -rf *.o
