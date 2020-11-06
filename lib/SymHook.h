// 该文件内容由PDB工具生成。
// 注意：
// 反修饰后的符号原型可能有误，仅供参考！
// 过长的符号将由其对应的md5值表示该符号对应的标识符。
#pragma once

namespace SymHook{
	using RVA = unsigned int;

	// [原型] private: static class std::unordered_map<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class SharedPtr<class BlockLegacy>,struct std::hash<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,struct std::equal_to<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class SharedPtr<class BlockLegacy> > > > BlockTypeRegistry::mBlockLookupMap
	// [符号] ?mBlockLookupMap@BlockTypeRegistry@@0V?$unordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$SharedPtr@VBlockLegacy@@@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$SharedPtr@VBlockLegacy@@@@@std@@@2@@std@@A
	constexpr RVA MSSYM_MD5_ceb8b47184006e4d7622b39978535236 = 0x01973620;

	// [原型] public: virtual void __cdecl MinecraftEventing::fireEventPlayerMessageChat(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
	// [符号] ?fireEventPlayerMessageChat@MinecraftEventing@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z
	constexpr RVA MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334 = 0x002EFE60;

	// [原型] public: void __cdecl Level::spawnParticleEffect(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class Vec3 const & __ptr64,class Dimension * __ptr64) __ptr64
	// [符号] ?spawnParticleEffect@Level@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVVec3@@PEAVDimension@@@Z
	constexpr RVA MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb = 0x00A79650;

	// [原型] void __cdecl CommandUtils::displayLocalizableMessage(bool,class Player & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > const & __ptr64)
	// [符号] ?displayLocalizableMessage@CommandUtils@@YAX_NAEAVPlayer@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@@Z
	constexpr RVA MSSYM_MD5_24be62e9330073695808606844de0d99 = 0x00445CB0;

	// [原型] public: virtual void __cdecl ServerLevel::tick(void) __ptr64
	// [符号] ?tick@ServerLevel@@UEAAXXZ
	constexpr RVA MSSYM_B1QA4tickB1AE11ServerLevelB2AAA7UEAAXXZ = 0x004EA570;

	// [原型] public: virtual int __cdecl ServerPlayer::tickWorld(struct Tick const & __ptr64) __ptr64
	// [符号] ?tickWorld@ServerPlayer@@UEAAHAEBUTick@@@Z
	constexpr RVA MSSYM_B1QA9tickWorldB1AE12ServerPlayerB2AAE13UEAAHAEBUTickB3AAAA1Z = 0x004ED3C0;

	// [原型] public: virtual void __cdecl Dimension::tick(void) __ptr64
	// [符号] ?tick@Dimension@@UEAAXXZ
	constexpr RVA MSSYM_B1QA4tickB1AA9DimensionB2AAA7UEAAXXZ = 0x00A633C0;

	// [原型] public: virtual void __cdecl Level::tick(void) __ptr64
	// [符号] ?tick@Level@@UEAAXXZ
	constexpr RVA MSSYM_B1QA4tickB1AA5LevelB2AAA7UEAAXXZ = 0x00A75A30;

	// [原型] public: void __cdecl LevelChunk::tick(class BlockSource & __ptr64,struct Tick const & __ptr64) __ptr64
	// [符号] ?tick@LevelChunk@@QEAAXAEAVBlockSource@@AEBUTick@@@Z
	constexpr RVA MSSYM_B1QA4tickB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB2AAA8AEBUTickB3AAAA1Z = 0x00A30750;

	// [原型] public: void __cdecl LevelChunk::tickBlocks(class BlockSource & __ptr64) __ptr64
	// [符号] ?tickBlocks@LevelChunk@@QEAAXAEAVBlockSource@@@Z
	constexpr RVA MSSYM_B1QE10tickBlocksB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z = 0x00A31630;

	// [原型] public: void __cdecl LevelChunk::tickBlockEntities(class BlockSource & __ptr64) __ptr64
	// [符号] ?tickBlockEntities@LevelChunk@@QEAAXAEAVBlockSource@@@Z
	constexpr RVA MSSYM_B1QE17tickBlockEntitiesB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z = 0x00A36690;

