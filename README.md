# gazebo_plugin

This repo serves as a template to write a model plugin of Gazebo using Clion. 


1. Download the repo 
~~~
git clone https://github.com/haoboluo/gazebo_plugin
mv gazebo_plugin_tutorial/ ..
~~~

2. Open a project for 'gazebo_plugin_tutorial' in Clion. 

3. configure as: 

<div align=center><img src="https://github.com/haoboluo/gazebo_plugin/blob/main/clion.png" width="450" height="300" /></div>

4. Test the compiled plugin: 
~~~
roscore
rosrun gazebo_ros gzserver /home/luo/gazebo_plugin_tutorial/sphere_contact.world
gzclient
~~~
