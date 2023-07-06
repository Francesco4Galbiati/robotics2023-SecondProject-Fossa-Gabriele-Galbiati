Nodes/Plugins/Packages used:
- Mapping (2d and 3d): slam toolbox
- Pointcloud conversion: pointcloud_to_laserscan
- Simulation: stage
- Navigation: move_base
- Local planner: teb_local_planner
- Global planner: global_planner
- Localization: amcl

The launch folder contains 3 launch files:
- one for 2d mapping (mapping.launch)
- one for 3d mapping (mapping3d.launch)
- one for navigation (navigation.launch)

The map used for the navigation is a slightly post-processed version of first bag 3d lidar map
