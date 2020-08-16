
#pragma once

namespace SymHook{
	using RVA = unsigned int;

	// [ԭ��] private: static class std::unordered_map<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class SharedPtr<class BlockLegacy>,struct std::hash<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,struct std::equal_to<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class SharedPtr<class BlockLegacy> > > > BlockTypeRegistry::mBlockLookupMap
	// [����] ?mBlockLookupMap@BlockTypeRegistry@@0V?$unordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$SharedPtr@VBlockLegacy@@@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$SharedPtr@VBlockLegacy@@@@@std@@@2@@std@@A
	constexpr RVA MSSYM_MD5_ceb8b47184006e4d7622b39978535236 = 0x0191AD20;

	// [ԭ��] public: virtual void __cdecl MinecraftEventing::fireEventPlayerMessageChat(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
	// [����] ?fireEventPlayerMessageChat@MinecraftEventing@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z
	constexpr RVA MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334 = 0x002EA910;

	// [ԭ��] public: void __cdecl Level::spawnParticleEffect(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class Vec3 const & __ptr64,class Dimension * __ptr64) __ptr64
	// [����] ?spawnParticleEffect@Level@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVVec3@@PEAVDimension@@@Z
	constexpr RVA MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb = 0x00A75510;

	// [ԭ��] void __cdecl CommandUtils::displayLocalizableMessage(bool,class Player & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > const & __ptr64)
	// [����] ?displayLocalizableMessage@CommandUtils@@YAX_NAEAVPlayer@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@@Z
	constexpr RVA MSSYM_MD5_24be62e9330073695808606844de0d99 = 0x00442330;

	// [ԭ��] public: virtual int __cdecl ServerPlayer::tickWorld(struct Tick const & __ptr64) __ptr64
	// [����] ?tickWorld@ServerPlayer@@UEAAHAEBUTick@@@Z
	constexpr RVA MSSYM_B1QA9tickWorldB1AE12ServerPlayerB2AAE13UEAAHAEBUTickB3AAAA1Z = 0x004E9A30;

	// [ԭ��] public: virtual void __cdecl Dimension::tick(void) __ptr64
	// [����] ?tick@Dimension@@UEAAXXZ
	constexpr RVA MSSYM_B1QA4tickB1AA9DimensionB2AAA7UEAAXXZ = 0x00A5F260;

	// [ԭ��] public: virtual void __cdecl Level::tick(void) __ptr64
	// [����] ?tick@Level@@UEAAXXZ
	constexpr RVA MSSYM_B1QA4tickB1AA5LevelB2AAA7UEAAXXZ = 0x00A718F0;

	// [ԭ��] public: void __cdecl LevelChunk::tick(class BlockSource & __ptr64,struct Tick const & __ptr64) __ptr64
	// [����] ?tick@LevelChunk@@QEAAXAEAVBlockSource@@AEBUTick@@@Z
	constexpr RVA MSSYM_B1QA4tickB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB2AAA8AEBUTickB3AAAA1Z = 0x00A2C880;

	// [ԭ��] public: void __cdecl LevelChunk::tickBlocks(class BlockSource & __ptr64) __ptr64
	// [����] ?tickBlocks@LevelChunk@@QEAAXAEAVBlockSource@@@Z
	constexpr RVA MSSYM_B1QE10tickBlocksB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z = 0x00A2D760;

	// [ԭ��] public: void __cdecl LevelChunk::tickBlockEntities(class BlockSource & __ptr64) __ptr64
	// [����] ?tickBlockEntities@LevelChunk@@QEAAXAEAVBlockSource@@@Z
	constexpr RVA MSSYM_B1QE17tickBlockEntitiesB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z = 0x00A327B0;

	// [ԭ��] public: void __cdecl Spawner::tick(class BlockSource & __ptr64,class LevelChunk const & __ptr64) __ptr64
	// [����] ?tick@Spawner@@QEAAXAEAVBlockSource@@AEBVLevelChunk@@@Z
	constexpr RVA MSSYM_B1QA4tickB1AA7SpawnerB2AAE20QEAAXAEAVBlockSourceB2AAE14AEBVLevelChunkB3AAAA1Z = 0x00B38310;

