cd ~/catkin_ws 
catkin_make -DCMAKE_EXPORT_COMPILE_COMMANDS=1 || exit 1
rqt_console & 
rviz -d /home/fede/catkin_ws/src/navigation_test/rviz/rviz.rviz & 
roscore &
sleep 3
roslaunch navigation_test navigation_test.launch  
