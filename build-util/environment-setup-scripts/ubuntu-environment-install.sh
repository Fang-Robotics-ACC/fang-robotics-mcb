#!/bin/bash -i

# COPYRIGHT 2025 RAVEN ASHER RAZIEL under MIT license
# This version is dual licensed under agplv3 as well
# (view license of fang-robotics-acc/fang-robotics-acc)
# Your project must upgrade from gplv3 to agplv3 if you use this script
# If you use taproot, you already are gplv3, might as well get better protection
# with agplv3

# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the “Software”), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# General build requirements
sudo apt-get install python3 python-is-python3 \
python3-pip git openocd gcc build-essential \
libboost-all-dev openocd stlink-tools \
libgmock-dev libgtest-dev pipenv wget curl -y

# Python build requirements
sudo apt install build-essential libreadline-dev libncursesw5-dev \
libssl-dev libsqlite3-dev tk-dev libgdbm-dev libc6-dev libbz2-dev \
libffi-dev zlib1g-dev liblzma-dev -y

# Custom embedded compiler
wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
tar -xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
rm gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2

mkdir -p ~/.local/share
mv gcc-arm-none-eabi-10.3-2021.10 ~/.local/share
echo 'export PATH="$HOME/.local/share/gcc-arm-none-eabi-10.3-2021.10/bin:$HOME/.local/bin:$PATH:$PATH"' >> ~/.bashrc

# Python version manager (read below)
curl -fsSL https://pyenv.run | bash
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bashrc
echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bashrc
echo 'eval "$(pyenv init - bash)"' >> ~/.bashrc
source ~/.bashrc

# This is needed because this is what the taproot devs use
# One majory reason is that the modm uses has_key() which got deprecated
# in later versions of python 3 
# Python 3.10 is used for the docker container along with a more recent
# Version of gmock 3.17 to prevent a semgentation fault error on unit tests
# It is clear that python does not use semantic versioning that well
pyenv install 3.8.10
cd ../../fang-mcb-project
pipenv install --python ~/.pyenv/versions/3.8.10/bin/python3
pipenv run pip install -r requirements.txt