	// [ԭ��] public: bool __cdecl BlockTickingQueue::tickPendingTicks(class BlockSource & __ptr64,struct Tick const & __ptr64,int,bool) __ptr64
	// [����] ?tickPendingTicks@BlockTickingQueue@@QEAA_NAEAVBlockSource@@AEBUTick@@H_N@Z
	constexpr RVA MSSYM_B1QE16tickPendingTicksB1AE17BlockTickingQueueB2AAA4QEAAB1UE16NAEAVBlockSourceB2AAA8AEBUTickB2AAA1HB1UA1NB1AA1Z = 0x00A1C5E0;

	// [ԭ��] public: virtual void __cdecl Dimension::tickRedstone(void) __ptr64
	// [����] ?tickRedstone@Dimension@@UEAAXXZ
	constexpr RVA MSSYM_B1QE12tickRedstoneB1AA9DimensionB2AAA7UEAAXXZ = 0x00A5EEB0;

	// [ԭ��] public: virtual void __cdecl Actor::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64) __ptr64
	// [����] ?getDebugText@Actor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z
	constexpr RVA MSSYM_MD5_f04fad6bac034f1e861181d3580320f2 = 0x00566170;

	// [ԭ��] public: virtual class Vec3 const & __ptr64 __cdecl Actor::getPos(void)const __ptr64
	// [����] ?getPos@Actor@@UEBAAEBVVec3@@XZ
	constexpr RVA MSSYM_B1QA6getPosB1AA5ActorB2AAE12UEBAAEBVVec3B2AAA2XZ = 0x00551080;

	// [ԭ��] public: virtual bool __cdecl Actor::attack(class Actor & __ptr64) __ptr64
	// [����] ?attack@Actor@@UEAA_NAEAV1@@Z
	constexpr RVA MSSYM_B1QA6attackB1AA5ActorB2AAA4UEAAB1UA6NAEAV1B2AAA1Z = 0x0054D230;

	// [ԭ��] public: virtual bool __cdecl Player::attack(class Actor & __ptr64) __ptr64
	// [����] ?attack@Player@@UEAA_NAEAVActor@@@Z
	constexpr RVA MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z = 0x00718BD0;

	// [ԭ��] public: void __cdecl Explosion::explode(void) __ptr64
	// [����] ?explode@Explosion@@QEAAXXZ
	constexpr RVA MSSYM_B1QA7explodeB1AA9ExplosionB2AAA7QEAAXXZ = 0x00A65710;

	// [ԭ��] protected: void __cdecl Actor::_refreshAABB(void) __ptr64
	// [����] ?_refreshAABB@Actor@@IEAAXXZ
	constexpr RVA MSSYM_B2QUE11refreshAABBB1AA5ActorB2AAA7IEAAXXZ = 0x00554F40;

	// [ԭ��] private: virtual bool __cdecl DyePowderItem::_useOn(class ItemStack & __ptr64,class Actor & __ptr64,class BlockPos,unsigned char,float,float,float)const __ptr64
	// [����] ?_useOn@DyePowderItem@@EEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EMMM@Z
	constexpr RVA MSSYM_B2QUA5useOnB1AE13DyePowderItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z = 0x007D1EB0;

	// [ԭ��] private: virtual bool __cdecl RedStoneDustItem::_useOn(class ItemStack & __ptr64,class Actor & __ptr64,class BlockPos,unsigned char,float,float,float)const __ptr64
	// [����] ?_useOn@RedStoneDustItem@@EEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EMMM@Z
	constexpr RVA MSSYM_B2QUA5useOnB1AE16RedStoneDustItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z = 0x00805FC0;

	// [ԭ��] public: class Block const & __ptr64 __cdecl BlockSource::getBlock(class BlockPos const & __ptr64)const __ptr64
	// [����] ?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAE12AEBVBlockPosB3AAAA1Z = 0x00A12520;

