#!/bin/bash

# install PROS
sudo apt-get --yes install unzip git make gcc-arm-none-eabi
cd ..
# install ConVEX
git clone https://github.com/jpearman/convex.git
cp convex/ChibiOS_2.6.2.zip ChibiOS_2.6.2.zip
unzip -q ChibiOS_2.6.2.zip
cp --recursive convex/convex/cortex/ convex/cortex/
cp --recursive convex/convex/plugins/ convex/plugins/