	// [原型] public: void __cdecl Spawner::tick(class BlockSource & __ptr64,class LevelChunk const & __ptr64) __ptr64
	// [符号] ?tick@Spawner@@QEAAXAEAVBlockSource@@AEBVLevelChunk@@@Z
	constexpr RVA MSSYM_B1QA4tickB1AA7SpawnerB2AAE20QEAAXAEAVBlockSourceB2AAE14AEBVLevelChunkB3AAAA1Z = 0x00B3C410;

	// [原型] public: bool __cdecl BlockTickingQueue::tickPendingTicks(class BlockSource & __ptr64,struct Tick const & __ptr64,int,bool) __ptr64
	// [符号] ?tickPendingTicks@BlockTickingQueue@@QEAA_NAEAVBlockSource@@AEBUTick@@H_N@Z
	constexpr RVA MSSYM_B1QE16tickPendingTicksB1AE17BlockTickingQueueB2AAA4QEAAB1UE16NAEAVBlockSourceB2AAA8AEBUTickB2AAA1HB1UA1NB1AA1Z = 0x00A204D0;

	// [原型] public: virtual void __cdecl Dimension::tickRedstone(void) __ptr64
	// [符号] ?tickRedstone@Dimension@@UEAAXXZ
	constexpr RVA MSSYM_B1QE12tickRedstoneB1AA9DimensionB2AAA7UEAAXXZ = 0x00A63010;

	// [原型] public: virtual void __cdecl Actor::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64) __ptr64
	// [符号] ?getDebugText@Actor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z
	constexpr RVA MSSYM_MD5_f04fad6bac034f1e861181d3580320f2 = 0x00569BC0;

	// [原型] public: virtual class Vec3 const & __ptr64 __cdecl Actor::getPos(void)const __ptr64
	// [符号] ?getPos@Actor@@UEBAAEBVVec3@@XZ
	constexpr RVA MSSYM_B1QA6getPosB1AA5ActorB2AAE12UEBAAEBVVec3B2AAA2XZ = 0x00554A80;

	// [原型] public: virtual bool __cdecl Actor::attack(class Actor & __ptr64) __ptr64
	// [符号] ?attack@Actor@@UEAA_NAEAV1@@Z
	constexpr RVA MSSYM_B1QA6attackB1AA5ActorB2AAA4UEAAB1UA6NAEAV1B2AAA1Z = 0x00550BF0;

	// [原型] public: virtual bool __cdecl Player::attack(class Actor & __ptr64) __ptr64
	// [符号] ?attack@Player@@UEAA_NAEAVActor@@@Z
	constexpr RVA MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z = 0x0071BF40;

	// [原型] public: void __cdecl Explosion::explode(void) __ptr64
	// [符号] ?explode@Explosion@@QEAAXXZ
	constexpr RVA MSSYM_B1QA7explodeB1AA9ExplosionB2AAA7QEAAXXZ = 0x00A69850;

	// [原型] public: virtual void __cdecl Actor::setNameTag(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
	// [符号] ?setNameTag@Actor@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
	constexpr RVA MSSYM_B1QE10setNameTagB1AA5ActorB2AAA9UEAAXAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z = 0x00562DA0;

	// [原型] public: virtual void __cdecl Mob::buildDebugInfo(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > & __ptr64)const __ptr64
	// [符号] ?buildDebugInfo@Mob@@UEBAXAEAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
	constexpr RVA MSSYM_B1QE14buildDebugInfoB1AA3MobB2AAA9UEBAXAEAVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z = 0x006F4960;

	// [原型] public: class Vec3 __cdecl Actor::getViewVector(float)const __ptr64
	// [符号] ?getViewVector@Actor@@QEBA?AVVec3@@M@Z
	constexpr RVA MSSYM_B1QE13getViewVectorB1AA5ActorB2AAA4QEBAB1QA6AVVec3B2AAA1MB1AA1Z = 0x005552A0;

	// [原型] public: virtual class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64 __cdecl Actor::getNameTag(void)const __ptr64
	// [符号] ?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
	constexpr RVA MSSYM_B1QE10getNameTagB1AA5ActorB2AAA8UEBAAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x00562BC0;

	// [原型] private: virtual bool __cdecl DyePowderItem::_useOn(class ItemStack & __ptr64,class Actor & __ptr64,class BlockPos,unsigned char,float,float,float)const __ptr64
	// [符号] ?_useOn@DyePowderItem@@EEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EMMM@Z
	constexpr RVA MSSYM_B2QUA5useOnB1AE13DyePowderItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z = 0x007D56D0;

