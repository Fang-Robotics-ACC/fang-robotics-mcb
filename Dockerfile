FROM ubuntu:latest

WORKDIR /home/ubuntu

COPY fang-mcb-project/requirements.txt requirements.txt 
RUN apt update
RUN apt install python3 python-is-python3 python3-pip git openocd gcc build-essential libboost-all-dev openocd stlink-tools libgmock-dev libgtest-dev pipenv wget pipenv -y
RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
RUN tar -xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
RUN mv gcc-arm-none-eabi-10.3-2021.10 ~/
ENV PATH="${PATH}:~/gcc-arm-none-eabi-10.3-2021.10/bin"
