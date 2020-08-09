// 该文件内容由PDB工具生成。
// 注意：
// 反修饰后的符号原型可能有误，仅供参考！
// 过长的符号将由其对应的md5值表示该符号对应的标识符。
#pragma once

namespace SymHook{
	using RVA = unsigned int;

	// [原型] public: virtual void __cdecl MinecraftEventing::fireEventPlayerMessageChat(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
	// [符号] ?fireEventPlayerMessageChat@MinecraftEventing@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z
	constexpr RVA MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334 = 0x002A7AA0;

	// [原型] public: void __cdecl Level::spawnParticleEffect(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class Vec3 const & __ptr64,class Dimension * __ptr64) __ptr64
	// [符号] ?spawnParticleEffect@Level@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVVec3@@PEAVDimension@@@Z
	constexpr RVA MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb = 0x009E3370;

	// [原型] private: void __cdecl SurvivalMode::_messagePlayers(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >) __ptr64
	// [符号] ?_messagePlayers@SurvivalMode@@AEAAXV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
	constexpr RVA MSSYM_B2QUE14messagePlayersB1AE12SurvivalModeB2AAA6AEAAXVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z = 0x0073ABA0;

	// [原型] public: virtual void __cdecl ServerPlayer::displayLocalizableMessage(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > const & __ptr64) __ptr64
	// [符号] ?displayLocalizableMessage@ServerPlayer@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@3@@Z
	constexpr RVA MSSYM_MD5_39e2c315b1969108fef04029f8bddbb8 = 0x004906B0;

	// [原型] public: virtual void __cdecl ServerPlayer::displayWhisperMessage(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
	// [符号] ?displayWhisperMessage@ServerPlayer@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@000@Z
	constexpr RVA MSSYM_B1QE21displayWhisperMessageB1AE12ServerPlayerB2AAA9UEAAXAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA3000B1AA1Z = 0x00490870;

	// [原型] public: virtual int __cdecl ServerPlayer::tickWorld(struct Tick const & __ptr64) __ptr64
	// [符号] ?tickWorld@ServerPlayer@@UEAAHAEBUTick@@@Z
	constexpr RVA MSSYM_B1QA9tickWorldB1AE12ServerPlayerB2AAE13UEAAHAEBUTickB3AAAA1Z = 0x0048BE30;

	// [原型] public: virtual void __cdecl Dimension::tick(void) __ptr64
	// [符号] ?tick@Dimension@@UEAAXXZ
	constexpr RVA MSSYM_B1QA4tickB1AA9DimensionB2AAA7UEAAXXZ = 0x009C77A0;

	// [原型] public: virtual void __cdecl Level::tick(void) __ptr64
	// [符号] ?tick@Level@@UEAAXXZ
	constexpr RVA MSSYM_B1QA4tickB1AA5LevelB2AAA7UEAAXXZ = 0x009DF830;

	// [原型] public: void __cdecl LevelChunk::tick(class BlockSource & __ptr64,struct Tick const & __ptr64) __ptr64
	// [符号] ?tick@LevelChunk@@QEAAXAEAVBlockSource@@AEBUTick@@@Z
	constexpr RVA MSSYM_B1QA4tickB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB2AAA8AEBUTickB3AAAA1Z = 0x009A7460;

	// [原型] public: void __cdecl LevelChunk::tickBlocks(class BlockSource & __ptr64) __ptr64
	// [符号] ?tickBlocks@LevelChunk@@QEAAXAEAVBlockSource@@@Z
	constexpr RVA MSSYM_B1QE10tickBlocksB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z = 0x009A8410;

	// [原型] public: void __cdecl LevelChunk::tickBlockEntities(class BlockSource & __ptr64) __ptr64
	// [符号] ?tickBlockEntities@LevelChunk@@QEAAXAEAVBlockSource@@@Z
	constexpr RVA MSSYM_B1QE17tickBlockEntitiesB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z = 0x009ACD50;

	// [原型] public: void __cdecl Spawner::tick(class BlockSource & __ptr64,class LevelChunk & __ptr64) __ptr64
	// [符号] ?tick@Spawner@@QEAAXAEAVBlockSource@@AEAVLevelChunk@@@Z
	constexpr RVA MSSYM_B1QA4tickB1AA7SpawnerB2AAE20QEAAXAEAVBlockSourceB2AAE14AEAVLevelChunkB3AAAA1Z = 0x00AB0340;

	// [原型] public: bool __cdecl BlockTickingQueue::tickPendingTicks(class BlockSource & __ptr64,struct Tick const & __ptr64,int,bool) __ptr64
	// [符号] ?tickPendingTicks@BlockTickingQueue@@QEAA_NAEAVBlockSource@@AEBUTick@@H_N@Z
	constexpr RVA MSSYM_B1QE16tickPendingTicksB1AE17BlockTickingQueueB2AAA4QEAAB1UE16NAEAVBlockSourceB2AAA8AEBUTickB2AAA1HB1UA1NB1AA1Z = 0x00997BC0;

