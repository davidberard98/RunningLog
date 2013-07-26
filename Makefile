all: RunningLog

RunningLog: main.o MyFrame.o MilesPanel.o WorkoutNotes.o DayOfWeek.o DailyPanel.o WeekInfo.o DayRun.o StoreRun.o Dates.o rlIds.o
	g++ main.o MyFrame.o MilesPanel.o WorkoutNotes.o DayOfWeek.o DailyPanel.o WeekInfo.o DayRun.o StoreRun.o Dates.o rlIds.o `wx-config --libs` `wx-config --cxxflags` -o RunningLog

main.o: main.cpp
	g++ -c main.cpp `wx-config --libs` `wx-config --cxxflags`

MyFrame.o: MyFrame.cpp
	g++ -c MyFrame.cpp `wx-config --libs` `wx-config --cxxflags`

MilesPanel.o: MilesPanel.cpp
	g++ -c MilesPanel.cpp `wx-config --libs` `wx-config --cxxflags`

WorkoutNotes.o: WorkoutNotes.cpp
	g++ -c WorkoutNotes.cpp `wx-config --libs` `wx-config --cxxflags`

DayOfWeek.o: DayOfWeek.cpp
	g++ -c DayOfWeek.cpp `wx-config --libs` `wx-config --cxxflags`

DailyPanel.o: DailyPanel.cpp
	g++ -c DailyPanel.cpp `wx-config --libs` `wx-config --cxxflags`

WeekInfo.o: WeekInfo.cpp
	g++ -c WeekInfo.cpp `wx-config --libs` `wx-config --cxxflags`

DayRun.o: DayRun.cpp
	g++ -c DayRun.cpp `wx-config --libs` `wx-config --cxxflags`

StoreRun.o: StoreRun.cpp
	g++ -c StoreRun.cpp `wx-config --libs` `wx-config --cxxflags`

Dates.o: Dates.cpp
	g++ -c Dates.cpp `wx-config --libs` `wx-config --cxxflags`

rlIds.o: rlIds.cpp
	g++ -c rlIds.cpp `wx-config --libs` `wx-config --cxxflags`

clean:
	rm -rf *.o
