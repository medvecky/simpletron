FROM archlinux 

WORKDIR /home/project

RUN pacman -Sy --noconfirm clang
RUN pacman -Sy --noconfirm make 
RUN pacman -Sy --noconfirm ctags
RUN pacman -Sy --noconfirm autoconf
RUN pacman -Sy --noconfirm automake
