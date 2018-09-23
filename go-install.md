# Ubuntu 18.04 虚拟机下安装配置 Go 语言环境

## 材料准备

本文使用的虚拟机为此前的博客文[Mac 环境下使用 VirtualBox 部署 Ubuntu 18.04私有云](https://blog.chenmt.science/2018/09/09/77/) 中所搭建的虚拟机，系统版本为Ubuntu 18.04.1 LTS。

## 配置过程

使用 apt 是最方便的安装方式，只需要输入命令`sudo apt install golang` 即可将 go 安装入系统。

安装后还需要配置相关环境变量以保证 go 的运行正常

### 1

首先要设置 GOPATH，这是 go 唯一需要设置的环境变量，它是 go 编译过程中查找代码包的地址，结构大致如下：

```
    /home/user/go/
        src/
            foo/
                bar/               (go code in package bar)
                    x.go
                quux/              (go code in package main)
                    y.go
        bin/
            quux                   (installed command)
        pkg/
            linux_amd64/
                foo/
                    bar.a          (installed package object)
```

其在 *nix 系统中默认位置为`$HOME/go` ，可以通过如下方式更改：

假定我们希望将目录改至`~/go-lab` , 可以通过下面的命令完成：

`export GOPATH=~/go-lab `

但是，这个命令在重启 SHELL 后便会失效，我们可以把它写入配置文件中，我使用的 SHELL 为 zsh，所以修改`~/.zshrc`文件；若你使用的是 bash，则需修改`~/.bash_profile` 文件，直接将该命令写入文件末尾即可。

此外，若你希望可以直接调用通过 `go install` 安装至`$GOPATH/bin`下的可执行文件。可以在以上的命令后再加一句`export PATH=$PATH:$GOPATH/bin`。

## 2

我们编写的代码都放置在GOPATH 的 src 文件夹下，按照包划分，使用`go build` 或`go install` 命令来进行编译或安装编写好的 go 程序。

## 使用 Gotour 来进行 Go 学习

Go 提供了Gotour 教程来帮助初学者快速入门，可以通过以下方式安装至本地：

`go get github.com/Go-zh/tour/gotour`

因为我使用的电脑配置较低，虚拟机的图形环境使用极为卡顿，所以通过以下方式来从宿主机访问虚拟机提供的 web 服务：

在 VirtualBox 的虚拟机的设置界面->网络->网卡1->高级->端口转发中增加对虚拟机3999端口的转发，然后在虚拟机中输入`gotour -http 192.168.100.101:3999`命令（其中的 ip 地址需要换为你的虚拟机的实际地址）即可启动 Gotour 并监听在3999端口。此时在宿主机浏览器中访问192.168.100.101:3999 就可以看到 Go 语言之旅教程了。