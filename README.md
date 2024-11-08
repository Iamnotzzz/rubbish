# savespace 帮助文档

set by imnotzzz 
## 热烈欢迎252！！！
## 热烈欢迎616！！！（乱入


本仓库建立于2024.11.7<br>
主要用来装一点~~乱七八糟我也不知道放哪~~ 好玩的东西<br>
恰如其名的rubbish聚集地（<br>


### 一点点文件说明


#### MMMMMMM

这是2024年夏完成的一个简易的麦当劳点餐系统<br>
本文件是内含c代码源文件和可独立运行封装完毕的.exe文件<br>
还很贴心的准备了easy-x包的下载地址来建立可视化界面（完整的包太大）<br>
注意注意注意！！！easy-x只能在vs-stdio中运行，请务必检查打开时的IDE<br>
未来计划将使用QT重新完成这个文件，敬请期待<br>


#### torch

这是由两个文件组成的一个简单的神经网络学习的小实例<br>
这段代码主要使用的包有torch torchvision matplotlib<br>
推荐使用miniconda建立虚拟环境后运行<br>
~~miniconda的使用详情请询问百度~~<br>
以下是这些包的pip安装代码<br>

```bash
pip install torch torchvision matplotlib
```
<br>
具体的代码说明请见lab2的torch/The AI report of lab2.pdf<br>
这段代码引入了CIFAR-10数据集（由于数据过大未在仓库中储存）<br>
这段代码分为两个版本，其中torch/torchcpu.py为使用cpu进行运算的版本<br>
而torch/torchgpu.py则为使用gpu计算的版本<br>
gpu版本目前疑似无法调用显存，只能通过内存+cuda的模式计算，有待优化<br>



#### OXgame

这是一个仅有前端的圈叉棋小游戏，支持本地双人对战<br>
很简单的网页练手，适用于html\css\javascript初学者进行联系<br>
具体解释详见[OX棋帮助文档](OXgame/readme.md)<br>
预计在学习vue3后使用vue与elementplus进行改写，尽情期待（画饼）<br>

##### P.S.本仓库在11.8凌晨因为本人操作不当数据完全丢失一次，在此告诫大家善用brench，及时存档！！！！！
