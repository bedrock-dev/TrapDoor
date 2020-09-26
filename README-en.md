V0.2.0 **Current only support Minecraft Bedrock Edition 1.16.10.02**

### What‘s this
This is a BDS-based server plugin which provides some useful functions to help player understandning the game. I want it can play a role like **capert-mod-be**
### How to use
1. The release only provide a`Trapdoor.dll`file.To use this,you **need to prepare a DLL injetor**，here is an avaliable one: [https://github.com/DarthTon/Xenos/releases/tag/2.3.2](https://github.com/DarthTon/Xenos/releases/tag/2.3.2) 
2. you need to enable the loopback of Minecraft Windows 10 UWP APP. click [here](https://www.google.com/search?sxsrf=ALeKk02SoLVvT6Rg8w5sAViKIJtnPDjx_Q%3A1601094611292&ei=08NuX5W6EcKbmAWT7KjwAg&q=how+to+enable+loopback+for+a+UWP+app&oq=how+to+enable+loopback+for+a+UWP+app&gs_lcp=CgZwc3ktYWIQAzoECCMQJzoFCCEQoAE6BwghEAoQoAFQkiNY_kpgmE5oA3AAeACAAdsDiAGHHpIBCDItMTEuMS4ymAEAoAEBqgEHZ3dzLXdpesABAQ&sclient=psy-ab&ved=0ahUKEwjV77qc_oXsAhXCDaYKHRM2Ci4Q4dUDCA0&uact=5) to seaech in google
3. prepare the BDS file for windows 1.16.10.2
4. double click the`Xenos64.exe`,click  `add`  to select the dll file,then click `select`  to select `bedrock_server.exe`
5. click `Inject` to start the server
6. open you game , set IP to `127.0.0.1`, then enjoy.

![](./img/howto.png)


### Command list

#### ./tick

- `./tick fz`  to freeze the world ticking,such as chunk (un)load,chunk tick, tick redstone and so on 
- `./tick slow num` set the world ticking speed [num] times slower then default
- `./tick fw num` forward [num] ticks 
- `./tick r` reset the world ticking to default

#### ./prof

- Proflie the world ticking，including mspt, redstone tick,random tick,block entity tick,spawn tick and so on. the mod will print the average run time in the next 100 gt.

#### Villiage

村庄相关目前有两个指令

- `./vill list `列出正在ticking的村庄 村庄边界 村庄中心 村庄半径
- `./vill draw [true/false]` 开启/关闭村庄范围和中心的显示，爱心粒子是村庄中心，龙息粒子是边框

注意`list`是列出**在ticking的村庄，不是所有在加载区块内的村庄都会加载**，这个指令能直观地告诉你玩家在某个挂机点的时候刷帖机的核心数到底是多少，有多少个村子在有效更新。

村庄边界的格式: `center,radius,workded/population golem,bedPOI canSpawnGolem,bounds `边界矩形框两个对角线的坐标，中心是矩形框的中心，`radius`是村庄半径,`worked`是工作过的村民数,`population`是当前村庄的村民数,`goldem`是属于该村庄的铁傀儡数，`bedPOI`是村庄拥有(已和村民绑定的)床的数量。

实现原理：维护了一个全局的村庄集合，每gt只要有village调用tick函数，它就会被加入set，这个集合会每5s清一次，方便从集合中移除被游戏移除的村庄

#### 刷怪

- `./actor start` 开始计数器，插件开始统计所有生成的生物
- `./actor end` 结束计数器
- `./actor p`打印统计结果，第一行是计时器经过的时间，第二行是各种生物的数量，第三行是刷怪点到玩家的距离(玩家打本条指令时的距离)分布(这一条好像数据有问题)，后面是每一行是每一个`y`值的刷怪数量
- `./actor info`列出一些刷怪信息，目前只有全局生物数量(大于小于200就不刷怪的那个数量)，如有更新会添加

### 漏斗计数器

> 这个功能完全抄`carpet`的

一共有五个频道

- 钻石 0
- 绿宝石 1
- 铁 2
- 金 3
- 青金石 4

在你用`./func hc true`后，放在这些矿物块上的漏斗会变成无尽的漏斗，所有吸入的东西都没了，但是数据会保留下来.你可以用`./counter channel p`来查看这些漏斗吸收的物品数据,包括每种物品的个数和吸入平均速率。用`./counter channel reset`来重置某个频道的所有漏斗。`channel`选填`[0-4]`.

### 测距

> 移除了 `./p`指令

在你使用`./func pm true`后，1.16新增的两种地狱菌类的木板会作为测距点，你挨个放置这两个方块的时候屏幕会显示这两个点之间欧式距离和曼哈顿距离，括号内的数据是忽略`y`的平面数据。

#### 其它

- `./config pvd [distance]` 控制村庄显示时候的粒子显示范围 默认是128 
- `./func explosion [true/false]` 开启/关闭爆炸(tnt，苦力怕等)破坏方块
- `./help `会显示一些简单的版本信息和帮助信息和感谢列表

### 注意

- 退出游戏之前请调用./tick r，不然因为时钟同步问题还会显示你在线上但你进不去服务器，这样只能重启服务器解决
- 使用的时候建议备份存档，个人不能保证肯定不会对存档造成问题
- 免责声明：如果本插件对你的存档造成损坏，概不负责，因此建议备份
- 如果你有任何问题可以在issue中提出

### Credit
[https://github.com/zhkj-liuxiaohua/MCMODDLL-CPP]( https://github.com/zhkj-liuxiaohua/MCMODDLL-CPP )

license : GPL