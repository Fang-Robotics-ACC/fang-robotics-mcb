FROM python:3.8-alpine
WORKDIR /root
#gcompat allows arm-none-gcc-eabi to work properly with alpine, the rest are complation dependnecies
RUN apk add gcompat tar build-base git openocd gcc boost stlink wget --no-cache
#NOTE: DO NOT REFACTOR. THIS IS COMING FROM THE LEAD REFACTOR DEV, EACH RUN CREATES A LAYER, IF A LAYER DOESN'T CLEAN UP AFTER ITSELF, DOCKER WILL ADD THE LAYER EVEN IF YOU REMOVE THE FILE THE NEXT LAYER. WE ARE USING SH SO WE DON'T INSTALL BASH.
# WE ARE NOT MESSING WITH FLATTENERS FOR THE TIME BEING
# We are stuck with chaining && as you can see
RUN apk add cmake --no-cache && git clone https://github.com/google/googletest.git && cd googletest && mkdir build && cd build && cmake .. && make install && apk del && cmake && cd .. && cd .. && rm -rf googletest
RUN wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
RUN tar -xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2 && rm -r /root/gcc-arm-none-eabi-10.3-2021.10/share  && rm gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
ENV PATH="${PATH}:/root/gcc-arm-none-eabi-10.3-2021.10/bin"
RUN git clone https://github.com/Fang-Robotics-ACC/fang-robotics-mcb.git && pip install -r ~/fang-robotics-mcb/fang-mcb-project/requirements.txt && rm -rf fang-robotics-mcb
