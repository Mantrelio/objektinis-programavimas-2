CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET = main
OBJDIR = build/obj
SOURCES = src/main.cpp src/main-menu.cpp src/utils/input-utils.cpp \
	src/utils/grading-utils.cpp src/student.cpp \
	src/generate-student-list.cpp \
	src/test/generate-student-list-test.cpp \
	src/test/output-nuskriausti-and-protingi-test.cpp \
	src/test/student-rule-of-five-operators-test.cpp \
	src/data-sorting/sort-students.cpp \
	src/data-sorting/sort-nuskriausti-and-protingi.cpp \
	src/output-results.cpp \
	src/create-student.cpp
OBJECTS = $(patsubst src/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)


$(OBJDIR)/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(OBJDIR)

.PHONY: clean
