FROM ubuntu:latest
FROM python:3.8

WORKDIR /root

RUN apt update
RUN apt install git openocd gcc build-essential libboost-all-dev openocd stlink-tools libgmock-dev libgtest-dev pipenv wget pipenv curl -y
RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
RUN tar -xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
ENV PATH="${PATH}:/root/gcc-arm-none-eabi-10.3-2021.10/bin"
RUN git clone https://github.com/Fang-Robotics-ACC/fang-robotics-mcb.git --recursive
RUN pip install -r ~/fang-robotics-mcb/fang-mcb-project/requirements.txt
