# 🤖 Base Node

⚡ Fundamental package for robotchain. ⚡

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

> 已经内置在robotchain中，无需单独、重复安装，该仓库仅供学习参考。
>
> It is already built-in within robotchain, so there is no need for separate or redundant installation. This repository is provided for learning and reference purposes only.

## 📖 Initialization

> 使用、编译、构建前请在Ubuntu设备中完成robotchain的安装和部署。
>
> Please complete the installation and deployment of `robotchain` on your `Ubuntu` device before using, compiling, and building.

```shell
sudo curl -s https://cdn.geekros.com/robotchain/install.sh|bash
```
> 使用git克隆仓库到Ubuntu设备。
>
> Clone the repository to your Ubuntu device using `git`.

```shell
git clone git@github.com:geekros/base_node_package.git
```

## 📖 Build

```shell
cd base_node_package
```

```shell
cd serial_foxy
mkdir build && cd build
cmake .. && make && sudo make install
cd ../ && sudo rm -rf build && cd ../

sudo cp /usr/local/lib/libserial.so ./debian/opt/tros/lib/

colcon build --packages-select serial_port_node
colcon build --packages-select vision_dnn
```

## 📖 Publishing a Debian (deb) software package.

```shell
cd rosbridge_suite
```
> 打包为deb文件
>
>Packaging into a `deb` file.

```shell
robotchain pack
```
> 发布deb到软件源
>
> Publishing the `deb` to a software repository.

```shell
robotchain publish
```

## 📖 Install

```shell
sudo apt install base_node_package
```

## 🌞 Development Team

> GEEKROS
> https://www.geekros.com