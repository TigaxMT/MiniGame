CPPSOURCES =  $(wildcard *.cpp)
LIBS= `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`

all: MiniGame

MiniGame: $(CPPSOURCES:.cpp=.o)
		@echo Creating executable file: $@	
		@g++ -std=c++11 -o  $@ $^ $(LIBS)

%.o: %.cpp
		@echo .
		@g++ -std=c++11 -c  $< $(LIBS) -o $@

clean: 
		 @echo Cleaning Files
		-@rm  -f *.o MiniGame *~

remade:
		$(MAKE) clean
		$(MAKE)

-include $(CPPSOURCES:.cpp=.d)

%.d: %.cpp
		@g++ -std=c++11  $< -MM -MT '$*.o $*.d' -MD $(LIBS)
