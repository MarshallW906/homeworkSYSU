#Readme -- Project 4 : Advanced Library Agenda
**本proj使用了Jsoncpp库，编译时需先安装jsoncpp。**
###jsoncpp的安装&使用
**安装**
**Mac OS X：**
命令行下输入
```bash
brew install jsoncpp
```
若还未有brew，则去[HomeBrew官网](brew.sh)按照提示下载安装homebrew。

**Ubuntu：**
```bash
sudo apt-get install jsoncpp
```
windows下不明，请自行到[jsoncpp的git主页](https://github.com/open-source-parsers/jsoncpp)查找安装方式。

**使用**
在代码中加入
```cpp
#include <json/json.h>
```
编译时增加参数（仅在Mac OS X 安装了Xcode command line Tools时测试通过），命令如下：
```bash
g++ -I /usr/local/include/ -L /usr/local/lib/ -ljsoncpp main.cpp -o library_agenda
```
然后运行即可。
```bash
./library_agenda
```