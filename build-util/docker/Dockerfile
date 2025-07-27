FROM python:3.8-alpine
WORKDIR /root
RUN apk add gcompat build-base git openocd gcc boost openocd stlink gtest gmock wget --no-cache
#RUN apt-get clean
#RUN apt autoremove --purge
RUN apk add cmake && git clone https://github.com/google/googletest.git && cd googletest && mkdir build && cd build && cmake .. && make install && apk del cmake
RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
RUN tar -xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 && rm -r /root/gcc-arm-none-eabi-10.3-2021.10/share  && rm gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
ENV PATH="${PATH}:/root/gcc-arm-none-eabi-10.3-2021.10/bin"
RUN git clone https://github.com/Fang-Robotics-ACC/fang-robotics-mcb.git --recursive && pip install -r ~/fang-robotics-mcb/fang-mcb-project/requirements.txt # rm -rf fang-robotics-mcb