	// [原型] private: virtual bool __cdecl RedStoneDustItem::_useOn(class ItemStack & __ptr64,class Actor & __ptr64,class BlockPos,unsigned char,float,float,float)const __ptr64
	// [符号] ?_useOn@RedStoneDustItem@@EEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EMMM@Z
	constexpr RVA MSSYM_B2QUA5useOnB1AE16RedStoneDustItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z = 0x008097E0;

	// [原型] public: class Block const & __ptr64 __cdecl BlockSource::getBlock(class BlockPos const & __ptr64)const __ptr64
	// [符号] ?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAE12AEBVBlockPosB3AAAA1Z = 0x00A16410;

	// [原型] public: class Block const & __ptr64 __cdecl BlockSource::getBlock(int,int,int)const __ptr64
	// [符号] ?getBlock@BlockSource@@QEBAAEBVBlock@@HHH@Z
	constexpr RVA MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAA3HHHB1AA1Z = 0x00A1D720;

	// [原型] public: class BlockLegacy const & __ptr64 __cdecl Block::getLegacyBlock(void)const __ptr64
	// [符号] ?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ
	constexpr RVA MSSYM_B1QE14getLegacyBlockB1AA5BlockB2AAE19QEBAAEBVBlockLegacyB2AAA2XZ = 0x000BBB60;

	// [原型] public: bool __cdecl BlockSource::setBlock(int,int,int,class Block const & __ptr64,int) __ptr64
	// [符号] ?setBlock@BlockSource@@QEAA_NHHHAEBVBlock@@H@Z
	constexpr RVA MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NHHHAEBVBlockB2AAA1HB1AA1Z = 0x00A16490;

	// [原型] public: bool __cdecl BlockSource::setBlock(class BlockPos const & __ptr64,class Block const & __ptr64,int,struct ActorBlockSyncMessage const * __ptr64) __ptr64
	// [符号] ?setBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@HPEBUActorBlockSyncMessage@@@Z
	constexpr RVA MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NAEBVBlockPosB2AAA9AEBVBlockB2AAE26HPEBUActorBlockSyncMessageB3AAAA1Z = 0x00A164E0;

	// [原型] private: virtual bool __cdecl ShovelItem::_useOn(class ItemStack & __ptr64,class Actor & __ptr64,class BlockPos,unsigned char,float,float,float)const __ptr64
	// [符号] ?_useOn@ShovelItem@@EEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EMMM@Z
	constexpr RVA MSSYM_B2QUA5useOnB1AE10ShovelItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z = 0x0080CF30;

	// [原型] public: virtual void __cdecl SpongeBlock::onPlace(class BlockSource & __ptr64,class BlockPos const & __ptr64)const __ptr64
	// [符号] ?onPlace@SpongeBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QA7onPlaceB1AE11SpongeBlockB2AAE20UEBAXAEAVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z = 0x009CD790;

	// [原型] public: void __cdecl BlockSource::updateNeighborsAt(class BlockPos const & __ptr64) __ptr64
	// [符号] ?updateNeighborsAt@BlockSource@@QEAAXAEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z = 0x00A176C0;

	// [原型] public: virtual enum EventResult __cdecl VanillaServerGameplayEventListener::onBlockPlacedByPlayer(class Player & __ptr64,class Block const & __ptr64,class BlockPos const & __ptr64,bool) __ptr64
	// [符号] ?onBlockPlacedByPlayer@VanillaServerGameplayEventListener@@UEAA?AW4EventResult@@AEAVPlayer@@AEBVBlock@@AEBVBlockPos@@_N@Z
	constexpr RVA MSSYM_B1QE21onBlockPlacedByPlayerB1AE34VanillaServerGameplayEventListenerB2AAA4UEAAB1QE14AW4EventResultB2AAE10AEAVPlayerB2AAA9AEBVBlockB2AAE12AEBVBlockPosB3AAUA1NB1AA1Z = 0x00BD5270;

	// [原型] private: bool __cdecl GameMode::_destroyBlockInternal(class BlockPos const & __ptr64,unsigned char) __ptr64
	// [符号] ?_destroyBlockInternal@GameMode@@AEAA_NAEBVBlockPos@@E@Z
	constexpr RVA MSSYM_B2QUE20destroyBlockInternalB1AA8GameModeB2AAA4AEAAB1UE13NAEBVBlockPosB2AAA1EB1AA1Z = 0x00775EB0;

