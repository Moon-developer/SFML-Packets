
NAME = PacketTest
CC = clang++
OUT = -o $(NAME)

# VAR for linux version
FLAGS = -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

# VAR for mac version
RPATH= -Wl,-rpath,$(PWD)/SFML/Frameworks
FRAMEWORKS= -framework sfml-graphics -framework sfml-window -framework sfml-system
FRAMEWORK_PATH= -F SFML/Frameworks
INCL= -I includes -I SFML/include -I SFML/lib

# ======= SFML ======= #
SFML_DIR='SFML-2.5.0-macOS-clang'
SFML_DIR='SFML-2.5.0'
DWNLD=sh -c '$$(curl -Lo $(SFML) --progress-bar https://www.sfml-dev.org/files/SFML-2.5.0-macOS-clang.tar.gz)'
UNTAR=sh -c '$$(tar -xzf $(SFML) && rm -rf $(SFML))'
CR_MV=sh -c '$$(mv $(SFML_DIR) SFML && cp -rf ./SFML/extlibs/* ./SFML/Frameworks/.)'

# check what operating system this is on
RUN :=
ifeq (`uname -s`, Linux)
	RUN += $(CC) $(OUT) $(RPATH) $(FRAMEWORK_PATH) $(FRAMEWORKS) $(INCL)
else
	RUN += $(CC) $(OUT) $(FLAGS1)
endif

all:
	$(RUN)

download:
	if [ -d "SFML" ];then echo "SFML already installed";else $(DWNLD) && $(UNTAR) && $(CR_MV)
	

fclean :
	@rm -rf $(NAME)
