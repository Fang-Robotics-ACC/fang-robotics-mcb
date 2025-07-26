FROM ubuntu:latest

WORKDIR /home/ubuntu

COPY requirements.txt ./fang-mcb-project
CMD apt update
CMD sudo apt-get install python3 python-is-python3 python3-pip git openocd gcc build-essential libboost-all-dev openocd stlink-tools libgmock-dev libgtest-dev pipenv wget -y
