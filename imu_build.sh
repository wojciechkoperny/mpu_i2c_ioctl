#colcon build --executor sequential --packages-select pck_wk

cd install/pck_wk/lib/pck_wk     # cd to the directory with your node
chown root:root my_node         # change ownship to root
chmod a+rx my_node              # set as executable by all
chmod u+s my_node               # set the setuid bit
cd ../../../..
# . install/setup.bash
#ros2 run pck_wk my_node
