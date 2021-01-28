# gazebo_plugin

This repo serves as a template to write a model plugin of Gazebo using Clion. 


1. Download the repo 
~~~
git clone https://github.com/haoboluo/gazebo_plugin.git
~~~

2. Open the project in Clion. 

3. configure as: 

4. Test the compiled plugin: 
~~~
roscore
rosrun gazebo_ros gzserver /home/luo/gazebo_plugin/sphere_contact.world
gzclient
~~~
