FROM python:3.8-alpine
WORKDIR /root
RUN apk update && apk add --no-cache bash autoconf build-base binutils cmake curl file gcc g++ git libgcc libtool linux-headers make musl-dev ninja tar unzip wget
RUN apk add build-base git openocd gcc boost openocd stlink gmock gtest wget --no-cache
#RUN apt-get clean
#RUN apt autoremove --purge
RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
RUN tar -xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
RUN rm gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
ENV PATH="${PATH}:/root/gcc-arm-none-eabi-10.3-2021.10/bin"
WORKDIR /root/gcc-arm-none-eabi-10.3-2021.10
RUN rm arm-none-eabi
RUN rm lib
RUN rm share
WORKDIR /root
RUN git clone https://github.com/Fang-Robotics-ACC/fang-robotics-mcb.git --recursive
RUN pip install -r ~/fang-robotics-mcb/fang-mcb-project/requirements.txt
