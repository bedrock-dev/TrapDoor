# 暂时不知道叫什么名字的插件 

V0.1 支持MCBE1.16.10.02正式版
开源地址:[https://github.com/hhhxiao/MCBEtoolSet/]( https://github.com/hhhxiao/MCBEtoolSet/)
本项在[https://github.com/zhkj-liuxiaohua/MCMODDLL-CPP]( https://github.com/zhkj-liuxiaohua/MCMODDLL-CPP )的基础上开发而成
欢迎给这两个项目star

### 使用:

打开绿色图标的BDSLauncher.exe 后选择 bedrock_server.exe运行，你的游戏需要enable look back，不然没法连上本地服务器 
注意：这插件是给玩单机的人做的，不是服务器插件，通过服务器来做只是曲线救国，因此，请本地单人使用，多人可能会出现信息乱发的现象

### 功能介绍:

#### ./tick

- `./tick fz` 暂停世界运行,包括区块加载，更新，实体更新，红石信号更新等等等行为。
- `./tick r` 恢复世界到正常状态
- `./tick slow num` 世界运行放慢num倍
- `./tick fw num` 步进n个游戏刻(如果tick数太多会导致客户端暂时没响应，请耐心等待，开始结束会有提示)



实现原理解析:

下面是服务器每gt执行的函数其中叶子节点包含在上一级节点內部

-- Dimension::updateRedstone() 更新所有红石原件的内部信号,这个时候就算红石灯收到信号也不会量，因为它还没收到更新，活塞同理

-- Level::tick()  更新除了红石之外的世界所有东西

​	-- Dimension::tick() 区块加载和卸载，村庄更新

​	-- ServerPlayer::tickWorld()  更新玩家所在的区域

​		-- LevelChunk::tick()  区块加载

​		--  LevelChunk::tickBlocks() 随机刻和环境更新(下雨，结冰等等)

​		--  LevelChunk::tickEntities() 方块实体更新，到这个时候活塞才会对伸出作出反应，漏斗也会漏东西

​		-- Spawner::tick()

​		-- Others 包括计划刻更新等等

  -- others

`fz` 做的就是每gt都阻止`Dimension::updateRedstone() 和Level::tick()`函数的执行

`slow`就更傻逼了，放慢了n倍就设置一个模n的计数器，只有计数器能倍n整除的时候才执行上面两个函数

`fw`也是一样的，连续执行n次上述两个函数 

#### 性能分析

性能分析目前仅支持下面一个指令

- `./prof` 性能分析，显示红石，世界运行，随机刻更新，方块实体更新，刷怪等的时间占用以及mspt(请在./tick r后执行)

原理分析：用高精度计数器在连续几个gt内计算上述各函数的执行事件，然后平均就行了。

#### Villiage

村庄相关目前有两个指令

- `./vill list `列出正在ticking的村庄 村庄边界 村庄中心 村庄半径
- `./vill draw [true/false]` 开启/关闭村庄范围和中心的显示

注意`list`是列出**在ticking的村庄，不是所有在加载区块内的村庄都会加载**，这个指令能直观地告诉你玩家在某个挂机点的时候刷帖机的核心数到底是多少，有多少个村子有效。

村庄边界的格式: [(x1,y1,z1),(x2,y2,z2),(cx,cy,cz),radius]边界矩形框两个对角线的坐标，中心是矩形框的中心，半径是直接调用的服务器内算半径的函数计算的，算法未知，这个半径会直接参与村庄距离有关的计算。

实现原理：维护了一个全局的村庄集合，每gt只要有village调用tick函数，它就会被加入set，这个集合会每5s清一次，方便从集合中移除被游戏移除的村庄

#### 其它

- `./info` 列出一些世界信息，目前只有全局生物数量(大于小于200就不刷怪的那个数量)，如有更新会添加，
- `./p` 开启/关闭测距 (用木铲子右击方块) 欧氏距离(忽略y的欧式距离)，曼哈顿距离(忽略y的曼哈顿距离)
- `./func explosion [true/false]` 开启/关闭爆炸(tnt，苦力怕等)破坏方块

### 注意

- 退出游戏之前请调用./tick r，不然因为时钟同步问题还会显示你在线上但你进不去服务器，这样只能重启服务器解决
- 使用的时候建议备份存档，个人不能保证肯定不会对存档造成问题
- 免责声明：如果本插件对你的存档造成损坏，概不负责，因此建议备份

license : MIT

