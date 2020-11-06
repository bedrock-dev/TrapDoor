# TrapDoor 

V0.2.0 **仅支持MCBE1.16.10.02正式版**
开源地址:[https://github.com/hhhxiao/TrapDoor/](https://github.com/hhhxiao/TrapDoor/)
本项在[https://github.com/zhkj-liuxiaohua/MCMODDLL-CPP]( https://github.com/zhkj-liuxiaohua/MCMODDLL-CPP )的基础上开发而成
欢迎给这两个项目star

### 使用:

`release`中的文件只是单纯的`dll`文件，你**需要下载一个dll注入器才能启动游戏**，dll注入器你可以前往[https://github.com/DarthTon/Xenos/releases/tag/2.3.2](https://github.com/DarthTon/Xenos/releases/tag/2.3.2) 下载。下载完后运行`Xenos64.exe`，剩下的看下图即可:

![](img/howto.png)

上面点`new`后会弹出窗口，选择服务端文件`bedrock_server.exe`即可。然后点`add`添加`dll`文件，最后点`Inject`启动服务器。

使用其它的注入器请自行探索用法。

> 注意: 你需要开启MC的loop back，不然无法连接本地服务端


### 功能介绍:

#### ./tick

- `./tick fz` 暂停世界运行,包括区块加载，更新，实体更新，红石信号更新等等等行为。
- `./tick r` 恢复世界到正常状态
- `./tick slow num` 世界运行放慢num倍
- `./tick fw num` 步进n个游戏刻(如果tick数太多会导致客户端暂时没响应，请耐心等待，开始结束会有提示)



实现原理解析:

下面是服务器每gt执行的函数其中叶子节点包含在上一级节点內部

```
-- Dimension::updateRedstone() 更新所有红石原件的内部信号,这个时候就算红石灯收到信号也不会量，因为它还没收到更新，活塞同理
-- Level::tick()  更新除了红石之外的世界所有东西
	-- Dimension::tick() 区块加载和卸载，村庄更新
	-- ServerPlayer::tickWorld()  更新玩家所在的区域
		-- LevelChunk::tick()  区块加载
		--  LevelChunk::tickBlocks() 随机刻和环境更新(下雨，结冰等等)
		--  LevelChunk::tickEntities() 方块实体更新，到这个时候活塞才会对伸出作出反应，漏斗也会漏东西
		-- Spawner::tick()
		-- Others 包括计划刻更新等等
  -- others
```

`fz` 做的就是每gt都阻止`Dimension::updateRedstone() 和Level::tick()`函数的执行

`slow`就更傻逼了，放慢了n倍就设置一个模n的计数器，只有计数器能倍n整除的时候才执行上面两个函数

`fw`也是一样的，连续执行n次上述两个函数 

#### 性能分析

性能分析目前仅支持下面一个指令

- `./prof` 性能分析，显示红石，世界运行，随机刻更新，方块实体更新，刷怪等的时间占用以及mspt(统计100gt的数据，因此数据显示会有5s的延迟)(请在./tick r后执行，不然不准)

原理分析：用高精度计时器在100gt内计算上述各函数的执行时间，然后平均就行了。

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

license : GPL