	// [原型] public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Block::toDebugString(void)const __ptr64
	// [符号] ?toDebugString@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
	constexpr RVA MSSYM_B1QE13toDebugStringB1AA5BlockB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x008D7100;

	// [原型] public: virtual class AABB const & __ptr64 __cdecl BlockLegacy::getOutline(class BlockSource & __ptr64,class BlockPos const & __ptr64,class AABB & __ptr64)const __ptr64
	// [符号] ?getOutline@BlockLegacy@@UEBAAEBVAABB@@AEAVBlockSource@@AEBVBlockPos@@AEAV2@@Z
	constexpr RVA MSSYM_B1QE10getOutlineB1AE11BlockLegacyB2AAE12UEBAAEBVAABBB2AAE15AEAVBlockSourceB2AAE12AEBVBlockPosB2AAA5AEAV2B2AAA1Z = 0x008DA4A0;

	// [原型] public: void __cdecl BlockLegacy::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64,class BlockPos const & __ptr64)const __ptr64
	// [符号] ?getDebugText@BlockLegacy@@QEBAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_MD5_794b421b4bf67101f7418cd0d78bad83 = 0x008DB770;

	// [原型] public: virtual void __cdecl BlockActor::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64,class BlockPos const & __ptr64) __ptr64
	// [符号] ?getDebugText@BlockActor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_MD5_b5a16de43d7486d6e9b23cfb126773a7 = 0x0089DF70;

	// [原型] public: bool __cdecl BlockSource::setExtraBlock(class BlockPos const & __ptr64,class Block const & __ptr64,int) __ptr64
	// [符号] ?setExtraBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@H@Z
	constexpr RVA MSSYM_B1QE13setExtraBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NAEBVBlockPosB2AAA9AEBVBlockB2AAA1HB1AA1Z = 0x00A16860;

	// [原型] public: class Block const * __ptr64 __cdecl BlockLegacy::tryGetStateFromLegacyData(unsigned short)const __ptr64
	// [符号] ?tryGetStateFromLegacyData@BlockLegacy@@QEBAPEBVBlock@@G@Z
	constexpr RVA MSSYM_B1QE25tryGetStateFromLegacyDataB1AE11BlockLegacyB2AAE13QEBAPEBVBlockB2AAA1GB1AA1Z = 0x008D8BF0;

	// [原型] public: void __cdecl Village::tick(struct Tick,class BlockSource & __ptr64) __ptr64
	// [符号] ?tick@Village@@QEAAXUTick@@AEAVBlockSource@@@Z
	constexpr RVA MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z = 0x00644680;

	// [原型] public: float __cdecl Village::getApproximateRadius(void)const __ptr64
	// [符号] ?getApproximateRadius@Village@@QEBAMXZ
	constexpr RVA MSSYM_B1QE20getApproximateRadiusB1AA7VillageB2AAA7QEBAMXZ = 0x00645380;

	// [原型] public: virtual void __cdecl VillagerV2::buildDebugInfo(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > & __ptr64)const __ptr64
	// [符号] ?buildDebugInfo@VillagerV2@@UEBAXAEAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
	constexpr RVA MSSYM_B1QE14buildDebugInfoB1AE10VillagerV2B2AAA9UEBAXAEAVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z = 0x0070A500;

	// [原型] public: static bool __cdecl Village::isVillagePOI(class BlockSource const & __ptr64,class BlockPos const & __ptr64)
	// [符号] ?isVillagePOI@Village@@SA_NAEBVBlockSource@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QE12isVillagePOIB1AA7VillageB2AAA2SAB1UE16NAEBVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z = 0x0064FA90;

	// [原型] public: void __cdecl VillageManager::tick(struct Tick const & __ptr64) __ptr64
	// [符号] ?tick@VillageManager@@QEAAXAEBUTick@@@Z
	constexpr RVA MSSYM_B1QA4tickB1AE14VillageManagerB2AAE13QEAAXAEBUTickB3AAAA1Z = 0x00652BD0;

	// [原型] public: class std::weak_ptr<class POIInstance> __cdecl VillageManager::getPOI(class BlockPos const & __ptr64)const __ptr64
	// [符号] ?getPOI@VillageManager@@QEBA?AV?$weak_ptr@VPOIInstance@@@std@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QA6getPOIB1AE14VillageManagerB2AAA4QEBAB1QA2AVB2QDA4weakB1UA3ptrB1AE12VPOIInstanceB3AAAA3stdB2AAE12AEBVBlockPosB3AAAA1Z = 0x006562E0;

