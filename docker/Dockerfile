FROM osrf/ros:humble-desktop

ARG DEBIAN_FRONTEND=noninteractive

WORKDIR /workspaces

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ros-humble-hardware-interface \
    ros-humble-generate-parameter-library \
    ros-humble-xacro \
    ros-humble-controller-interface \
    ros-humble-realtime-tools \
    ros-humble-ros2-control-test-assets \
    ros-humble-controller-manager \
    ros-humble-joint-state-publisher \
    ros-humble-control-msgs \
    ros-humble-gazebo-ros \
    ros-humble-control-toolbox \
    ros-humble-ackermann-msgs \
    ros-humble-ament-cmake \
    ros-humble-ament-cmake-clang-format \
    ros-humble-moveit \
    ros-humble-joint-state-broadcaster \
    libignition-gazebo6-dev \
    ros-humble-joint-trajectory-controller \
    libpoco-dev \
    libeigen3-dev \
    ament-cmake-clang-tidy \
    && rm -rf /var/lib/apt/lists/*


RUN mkdir ~/source_code
RUN cd ~/source_code && git clone https://github.com/frankaemika/libfranka.git \
    && cd libfranka \
    && git switch fr3-develop \
    && git submodule init \
    && git submodule update \
    && mkdir build && cd build \
    && cmake -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF  .. \
    && make franka -j$(nproc) \
    && cpack -G DEB \
    && sudo dpkg -i libfranka*.deb
    
RUN echo source "/opt/ros/${ROS_DISTRO}/setup.bash" >>~/.bashrc
