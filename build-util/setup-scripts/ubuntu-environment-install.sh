#!/bin/bash -i

#General build requirements
sudo apt-get install python3 python-is-python3 \
python3-pip git openocd gcc build-essential \
libboost-all-dev openocd stlink-tools \
libgmock-dev libgtest-dev pipenv wget curl -y

#Python build requirements
sudo apt install build-essential libreadline-dev libncursesw5-dev \
libssl-dev libsqlite3-dev tk-dev libgdbm-dev libc6-dev libbz2-dev \
libffi-dev zlib1g-dev liblzma-dev -y

#Custom embedded compiler
wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
tar -xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
rm gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2

mkdir -p ~/.local/share
mv gcc-arm-none-eabi-10.3-2021.10 ~/.local/share
echo 'export PATH="$HOME/gcc-arm-none-eabi-10.3-2021.10/bin:$HOME/.local/bin:$PATH:$PATH"' >> ~/.bashrc

#Python version manager (read below)
curl -fsSL https://pyenv.run | bash
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
echo 'eval "$(pyenv init - bash)"' >> ~/.bashrc
source ~/.bashrc

#This is needed because this is what the taproot devs use
#One majory reason is that the modm uses has_key() which got deprecated
#in later versions of python 3 
#Python 3.10 is used for the docker container along with a more recent
#Version of gmock 3.17 to prevent a semgentation fault error on unit tests
#It is clear that python does not use semantic versioning that well
pyenv install 3.8.10
cd ../../fang-mcb-project
pipenv install --python ~/.pyenv/versions/3.8.10/bin/python3
