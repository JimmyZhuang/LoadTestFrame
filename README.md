# 简介
C++ 多线程压测工具，可统计被压测服务的QPS以及请求平均时延。

# 环境依赖
## 编译器
* 安装支持 C++ 11 或更高版本的编译器：GCC 4.8 或以上版本

## 依赖库

- [libcurl](https://curl.haxx.se/libcurl/)

安装例子如下:

```
ubuntu
sudo apt-get install libcurl4-openssl-dev

centos
yum install libcurl-devel
```

备注：建议安装最新版的 libcurl 库，否则可能存在 libcurl 库内存泄露 bug 问题

# 例子
参考 tencentcloudapi_instance_example 和 http_instance_example 用例代码，并修改相应的 Makefile 文件。
