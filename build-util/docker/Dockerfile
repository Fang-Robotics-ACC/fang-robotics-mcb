FROM python:3.8-slim-bullseye
#WORKDIR /root
#RUN apk add build-base git openocd gcc boost openocd stlink gmock gtest wget --no-cache
RUN apt update
RUN apt install git openocd gcc build-essential libboost-dev openocd libgmock-dev libgtest-dev wget -y && apt-get clean && apt autoremove --purge
##RUN apt autoremove --purge
#RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
#RUN tar -xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 && rm -r /root/gcc-arm-none-eabi-10.3-2021.10/lib && rm -r /root/gcc-arm-none-eabi-10.3-2021.10/share && rm -r /root/gcc-arm-none-eabi-10.3-2021.10/arm-none-eabi && rm gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
#ENV PATH="${PATH}:/root/gcc-arm-none-eabi-10.3-2021.10/bin"
#RUN git clone https://github.com/Fang-Robotics-ACC/fang-robotics-mcb.git && pip install -r ~/fang-robotics-mcb/fang-mcb-project/requirements.txt && rm -rf fang-robotics-mcb
