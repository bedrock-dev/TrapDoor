# 暂时不知道叫什么名字的插件 

V0.1 支持MCBE1.16.10.02正式版
开源地址:[https://github.com/hhhxiao/MCBEtoolSet/]( https://github.com/hhhxiao/MCBEtoolSet/)
本项在[https://github.com/zhkj-liuxiaohua/MCMODDLL-CPP]( https://github.com/zhkj-liuxiaohua/MCMODDLL-CPP )的基础上开发而成
欢迎给这两个项目star

### 使用:

打开绿色图标的BDSLauncher.exe 后选择 bedrock_server.exe运行，你的游戏需要enable look back，不然没法连上本地服务器 
注意：这插件是给玩单机的人做的，不是服务器插件，通过服务器来做只是曲线救国，因此，请本地单人使用，多人可能会出现信息乱发的现象

### 功能介绍:
- `./tick fz` 暂停世界运行
- `./tick r` 恢复世界到正常状态
- `./tick slow num` 世界运行放慢num倍
- `./tick fw num` 步进n个游戏刻(如果tick数太多会导致客户端暂时没响应，请耐心等待，开始结束会有提示)
- `./prof` 性能分析，显示红石，世界运行，随机刻更新，方块实体更新，刷怪等的时间占用以及mspt(请在./tick r后执行)
- `./vill list `列出正在ticking的村庄 村庄边界 村庄中心 村庄半径
- `./vill draw [true/false]` 开启/关闭村庄范围和中心的显示
- `./info` 列出一些世界信息，目前只有全局生物数量(大于小于200就不刷怪的那个数量)，如有更新会添加
- `./p` 开启/关闭测距 (用木铲子右击方块) 欧氏距离(忽略y的欧式距离)，曼哈顿距离(忽略y的曼哈顿距离)
- `./func explosion [true/false]` 开启/关闭爆炸(tnt，苦力怕等)破坏方块

### 注意

- 退出游戏之前请调用./tick r，不然因为时钟同步问题还会显示你在线上但你进不去服务器，这样只能重启服务器解决
- 使用的时候建议备份存档，个人不能保证肯定不会对存档造成问题
- 免责声明：如果本插件对你的存档造成损坏，概不负责，因此建议备份

license : MIT