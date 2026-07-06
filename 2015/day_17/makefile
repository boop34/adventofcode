
!if [cmd /c for %f in (day_*.cpp) do @echo detect = %~nf > detect.tmp & goto :done]
!endif

!include detect.tmp

TARGET = $(detect)

CC = clang++
CFLAGS = -std=c++23 -Wall -Wextra -ggdb -Weffc++ -Wconversion -Wsign-conversion

all: $(TARGET).exe

$(TARGET).exe: $(TARGET).cpp
        $(CC) $(TARGET).cpp -o $(TARGET).exe $(CFLAGS)

run: $(TARGET).exe
        $(TARGET).exe

clean:
        del *.obj 2>nul
        del *.exe 2>nul
        del detect.tmp 2>nul
