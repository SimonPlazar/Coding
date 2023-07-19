TARGET = "demo_klici"

all: build run

build: 
	gcc -m32 -fPIE -Wall -Wextra -Werror -o $(TARGET) main.c 

run: 
	./$(TARGET)

clean:
	if [ -f $(TARGET) ]; then rm $(TARGET); fi
	if [ -f SysDir/PidTimeData.dat ]; then rm SysDir/PidTimeData.dat; fi
	if [ SysDir ]; then rmdir SysDir; fi