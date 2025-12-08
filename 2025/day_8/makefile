# Generate detect.tmp containing: detect = day_XX
!if [cmd /c for %f in (day_*.cpp) do @echo detect = %~nf > detect.tmp & goto :done]
!endif

!include detect.tmp

TARGET = $(detect)

CC = cl
CFLAGS = /std:c++20 /Wall /EHsc

all: $(TARGET).exe

$(TARGET).exe: $(TARGET).cpp
	$(CC) $(TARGET).cpp /Fe:$(TARGET).exe $(CFLAGS)

run: $(TARGET).exe
	$(TARGET).exe

clean:
	del *.obj 2>nul
	del *.exe 2>nul
	del detect.tmp 2>nul

