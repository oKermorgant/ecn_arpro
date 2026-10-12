#!/usr/bin/env bash

root=$pwd
distro=resolute

# IDE conf (QtCreator / VScode)
if [[ "$(grep ideconf ~/.bashrc -c)" == "0" ]]; then
    echo 'Configuring the ideconf shortcut...'
    git clone https://github.com/oKermorgant/ros_management_tools ~/.ros_management_tools  &> /dev/null
    echo "alias ideconf='python3 $HOME/.ros_management_tools/ide/ide_config.py'" >> ~/.bashrc
fi

# Duels framework
echo 'Setting up the Duels framework...'
echo '   - installing pygame...'
pip uninstall pygame  --break-system-packages
pip install pygame-ce zmq --break-system-packages
rm -rf /tmp/duels
mkdir -p /tmp/duels
cd /tmp/duels

if [[ -e ~/duels/games ]]; then
    echo 'Copy current games into ~/duels_games'
    cp -r ~/duels/games ~/duels_games
fi

echo '   - getting duels version...'
wget https://raw.githubusercontent.com/CentraleNantesRobotics/ecn_install/refs/heads/ros2/modules.yaml -O modules.yaml  &> /dev/null
duels_deb=$(grep -Eho 'duels(.*?).deb' modules.yaml)
duels_deb=$(echo $duels_deb | sed "s/[]]/${distro}]/g")
echo "    -> using ${duels_deb}..."
wget "https://box.ec-nantes.fr/index.php/s/s7rbFwAeTqwoe6e/download?path=%2F&files=${duels_deb}" -O duels.deb  &> /dev/null
echo "   - extracting to ${HOME}/duels."
ar x duels.deb  &> /dev/null
zstd -df data.tar.zst  &> /dev/null
tar -xf data.tar
rm -rf ~/duels
mv opt/duels ~
cd $root
rm -rf /tmp/duels
