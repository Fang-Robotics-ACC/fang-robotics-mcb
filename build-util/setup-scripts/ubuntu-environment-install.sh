sudo apt-get install python3 python-is-python3\
python3-pip git openocd gcc build-essential\
libboost-all-dev openocd stlink-tools\
libgmock-dev libgtest-dev pipenv wget -y


wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
tar -xf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
rm gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
mkdir ~/.local/share
mv gcc-arm-none-eabi-10.3-2021.10 ~/.local/share
echo 'export PATH="$HOME/gcc-arm-none-eabi-10.3-2021.10/bin:$HOME/.local/bin:$PATH:$PATH"' >> ~/.bashrc
source ~/.bashrc
curl -fsSL https://pyenv.run | bash
pyenv install 3.8.10
cd ../fang-mcb-project
pipenv install --python 3.8.10
