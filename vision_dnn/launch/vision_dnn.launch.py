from launch_ros.actions import Node
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import TextSubstitution
from launch.substitutions import LaunchConfiguration


def generate_launch_description():

    config_file_launch_arg = DeclareLaunchArgument(
        "dnn_example_config_file", default_value=TextSubstitution(text="config/fcosworkconfig.json")
    )

    dump_render_launch_arg = DeclareLaunchArgument(
        "dnn_example_dump_render_img", default_value=TextSubstitution(text="0")
    )

    msg_pub_topic_name_launch_arg = DeclareLaunchArgument(
        "dnn_example_msg_pub_topic_name", default_value=TextSubstitution(text="hobot_dnn_detection")
    )

    dnn_node_example_node = Node(
        package="dnn_node_example",
        executable="example",
        output="screen",
        parameters=[
            {"config_file": LaunchConfiguration("dnn_example_config_file")},
            {"dump_render_img": LaunchConfiguration("dnn_example_dump_render_img")},
            {"feed_type": 1},
            {"is_shared_mem_sub": 1},
            {"msg_pub_topic_name": LaunchConfiguration("dnn_example_msg_pub_topic_name")}
        ],
        arguments=["--ros-args", "--log-level", "warn"]
    )

    return LaunchDescription([config_file_launch_arg, dump_render_launch_arg, msg_pub_topic_name_launch_arg, dnn_node_example_node])