	// [ԭ��] public: class Block const & __ptr64 __cdecl BlockSource::getBlock(int,int,int)const __ptr64
	// [����] ?getBlock@BlockSource@@QEBAAEBVBlock@@HHH@Z
	constexpr RVA MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAA3HHHB1AA1Z = 0x00A19830;

	// [ԭ��] public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Block::toDebugString(void)const __ptr64
	// [����] ?toDebugString@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
	constexpr RVA MSSYM_B1QE13toDebugStringB1AA5BlockB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x008D39D0;

	// [ԭ��] public: bool __cdecl BlockSource::setBlock(int,int,int,class Block const & __ptr64,int) __ptr64
	// [����] ?setBlock@BlockSource@@QEAA_NHHHAEBVBlock@@H@Z
	constexpr RVA MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NHHHAEBVBlockB2AAA1HB1AA1Z = 0x00A125A0;

	// [ԭ��] private: virtual bool __cdecl ShovelItem::_useOn(class ItemStack & __ptr64,class Actor & __ptr64,class BlockPos,unsigned char,float,float,float)const __ptr64
	// [����] ?_useOn@ShovelItem@@EEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EMMM@Z
	constexpr RVA MSSYM_B2QUA5useOnB1AE10ShovelItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z = 0x00809710;

	// [ԭ��] public: virtual void __cdecl SpongeBlock::onPlace(class BlockSource & __ptr64,class BlockPos const & __ptr64)const __ptr64
	// [����] ?onPlace@SpongeBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QA7onPlaceB1AE11SpongeBlockB2AAE20UEBAXAEAVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z = 0x009C9F10;

	// [ԭ��] public: void __cdecl Village::tick(struct Tick,class BlockSource & __ptr64) __ptr64
	// [����] ?tick@Village@@QEAAXUTick@@AEAVBlockSource@@@Z
	constexpr RVA MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z = 0x00641170;

	// [ԭ��] public: float __cdecl Village::getApproximateRadius(void)const __ptr64
	// [����] ?getApproximateRadius@Village@@QEBAMXZ
	constexpr RVA MSSYM_B1QE20getApproximateRadiusB1AA7VillageB2AAA7QEBAMXZ = 0x00641E70;

	// [ԭ��] public: virtual void __cdecl VillagerV2::buildDebugInfo(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > & __ptr64)const __ptr64
	// [����] ?buildDebugInfo@VillagerV2@@UEBAXAEAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
	constexpr RVA MSSYM_B1QE14buildDebugInfoB1AE10VillagerV2B2AAA9UEBAXAEAVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z = 0x00707190;

	// [ԭ��] public: static bool __cdecl Village::isVillagePOI(class BlockSource const & __ptr64,class BlockPos const & __ptr64)
	// [����] ?isVillagePOI@Village@@SA_NAEBVBlockSource@@AEBVBlockPos@@@Z
	constexpr RVA MSSYM_B1QE12isVillagePOIB1AA7VillageB2AAA2SAB1UE16NAEBVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z = 0x0064C580;

	// [ԭ��] public: class Mob * __ptr64 __cdecl Spawner::spawnMob(class BlockSource & __ptr64,struct ActorDefinitionIdentifier const & __ptr64,class Actor * __ptr64,class Vec3 const & __ptr64,bool,bool,bool) __ptr64
	// [����] ?spawnMob@Spawner@@QEAAPEAVMob@@AEAVBlockSource@@AEBUActorDefinitionIdentifier@@PEAVActor@@AEBVVec3@@_N44@Z
	constexpr RVA MSSYM_B1QA8spawnMobB1AA7SpawnerB2AAE11QEAAPEAVMobB2AAE15AEAVBlockSourceB2AAE29AEBUActorDefinitionIdentifierB2AAA9PEAVActorB2AAA8AEBVVec3B3AAUA3N44B1AA1Z = 0x00B35930;
}