	// [原型] public: virtual void __cdecl Dimension::tickRedstone(void) __ptr64
	// [符号] ?tickRedstone@Dimension@@UEAAXXZ
	constexpr RVA MSSYM_B1QE12tickRedstoneB1AA9DimensionB2AAA7UEAAXXZ = 0x009C7440;

	// [原型] protected: class BlockPos __cdecl Actor::_getBlockOnPos(void) __ptr64
	// [符号] ?_getBlockOnPos@Actor@@IEAA?AVBlockPos@@XZ
	constexpr RVA MSSYM_B2QUE13getBlockOnPosB1AA5ActorB2AAA4IEAAB1QE10AVBlockPosB2AAA2XZ = 0x004F11E0;

	// [原型] public: virtual void __cdecl Actor::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64) __ptr64
	// [符号] ?getDebugText@Actor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z
	constexpr RVA MSSYM_MD5_f04fad6bac034f1e861181d3580320f2 = 0x00502C80;

	// [原型] public: virtual class Vec3 const & __ptr64 __cdecl Actor::getPos(void)const __ptr64
	// [符号] ?getPos@Actor@@UEBAAEBVVec3@@XZ
	constexpr RVA MSSYM_B1QA6getPosB1AA5ActorB2AAE12UEBAAEBVVec3B2AAA2XZ = 0x004EE910;

	// [原型] public: virtual bool __cdecl Actor::attack(class Actor & __ptr64) __ptr64
	// [符号] ?attack@Actor@@UEAA_NAEAV1@@Z
	constexpr RVA MSSYM_B1QA6attackB1AA5ActorB2AAA4UEAAB1UA6NAEAV1B2AAA1Z = 0x004EA660;

	// [原型] public: virtual bool __cdecl Player::attack(class Actor & __ptr64) __ptr64
	// [符号] ?attack@Player@@UEAA_NAEAVActor@@@Z
	constexpr RVA MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z = 0x006E5F30;

	// [原型] private: virtual bool __cdecl DyePowderItem::_useOn(class ItemStack & __ptr64,class Actor & __ptr64,class BlockPos,unsigned char,float,float,float)const __ptr64
	// [符号] ?_useOn@DyePowderItem@@EEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EMMM@Z
	constexpr RVA MSSYM_B2QUA5useOnB1AE13DyePowderItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z = 0x0077FBE0;

	// [原型] private: virtual bool __cdecl RedStoneDustItem::_useOn(class ItemStack & __ptr64,class Actor & __ptr64,class BlockPos,unsigned char,float,float,float)const __ptr64
	// [符号] ?_useOn@RedStoneDustItem@@EEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EMMM@Z
	constexpr RVA MSSYM_B2QUA5useOnB1AE16RedStoneDustItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z = 0x007B27D0;

	// [原型] public: class Block const & __ptr64 __cdecl BlockSource::getBlock(class BlockPos const & __ptr64)const __ptr64
	// [符号] ?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAE12AEBVBlockPosB3AAAA1Z = 0x0098D560;

	// [原型] public: class Block const & __ptr64 __cdecl BlockSource::getBlock(int,int,int)const __ptr64
	// [符号] ?getBlock@BlockSource@@QEBAAEBVBlock@@HHH@Z
	constexpr RVA MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAA3HHHB1AA1Z = 0x00994E80;

	// [原型] public: class Block const * __ptr64 __cdecl Block::setState<enum Direction::Type>(class ItemState const & __ptr64,enum Direction::Type)const __ptr64
	// [符号] ??$setState@W4Type@Direction@@@Block@@QEBAPEBV0@AEBVItemState@@W4Type@Direction@@@Z
	constexpr RVA MSSYM_B3QQDA8setStateB1AA6W4TypeB1AA9DirectionB3AAAA5BlockB2AAA9QEBAPEBV0B1AE13AEBVItemStateB2AAA6W4TypeB1AA9DirectionB3AAAA1Z = 0x00866DF0;

	// [原型] public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Block::toDebugString(void)const __ptr64
	// [符号] ?toDebugString@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
	constexpr RVA MSSYM_B1QE13toDebugStringB1AA5BlockB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x00872AB0;

	// [原型] public: bool __cdecl BlockSource::setBlock(int,int,int,class Block const & __ptr64,int) __ptr64
	// [符号] ?setBlock@BlockSource@@QEAA_NHHHAEBVBlock@@H@Z
	constexpr RVA MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NHHHAEBVBlockB2AAA1HB1AA1Z = 0x0098D5E0;

	// [原型] private: virtual bool __cdecl ShovelItem::_useOn(class ItemStack & __ptr64,class Actor & __ptr64,class BlockPos,unsigned char,float,float,float)const __ptr64
	// [符号] ?_useOn@ShovelItem@@EEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EMMM@Z
	constexpr RVA MSSYM_B2QUA5useOnB1AE10ShovelItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z = 0x007B5A70;

	// [原型] public: void __cdecl Village::tick(struct Tick,class BlockSource & __ptr64) __ptr64
	// [符号] ?tick@Village@@QEAAXUTick@@AEAVBlockSource@@@Z
	constexpr RVA MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z = 0x0060EB10;

}

// 文件结束
