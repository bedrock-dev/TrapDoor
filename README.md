V0.2.0 **Current only support Minecraft Bedrock Edition 1.16.10.02**

 中文在  [这里](https://github.com/hhhxiao/TrapDoor/blob/master/README-zh.md)

### What‘s this
This is a BDS-based server plugin which provides some useful functions to help player understandning the game. I want it can play a role like **capert-mod-be**
### How to use
1. The release only provide a`Trapdoor.dll`file.To use this,you **need to prepare a DLL injetor**，here is an avaliable one: [https://github.com/DarthTon/Xenos/releases/tag/2.3.2](https://github.com/DarthTon/Xenos/releases/tag/2.3.2) 
2. you need to enable the loopback of Minecraft Windows 10 UWP APP. click [here](https://www.google.com/search?sxsrf=ALeKk02SoLVvT6Rg8w5sAViKIJtnPDjx_Q%3A1601094611292&ei=08NuX5W6EcKbmAWT7KjwAg&q=how+to+enable+loopback+for+a+UWP+app&oq=how+to+enable+loopback+for+a+UWP+app&gs_lcp=CgZwc3ktYWIQAzoECCMQJzoFCCEQoAE6BwghEAoQoAFQkiNY_kpgmE5oA3AAeACAAdsDiAGHHpIBCDItMTEuMS4ymAEAoAEBqgEHZ3dzLXdpesABAQ&sclient=psy-ab&ved=0ahUKEwjV77qc_oXsAhXCDaYKHRM2Ci4Q4dUDCA0&uact=5) to seaech in google
3. prepare the BDS file for windows 1.16.10.2
4. double click the`Xenos64.exe`,click  `add`  to select the dll file,then click `select`  to select `bedrock_server.exe`
5. click `Inject` to start the server
6. open you game , in Servers tab  click `add Server`, set Server address  to `127.0.0.1`,  port is dealut `19132`  then enjoy it.

![](img/howto.png)


### Command list

#### ./tick

- `./tick fz`  to freeze the world ticking,such as chunk (un)load,chunk tick, tick redstone and so on 
- `./tick slow num` set the world ticking speed [num] times slower than default
- `./tick fw num` forward [num] ticks 
- `./tick r` reset the world ticking to default

#### ./prof

- Proflie the world ticking，including mspt, redstone tick,random tick,block entity tick,spawn tick and so on. the mod will print the average run time in the next 100 gt.

#### Villiage

- `./vill list ` list all villages' som useful  imformation,these information is ：
  - center
  - radius
  - worked dwellers number
  - population
  - golem number in current village
  - bedPOI  number(include claimed and unclaimed)
  - can spawn irom golem or not
  - bounds
- `./vill draw [true/false]` [enable/disable] the display of ticking villages' bounds and center 

> notice: the above two commands can only be used in **ticking villages**

#### Spawn

- `./actor start` start a mob spawn counter
- `./actor end`  to end a mob spawn counter
- `./actor p` to print the counter result，the first line is number of ticks，follow part  is spawn mobs' type and num , the third part is a histogram of `distanceToPalyer - num`(**this part seems wrong**)，the last part is a histogram of `heght(y)-num`
- `./actor info` to list some info, currently only support global total mob num

### Hopper counter

> this function is from carpet

Different from carpet, this mod only provides 5 channels ,they are:

- diamond_block 0
- emerald_block 1
- iron_block 2
- gold_block 3
- lapis_block 4

after you type`./func hc true`，all the hoppers above these hoppers will have an unlimited capacity.you can type`./counter channel p` to print the absorbing items' name , number and speed 。Please  use `./counter channel reset` to reset the data of one chaeenl.  please **use number or not block name** to replace `channel`  in above commands.

### Distance measure

After you use `./func pm true`， the two kinds new planks will become the distance measure tools. the screen will print the distance information between the two points. 

#### Others

- `./config pvd [distance]`  set the village particles max view distance(to decrease network load) default is 128 
- `./func explosion [true/false]`  disable/enable explosion destroy blocks.
- `./help ` show some help information and credits.

### Notice

- if you have used `./tick` commands, please type `./tick r ` before left the game(or directly restart the server) 
- Please backup you level

### Develop

this poroject is build by cmake and complied by MSVC,to build this project you should download  `detours.lib` file 

welcome pull requests.

### Credit
[https://github.com/zhkj-liuxiaohua/MCMODDLL-CPP]( https://github.com/zhkj-liuxiaohua/MCMODDLL-CPP )

### License

GPL