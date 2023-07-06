define robot_laser ranger
(
  sensor
  (
    fov 360.0
    samples 640
    range [0.2 10]
  )

  color "black"
  size [ 0.06 0.15 0.03 ]
)

define robot position
(
  pose [ 0.0 0.0 0.0 0.0 ]
  
  localization "odom"

  odom_error [0.0 0.0 0.0 0.0]

  size [ 0.60 0.40 0.0]
  origin [ 0.0 0.0 0.0 0.0 ]
  gui_nose 1
  drive "diff"
  color "gray"
  
  robot_laser(pose [0.0 0.0 0.0 0.0])
)
