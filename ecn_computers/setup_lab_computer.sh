#!/usr/bin/env bash

root=$pwd

# IDE conf (QtCreator / VScode)
if [[ "$(grep ideconf ~/.bashrc -c)" == "0" ]]; then
    echo 'Configuring the ideconf shortcut...'
    git clone https://github.com/oKermorgant/ros_management_tools ~/.ros_management_tools  &> /dev/null
    echo "alias ideconf='python3 $HOME/.ros_management_tools/ide/ide_config.py'" >> ~/.bashrc
fi

# Duels framework
echo 'Setting up the Duels framework...'
pip install pygame --break-system-packages
rm -rf /tmp/duels
mkdir -p /tmp/duels
cd /tmp/duels
wget https://raw.githubusercontent.com/CentraleNantesRobotics/ecn_install/refs/heads/master/modules.yaml -O modules.yaml  &> /dev/null
duels_deb=$(grep -Eho 'duels(.*?).deb' modules.yaml)
duels_deb=$(echo $duels_deb | sed 's/[]]/noble]/g')
wget "https://box.ec-nantes.fr/index.php/s/s7rbFwAeTqwoe6e/download?path=%2F&files=${duels_deb}" -O duels.deb  &> /dev/null
ar x duels.deb  &> /dev/null
zstd -df data.tar.zst  &> /dev/null
mkdir -p root
tar -xvf data.tar --directory=root  &> /dev/null
cp -r root/opt/duels ~/

cd $root
rm -rf /tmp/duels