	// [原型] public: unsigned __int64 __cdecl Village::getBedPOICount(void)const __ptr64
	// [符号] ?getBedPOICount@Village@@QEBA_KXZ
	constexpr RVA MSSYM_B1QE14getBedPOICountB1AA7VillageB2AAA4QEBAB1UA3KXZ = 0x00645420;

	// [原型] public: class Mob * __ptr64 __cdecl Spawner::spawnMob(class BlockSource & __ptr64,struct ActorDefinitionIdentifier const & __ptr64,class Actor * __ptr64,class Vec3 const & __ptr64,bool,bool,bool) __ptr64
	// [符号] ?spawnMob@Spawner@@QEAAPEAVMob@@AEAVBlockSource@@AEBUActorDefinitionIdentifier@@PEAVActor@@AEBVVec3@@_N44@Z
	constexpr RVA MSSYM_B1QA8spawnMobB1AA7SpawnerB2AAE11QEAAPEAVMobB2AAE15AEAVBlockSourceB2AAE29AEBUActorDefinitionIdentifierB2AAA9PEAVActorB2AAA8AEBVVec3B3AAUA3N44B1AA1Z = 0x00B39A30;

	// [原型] public: static bool __cdecl Command::validRange(int,int,int,class CommandOutput & __ptr64)
	// [符号] ?validRange@Command@@SA_NHHHAEAVCommandOutput@@@Z
	constexpr RVA MSSYM_B1QE10validRangeB1AA7CommandB2AAA2SAB1UE21NHHHAEAVCommandOutputB3AAAA1Z = 0x0041A1E0;

	// [原型] protected: bool __cdecl Hopper::_tryMoveInItem(class BlockSource & __ptr64,class Container & __ptr64,class ItemStack & __ptr64,int,int,int) __ptr64
	// [符号] ?_tryMoveInItem@Hopper@@IEAA_NAEAVBlockSource@@AEAVContainer@@AEAVItemStack@@HHH@Z
	constexpr RVA MSSYM_B2QUE13tryMoveInItemB1AA6HopperB2AAA4IEAAB1UE16NAEAVBlockSourceB2AAE13AEAVContainerB2AAE13AEAVItemStackB2AAA3HHHB1AA1Z = 0x006D0120;

	// [原型] public: virtual void __cdecl HopperBlockActor::setItem(int,class ItemStack const & __ptr64) __ptr64
	// [符号] ?setItem@HopperBlockActor@@UEAAXHAEBVItemStack@@@Z
	constexpr RVA MSSYM_B1QA7setItemB1AE16HopperBlockActorB2AAE19UEAAXHAEBVItemStackB3AAAA1Z = 0x008B8290;

	// [原型] public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl ItemStackBase::getName(void)const __ptr64
	// [符号] ?getName@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
	constexpr RVA MSSYM_B1QA7getNameB1AE13ItemStackBaseB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x007F9540;

	// [原型] public: bool __cdecl Item::useOn(class ItemStack & __ptr64,class Actor & __ptr64,int,int,int,unsigned char,float,float,float)const __ptr64
	// [符号] ?useOn@Item@@QEBA_NAEAVItemStack@@AEAVActor@@HHHEMMM@Z
	constexpr RVA MSSYM_B1QA5useOnB1AA4ItemB2AAA4QEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA7HHHEMMMB1AA1Z = 0x007ED3E0;

	// [原型] public: class BaseCircuitComponent * __ptr64 __cdecl CircuitSceneGraph::getBaseComponent(class BlockPos const & __ptr64) __ptr64
	// [符号] ?getBaseComponent@CircuitSceneGraph@@QEAAPEAVBaseCircuitComponent@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B8EAB0;

	// [原型] public: void __cdecl CircuitSystem::evaluate(class BlockSource * __ptr64) __ptr64
	// [符号] ?evaluate@CircuitSystem@@QEAAXPEAVBlockSource@@@Z
	constexpr RVA MSSYM_B1QA8evaluateB1AE13CircuitSystemB2AAE20QEAAXPEAVBlockSourceB3AAAA1Z = 0x00B93B50;

	// [原型] public: virtual bool __cdecl ConsumerComponent::evaluate(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
	// [符号] ?evaluate@ConsumerComponent@@UEAA_NAEAVCircuitSystem@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QA8evaluateB1AE17ConsumerComponentB2AAA4UEAAB1UE18NAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B94F60;

	// [原型] public: virtual bool __cdecl TransporterComponent::evaluate(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
	// [符号] ?evaluate@TransporterComponent@@UEAA_NAEAVCircuitSystem@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QA8evaluateB1AE20TransporterComponentB2AAA4UEAAB1UE18NAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B973B0;

	// [原型] public: virtual bool __cdecl RedstoneTorchCapacitor::evaluate(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
	// [符号] ?evaluate@RedstoneTorchCapacitor@@UEAA_NAEAVCircuitSystem@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QA8evaluateB1AE22RedstoneTorchCapacitorB2AAA4UEAAB1UE18NAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B95A30;

	// [原型] public: virtual void __cdecl TransporterComponent::cacheValues(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
	// [符号] ?cacheValues@TransporterComponent@@UEAAXAEAVCircuitSystem@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QE11cacheValuesB1AE20TransporterComponentB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B97340;

	// [原型] public: virtual void __cdecl ComparatorCapacitor::cacheValues(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
	// [符号] ?cacheValues@ComparatorCapacitor@@UEAAXAEAVCircuitSystem@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QE11cacheValuesB1AE19ComparatorCapacitorB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B94E50;

	// [原型] public: virtual void __cdecl RepeaterCapacitor::cacheValues(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
	// [符号] ?cacheValues@RepeaterCapacitor@@UEAAXAEAVCircuitSystem@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QE11cacheValuesB1AE17RepeaterCapacitorB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B96D20;

	// [原型] public: virtual void __cdecl RedstoneTorchCapacitor::cacheValues(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
	// [符号] ?cacheValues@RedstoneTorchCapacitor@@UEAAXAEAVCircuitSystem@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QE11cacheValuesB1AE22RedstoneTorchCapacitorB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B95830;

	// [原型] private: int __cdecl RedstoneTorchCapacitor::FindStrongestStrength(class BlockPos const & __ptr64,class CircuitSystem & __ptr64,bool & __ptr64) __ptr64
	// [符号] ?FindStrongestStrength@RedstoneTorchCapacitor@@AEAAHAEBVBlockPos@@AEAVCircuitSystem@@AEA_N@Z
	constexpr RVA MSSYM_B1QE21FindStrongestStrengthB1AE22RedstoneTorchCapacitorB2AAE17AEAAHAEBVBlockPosB2AAE17AEAVCircuitSystemB2AAA3AEAB1UA1NB1AA1Z = 0x00B95AA0;

	// [原型] public: virtual void __cdecl Actor::setPos(class Vec3 const & __ptr64) __ptr64
	// [符号] ?setPos@Actor@@UEAAXAEBVVec3@@@Z
	constexpr RVA MSSYM_B1QA6setPosB1AA5ActorB2AAE13UEAAXAEBVVec3B3AAAA1Z = 0x00554A20;

	// [原型] private: class std::unique_ptr<class Actor,struct std::default_delete<class Actor> > __cdecl ActorFactory::_constructActor(struct ActorDefinitionIdentifier const & __ptr64,class Vec3 const & __ptr64,class Vec2 const & __ptr64) __ptr64
	// [符号] ?_constructActor@ActorFactory@@AEAA?AV?$unique_ptr@VActor@@U?$default_delete@VActor@@@std@@@std@@AEBUActorDefinitionIdentifier@@AEBVVec3@@AEBVVec2@@@Z
	constexpr RVA MSSYM_MD5_4ad35b002b3931f6af40cb4fe59053ef = 0x005FDF40;

	// [原型] private: void __cdecl Core::Random::_setSeed(unsigned int) __ptr64
	// [符号] ?_setSeed@Random@Core@@AEAAXI@Z
	constexpr RVA MSSYM_B2QUA7setSeedB1AA6RandomB1AA4CoreB2AAA6AEAAXIB1AA1Z = 0x00163ED0;

	// [原型] private: unsigned int __cdecl Core::Random::_genRandInt32(void) __ptr64
	// [符号] ?_genRandInt32@Random@Core@@AEAAIXZ
	constexpr RVA MSSYM_B2QUE12genRandInt32B1AA6RandomB1AA4CoreB2AAA7AEAAIXZ = 0x001B0070;

}

// 文件结束
