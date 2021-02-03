// ���ļ�������PDB�������ɡ�
// ע�⣺
// �����κ�ķ���ԭ�Ϳ������󣬽����ο���
// �����ķ��Ž������Ӧ��md5ֵ��ʾ�÷��Ŷ�Ӧ�ı�ʶ����
#pragma once

namespace SymHook {
    using RVA = unsigned int;

    // [ԭ��] private: static class std::unordered_map<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class SharedPtr<class BlockLegacy>,struct std::hash<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,struct std::equal_to<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class SharedPtr<class BlockLegacy> > > > BlockTypeRegistry::mBlockLookupMap
    // [����] ?mBlockLookupMap@BlockTypeRegistry@@0V?$unordered_map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$SharedPtr@VBlockLegacy@@@@U?$hash@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@U?$equal_to@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$SharedPtr@VBlockLegacy@@@@@std@@@2@@std@@A
    constexpr RVA MSSYM_MD5_ceb8b47184006e4d7622b39978535236 = 0x01973620;

    // [ԭ��] public: virtual void __cdecl MinecraftEventing::fireEventPlayerMessageChat(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
    // [����] ?fireEventPlayerMessageChat@MinecraftEventing@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z
    constexpr RVA MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334 = 0x002EFE60;

    // [ԭ��] public: void __cdecl Level::spawnParticleEffect(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class Vec3 const & __ptr64,class Dimension * __ptr64) __ptr64
    // [����] ?spawnParticleEffect@Level@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVVec3@@PEAVDimension@@@Z
    constexpr RVA MSSYM_MD5_a2fdc6a066bbe9a360c9c9d76725a8fb = 0x00A79650;

    // [ԭ��] void __cdecl CommandUtils::displayLocalizableMessage(bool,class Player & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > const & __ptr64)
    // [����] ?displayLocalizableMessage@CommandUtils@@YAX_NAEAVPlayer@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@@Z
    constexpr RVA MSSYM_MD5_24be62e9330073695808606844de0d99 = 0x00445CB0;

    // [ԭ��] public: virtual void __cdecl ServerLevel::tick(void) __ptr64
    // [����] ?tick@ServerLevel@@UEAAXXZ
    constexpr RVA MSSYM_B1QA4tickB1AE11ServerLevelB2AAA7UEAAXXZ = 0x004EA570;

    // [ԭ��] public: virtual int __cdecl ServerPlayer::tickWorld(struct Tick const & __ptr64) __ptr64
    // [����] ?tickWorld@ServerPlayer@@UEAAHAEBUTick@@@Z
    constexpr RVA MSSYM_B1QA9tickWorldB1AE12ServerPlayerB2AAE13UEAAHAEBUTickB3AAAA1Z = 0x004ED3C0;

    // [ԭ��] public: virtual void __cdecl Dimension::tick(void) __ptr64
    // [����] ?tick@Dimension@@UEAAXXZ
    constexpr RVA MSSYM_B1QA4tickB1AA9DimensionB2AAA7UEAAXXZ = 0x00A633C0;

    // [ԭ��] public: virtual void __cdecl Level::tick(void) __ptr64
    // [����] ?tick@Level@@UEAAXXZ
    constexpr RVA MSSYM_B1QA4tickB1AA5LevelB2AAA7UEAAXXZ = 0x00A75A30;

    // [ԭ��] public: void __cdecl LevelChunk::tick(class BlockSource & __ptr64,struct Tick const & __ptr64) __ptr64
    // [����] ?tick@LevelChunk@@QEAAXAEAVBlockSource@@AEBUTick@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB2AAA8AEBUTickB3AAAA1Z = 0x00A30750;

    // [ԭ��] public: void __cdecl LevelChunk::tickBlocks(class BlockSource & __ptr64) __ptr64
    // [����] ?tickBlocks@LevelChunk@@QEAAXAEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QE10tickBlocksB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z = 0x00A31630;

    // [ԭ��] public: void __cdecl LevelChunk::tickBlockEntities(class BlockSource & __ptr64) __ptr64
    // [����] ?tickBlockEntities@LevelChunk@@QEAAXAEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QE17tickBlockEntitiesB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z = 0x00A36690;

    // [ԭ��] public: void __cdecl Spawner::tick(class BlockSource & __ptr64,class LevelChunk const & __ptr64) __ptr64
    // [����] ?tick@Spawner@@QEAAXAEAVBlockSource@@AEBVLevelChunk@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AA7SpawnerB2AAE20QEAAXAEAVBlockSourceB2AAE14AEBVLevelChunkB3AAAA1Z = 0x00B3C410;

    // [ԭ��] public: bool __cdecl BlockTickingQueue::tickPendingTicks(class BlockSource & __ptr64,struct Tick const & __ptr64,int,bool) __ptr64
    // [����] ?tickPendingTicks@BlockTickingQueue@@QEAA_NAEAVBlockSource@@AEBUTick@@H_N@Z
    constexpr RVA MSSYM_B1QE16tickPendingTicksB1AE17BlockTickingQueueB2AAA4QEAAB1UE16NAEAVBlockSourceB2AAA8AEBUTickB2AAA1HB1UA1NB1AA1Z = 0x00A204D0;

    // [ԭ��] public: virtual void __cdecl Dimension::tickRedstone(void) __ptr64
    // [����] ?tickRedstone@Dimension@@UEAAXXZ
    constexpr RVA MSSYM_B1QE12tickRedstoneB1AA9DimensionB2AAA7UEAAXXZ = 0x00A63010;

    // [ԭ��] public: void __cdecl Level::tickEntities(void) __ptr64
    // [����] ?tickEntities@Level@@QEAAXXZ
    constexpr RVA MSSYM_B1QE12tickEntitiesB1AA5LevelB2AAA7QEAAXXZ = 0x00A79140;

    // [ԭ��] public: void __cdecl EntitySystems::tick(class EntityRegistry & __ptr64) __ptr64
    // [����] ?tick@EntitySystems@@QEAAXAEAVEntityRegistry@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AE13EntitySystemsB2AAE23QEAAXAEAVEntityRegistryB3AAAA1Z = 0x002B81D0;

    // [ԭ��] public: virtual void __cdecl BlockActor::tick(class BlockSource & __ptr64) __ptr64
    // [����] ?tick@BlockActor@@UEAAXAEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AE10BlockActorB2AAE20UEAAXAEAVBlockSourceB3AAAA1Z = 0x0089D990;

    // [ԭ��] public: bool __cdecl Actor::tick(class BlockSource & __ptr64) __ptr64
    // [����] ?tick@Actor@@QEAA_NAEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AA5ActorB2AAA4QEAAB1UE16NAEAVBlockSourceB3AAAA1Z = 0x00556BB0;

    // [ԭ��] public: virtual void __cdecl Actor::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64) __ptr64
    // [����] ?getDebugText@Actor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z
    constexpr RVA MSSYM_MD5_f04fad6bac034f1e861181d3580320f2 = 0x00569BC0;

    // [ԭ��] public: virtual class Vec3 const & __ptr64 __cdecl Actor::getPos(void)const __ptr64
    // [����] ?getPos@Actor@@UEBAAEBVVec3@@XZ
    constexpr RVA MSSYM_B1QA6getPosB1AA5ActorB2AAE12UEBAAEBVVec3B2AAA2XZ = 0x00554A80;

    // [ԭ��] public: virtual bool __cdecl Actor::attack(class Actor & __ptr64) __ptr64
    // [����] ?attack@Actor@@UEAA_NAEAV1@@Z
    constexpr RVA MSSYM_B1QA6attackB1AA5ActorB2AAA4UEAAB1UA6NAEAV1B2AAA1Z = 0x00550BF0;

    // [ԭ��] public: virtual bool __cdecl Player::attack(class Actor & __ptr64) __ptr64
    // [����] ?attack@Player@@UEAA_NAEAVActor@@@Z
    constexpr RVA MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z = 0x0071BF40;

    // [ԭ��] public: void __cdecl Explosion::explode(void) __ptr64
    // [����] ?explode@Explosion@@QEAAXXZ
    constexpr RVA MSSYM_B1QA7explodeB1AA9ExplosionB2AAA7QEAAXXZ = 0x00A69850;

    // [ԭ��] public: virtual void __cdecl Actor::setNameTag(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
    // [����] ?setNameTag@Actor@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
    constexpr RVA MSSYM_B1QE10setNameTagB1AA5ActorB2AAA9UEAAXAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z = 0x00562DA0;

    // [ԭ��] public: virtual void __cdecl Mob::buildDebugInfo(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > & __ptr64)const __ptr64
    // [����] ?buildDebugInfo@Mob@@UEBAXAEAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
    constexpr RVA MSSYM_B1QE14buildDebugInfoB1AA3MobB2AAA9UEBAXAEAVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z = 0x006F4960;

    // [ԭ��] public: class Vec3 __cdecl Actor::getViewVector(float)const __ptr64
    // [����] ?getViewVector@Actor@@QEBA?AVVec3@@M@Z
    constexpr RVA MSSYM_B1QE13getViewVectorB1AA5ActorB2AAA4QEBAB1QA6AVVec3B2AAA1MB1AA1Z = 0x005552A0;

    // [ԭ��] public: virtual class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64 __cdecl Actor::getNameTag(void)const __ptr64
    // [����] ?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
    constexpr RVA MSSYM_B1QE10getNameTagB1AA5ActorB2AAA8UEBAAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x00562BC0;

    // [ԭ��] public: virtual void __cdecl ServerPlayer::setPlayerGameType(enum GameType) __ptr64
    // [����] ?setPlayerGameType@ServerPlayer@@UEAAXW4GameType@@@Z
    constexpr RVA MSSYM_B1QE17setPlayerGameTypeB1AE12ServerPlayerB2AAE15UEAAXW4GameTypeB3AAAA1Z = 0x004F1A20;

    // [ԭ��] public: class Block const & __ptr64 __cdecl BlockSource::getBlock(class BlockPos const & __ptr64)const __ptr64
    // [����] ?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAE12AEBVBlockPosB3AAAA1Z = 0x00A16410;

    // [ԭ��] public: class BlockLegacy const & __ptr64 __cdecl Block::getLegacyBlock(void)const __ptr64
    // [����] ?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ
    constexpr RVA MSSYM_B1QE14getLegacyBlockB1AA5BlockB2AAE19QEBAAEBVBlockLegacyB2AAA2XZ = 0x000BBB60;

    // [ԭ��] public: bool __cdecl BlockSource::setBlock(int,int,int,class Block const & __ptr64,int) __ptr64
    // [����] ?setBlock@BlockSource@@QEAA_NHHHAEBVBlock@@H@Z
    constexpr RVA MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NHHHAEBVBlockB2AAA1HB1AA1Z = 0x00A16490;

    // [ԭ��] public: bool __cdecl BlockSource::setBlock(class BlockPos const & __ptr64,class Block const & __ptr64,int,struct ActorBlockSyncMessage const * __ptr64) __ptr64
    // [����] ?setBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@HPEBUActorBlockSyncMessage@@@Z
    constexpr RVA MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NAEBVBlockPosB2AAA9AEBVBlockB2AAE26HPEBUActorBlockSyncMessageB3AAAA1Z = 0x00A164E0;

    // [ԭ��] private: virtual bool __cdecl ShovelItem::_useOn(class ItemStack & __ptr64,class Actor & __ptr64,class BlockPos,unsigned char,float,float,float)const __ptr64
    // [����] ?_useOn@ShovelItem@@EEBA_NAEAVItemStack@@AEAVActor@@VBlockPos@@EMMM@Z
    constexpr RVA MSSYM_B2QUA5useOnB1AE10ShovelItemB2AAA4EEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA9VBlockPosB2AAA4EMMMB1AA1Z = 0x0080CF30;

    // [ԭ��] public: void __cdecl BlockSource::updateNeighborsAt(class BlockPos const & __ptr64) __ptr64
    // [����] ?updateNeighborsAt@BlockSource@@QEAAXAEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z = 0x00A176C0;

    // [ԭ��] public: virtual enum EventResult __cdecl VanillaServerGameplayEventListener::onBlockPlacedByPlayer(class Player & __ptr64,class Block const & __ptr64,class BlockPos const & __ptr64,bool) __ptr64
    // [����] ?onBlockPlacedByPlayer@VanillaServerGameplayEventListener@@UEAA?AW4EventResult@@AEAVPlayer@@AEBVBlock@@AEBVBlockPos@@_N@Z
    constexpr RVA MSSYM_B1QE21onBlockPlacedByPlayerB1AE34VanillaServerGameplayEventListenerB2AAA4UEAAB1QE14AW4EventResultB2AAE10AEAVPlayerB2AAA9AEBVBlockB2AAE12AEBVBlockPosB3AAUA1NB1AA1Z = 0x00BD5270;

    // [ԭ��] private: bool __cdecl GameMode::_destroyBlockInternal(class BlockPos const & __ptr64,unsigned char) __ptr64
    // [����] ?_destroyBlockInternal@GameMode@@AEAA_NAEBVBlockPos@@E@Z
    constexpr RVA MSSYM_B2QUE20destroyBlockInternalB1AA8GameModeB2AAA4AEAAB1UE13NAEBVBlockPosB2AAA1EB1AA1Z = 0x00775EB0;

    // [ԭ��] public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Block::toDebugString(void)const __ptr64
    // [����] ?toDebugString@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
    constexpr RVA MSSYM_B1QE13toDebugStringB1AA5BlockB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x008D7100;

    // [ԭ��] public: virtual class AABB const & __ptr64 __cdecl BlockLegacy::getOutline(class BlockSource & __ptr64,class BlockPos const & __ptr64,class AABB & __ptr64)const __ptr64
    // [����] ?getOutline@BlockLegacy@@UEBAAEBVAABB@@AEAVBlockSource@@AEBVBlockPos@@AEAV2@@Z
    constexpr RVA MSSYM_B1QE10getOutlineB1AE11BlockLegacyB2AAE12UEBAAEBVAABBB2AAE15AEAVBlockSourceB2AAE12AEBVBlockPosB2AAA5AEAV2B2AAA1Z = 0x008DA4A0;

    // [ԭ��] public: void __cdecl BlockLegacy::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64,class BlockPos const & __ptr64)const __ptr64
    // [����] ?getDebugText@BlockLegacy@@QEBAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_MD5_794b421b4bf67101f7418cd0d78bad83 = 0x008DB770;

    // [ԭ��] public: virtual void __cdecl BlockActor::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64,class BlockPos const & __ptr64) __ptr64
    // [����] ?getDebugText@BlockActor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_MD5_b5a16de43d7486d6e9b23cfb126773a7 = 0x0089DF70;

    // [ԭ��] public: bool __cdecl BlockSource::setExtraBlock(class BlockPos const & __ptr64,class Block const & __ptr64,int) __ptr64
    // [����] ?setExtraBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@H@Z
    constexpr RVA MSSYM_B1QE13setExtraBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NAEBVBlockPosB2AAA9AEBVBlockB2AAA1HB1AA1Z = 0x00A16860;

    // [ԭ��] public: class Block const * __ptr64 __cdecl BlockLegacy::tryGetStateFromLegacyData(unsigned short)const __ptr64
    // [����] ?tryGetStateFromLegacyData@BlockLegacy@@QEBAPEBVBlock@@G@Z
    constexpr RVA MSSYM_B1QE25tryGetStateFromLegacyDataB1AE11BlockLegacyB2AAE13QEBAPEBVBlockB2AAA1GB1AA1Z = 0x008D8BF0;

    // [ԭ��] private: void __cdecl HopperBlockActor::_tick(class BlockSource & __ptr64,int) __ptr64
    // [����] ?_tick@HopperBlockActor@@AEAAXAEAVBlockSource@@H@Z
    constexpr RVA MSSYM_B2QUA4tickB1AE16HopperBlockActorB2AAE20AEAAXAEAVBlockSourceB2AAA1HB1AA1Z = 0x008B7AA0;

    // [ԭ��] public: class Biome & __ptr64 __cdecl BlockSource::getBiome(class BlockPos const & __ptr64) __ptr64
    // [����] ?getBiome@BlockSource@@QEAAAEAVBiome@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QA8getBiomeB1AE11BlockSourceB2AAE13QEAAAEAVBiomeB2AAE12AEBVBlockPosB3AAAA1Z = 0x00A1CFE0;

    // [ԭ��] public: void __cdecl Village::tick(struct Tick,class BlockSource & __ptr64) __ptr64
    // [����] ?tick@Village@@QEAAXUTick@@AEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z = 0x00644680;

    // [ԭ��] public: float __cdecl Village::getApproximateRadius(void)const __ptr64
    // [����] ?getApproximateRadius@Village@@QEBAMXZ
    constexpr RVA MSSYM_B1QE20getApproximateRadiusB1AA7VillageB2AAA7QEBAMXZ = 0x00645380;

    // [ԭ��] public: virtual void __cdecl VillagerV2::buildDebugInfo(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > & __ptr64)const __ptr64
    // [����] ?buildDebugInfo@VillagerV2@@UEBAXAEAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
    constexpr RVA MSSYM_B1QE14buildDebugInfoB1AE10VillagerV2B2AAA9UEBAXAEAVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z = 0x0070A500;

    // [ԭ��] public: static bool __cdecl Village::isVillagePOI(class BlockSource const & __ptr64,class BlockPos const & __ptr64)
    // [����] ?isVillagePOI@Village@@SA_NAEBVBlockSource@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QE12isVillagePOIB1AA7VillageB2AAA2SAB1UE16NAEBVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z = 0x0064FA90;

    // [ԭ��] public: void __cdecl VillageManager::tick(struct Tick const & __ptr64) __ptr64
    // [����] ?tick@VillageManager@@QEAAXAEBUTick@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AE14VillageManagerB2AAE13QEAAXAEBUTickB3AAAA1Z = 0x00652BD0;

    // [ԭ��] public: class std::weak_ptr<class POIInstance> __cdecl VillageManager::getPOI(class BlockPos const & __ptr64)const __ptr64
    // [����] ?getPOI@VillageManager@@QEBA?AV?$weak_ptr@VPOIInstance@@@std@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QA6getPOIB1AE14VillageManagerB2AAA4QEBAB1QA2AVB2QDA4weakB1UA3ptrB1AE12VPOIInstanceB3AAAA3stdB2AAE12AEBVBlockPosB3AAAA1Z = 0x006562E0;

    // [ԭ��] public: unsigned __int64 __cdecl Village::getBedPOICount(void)const __ptr64
    // [����] ?getBedPOICount@Village@@QEBA_KXZ
    constexpr RVA MSSYM_B1QE14getBedPOICountB1AA7VillageB2AAA4QEBAB1UA3KXZ = 0x00645420;

    // [ԭ��] public: class Mob * __ptr64 __cdecl Spawner::spawnMob(class BlockSource & __ptr64,struct ActorDefinitionIdentifier const & __ptr64,class Actor * __ptr64,class Vec3 const & __ptr64,bool,bool,bool) __ptr64
    // [����] ?spawnMob@Spawner@@QEAAPEAVMob@@AEAVBlockSource@@AEBUActorDefinitionIdentifier@@PEAVActor@@AEBVVec3@@_N44@Z
    constexpr RVA MSSYM_B1QA8spawnMobB1AA7SpawnerB2AAE11QEAAPEAVMobB2AAE15AEAVBlockSourceB2AAE29AEBUActorDefinitionIdentifierB2AAA9PEAVActorB2AAA8AEBVVec3B3AAUA3N44B1AA1Z = 0x00B39A30;

    // [ԭ��] public: int __cdecl MobSpawnRules::getSpawnCount(class SpawnConditions const & __ptr64,class BlockSource & __ptr64,class Random & __ptr64,struct MobSpawnHerdInfo const & __ptr64)const __ptr64
    // [����] ?getSpawnCount@MobSpawnRules@@QEBAHAEBVSpawnConditions@@AEAVBlockSource@@AEAVRandom@@AEBUMobSpawnHerdInfo@@@Z
    constexpr RVA MSSYM_B1QE13getSpawnCountB1AE13MobSpawnRulesB2AAE24QEBAHAEBVSpawnConditionsB2AAE15AEAVBlockSourceB2AAE10AEAVRandomB2AAE20AEBUMobSpawnHerdInfoB3AAAA1Z = 0x0085E940;

    // [ԭ��] public: virtual class MobSpawnerData const * __ptr64 __cdecl BlockLegacy::getMobToSpawn(class SpawnConditions const & __ptr64,class BlockSource & __ptr64)const __ptr64
    // [����] ?getMobToSpawn@BlockLegacy@@UEBAPEBVMobSpawnerData@@AEBVSpawnConditions@@AEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QE13getMobToSpawnB1AE11BlockLegacyB2AAE22UEBAPEBVMobSpawnerDataB2AAE19AEBVSpawnConditionsB2AAE15AEAVBlockSourceB3AAAA1Z = 0x008DB2B0;

    // [ԭ��] public: int __cdecl ActorSpawnRuleGroup::getActorSpawnPool(struct ActorDefinitionIdentifier const & __ptr64)const __ptr64
    // [����] ?getActorSpawnPool@ActorSpawnRuleGroup@@QEBAHAEBUActorDefinitionIdentifier@@@Z
    constexpr RVA MSSYM_B1QE17getActorSpawnPoolB1AE19ActorSpawnRuleGroupB2AAE34QEBAHAEBUActorDefinitionIdentifierB3AAAA1Z = 0x00612280;

    // [ԭ��] private: bool __cdecl Spawner::_popCapAllows(class Dimension const & __ptr64,class MobSpawnerData const & __ptr64,bool,bool)const __ptr64
    // [����] ?_popCapAllows@Spawner@@AEBA_NAEBVDimension@@AEBVMobSpawnerData@@_N2@Z
    constexpr RVA MSSYM_B2QUE12popCapAllowsB1AA7SpawnerB2AAA4AEBAB1UE14NAEBVDimensionB2AAE18AEBVMobSpawnerDataB3AAUA2N2B1AA1Z = 0x00B39F00;

    // [ԭ��] private: int __cdecl Spawner::_handlePopulationCap(class MobSpawnerData const * __ptr64,class SpawnConditions const & __ptr64,int) __ptr64
    // [����] ?_handlePopulationCap@Spawner@@AEAAHPEBVMobSpawnerData@@AEBVSpawnConditions@@H@Z
    constexpr RVA MSSYM_B2QUE19handlePopulationCapB1AA7SpawnerB2AAE23AEAAHPEBVMobSpawnerDataB2AAE19AEBVSpawnConditionsB2AAA1HB1AA1Z = 0x00B3BB40;

    // [ԭ��] private: void __cdecl Spawner::_spawnStructureMob(class BlockSource & __ptr64,class BlockPos const & __ptr64,struct LevelChunk::HardcodedSpawningArea const & __ptr64,class SpawnConditions const & __ptr64) __ptr64
    // [����] ?_spawnStructureMob@Spawner@@AEAAXAEAVBlockSource@@AEBVBlockPos@@AEBUHardcodedSpawningArea@LevelChunk@@AEBVSpawnConditions@@@Z
    constexpr RVA MSSYM_B2QUE17spawnStructureMobB1AA7SpawnerB2AAE20AEAAXAEAVBlockSourceB2AAE12AEBVBlockPosB2AAE25AEBUHardcodedSpawningAreaB1AE10LevelChunkB2AAE19AEBVSpawnConditionsB3AAAA1Z = 0x00B3B6F0;

    // [ԭ��] public: static bool __cdecl Spawner::findNextSpawnBlockUnder(class BlockSource const & __ptr64,class BlockPos & __ptr64,enum MaterialType,enum SpawnBlockRequirements)
    // [����] ?findNextSpawnBlockUnder@Spawner@@SA_NAEBVBlockSource@@AEAVBlockPos@@W4MaterialType@@W4SpawnBlockRequirements@@@Z
    constexpr RVA MSSYM_B1QE23findNextSpawnBlockUnderB1AA7SpawnerB2AAA2SAB1UE16NAEBVBlockSourceB2AAE12AEAVBlockPosB2AAE14W4MaterialTypeB2AAE24W4SpawnBlockRequirementsB3AAAA1Z = 0x00B3A9D0;

    // [ԭ��] protected: bool __cdecl Hopper::_tryMoveInItem(class BlockSource & __ptr64,class Container & __ptr64,class ItemStack & __ptr64,int,int,int) __ptr64
    // [����] ?_tryMoveInItem@Hopper@@IEAA_NAEAVBlockSource@@AEAVContainer@@AEAVItemStack@@HHH@Z
    constexpr RVA MSSYM_B2QUE13tryMoveInItemB1AA6HopperB2AAA4IEAAB1UE16NAEAVBlockSourceB2AAE13AEAVContainerB2AAE13AEAVItemStackB2AAA3HHHB1AA1Z = 0x006D0120;

    // [ԭ��] public: virtual void __cdecl HopperBlockActor::setItem(int,class ItemStack const & __ptr64) __ptr64
    // [����] ?setItem@HopperBlockActor@@UEAAXHAEBVItemStack@@@Z
    constexpr RVA MSSYM_B1QA7setItemB1AE16HopperBlockActorB2AAE19UEAAXHAEBVItemStackB3AAAA1Z = 0x008B8290;

    // [ԭ��] public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl ItemStackBase::getName(void)const __ptr64
    // [����] ?getName@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
    constexpr RVA MSSYM_B1QA7getNameB1AE13ItemStackBaseB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x007F9540;

    // [ԭ��] public: bool __cdecl Item::useOn(class ItemStack & __ptr64,class Actor & __ptr64,int,int,int,unsigned char,float,float,float)const __ptr64
    // [����] ?useOn@Item@@QEBA_NAEAVItemStack@@AEAVActor@@HHHEMMM@Z
    constexpr RVA MSSYM_B1QA5useOnB1AA4ItemB2AAA4QEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA7HHHEMMMB1AA1Z = 0x007ED3E0;

    // [ԭ��] public: class BaseCircuitComponent * __ptr64 __cdecl CircuitSceneGraph::getBaseComponent(class BlockPos const & __ptr64) __ptr64
    // [����] ?getBaseComponent@CircuitSceneGraph@@QEAAPEAVBaseCircuitComponent@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B8EAB0;

    // [ԭ��] public: void __cdecl CircuitSystem::evaluate(class BlockSource * __ptr64) __ptr64
    // [����] ?evaluate@CircuitSystem@@QEAAXPEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QA8evaluateB1AE13CircuitSystemB2AAE20QEAAXPEAVBlockSourceB3AAAA1Z = 0x00B93B50;

    // [ԭ��] public: virtual bool __cdecl ConsumerComponent::evaluate(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
    // [����] ?evaluate@ConsumerComponent@@UEAA_NAEAVCircuitSystem@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QA8evaluateB1AE17ConsumerComponentB2AAA4UEAAB1UE18NAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B94F60;

    // [ԭ��] public: virtual bool __cdecl TransporterComponent::evaluate(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
    // [����] ?evaluate@TransporterComponent@@UEAA_NAEAVCircuitSystem@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QA8evaluateB1AE20TransporterComponentB2AAA4UEAAB1UE18NAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B973B0;

    // [ԭ��] public: virtual bool __cdecl RedstoneTorchCapacitor::evaluate(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
    // [����] ?evaluate@RedstoneTorchCapacitor@@UEAA_NAEAVCircuitSystem@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QA8evaluateB1AE22RedstoneTorchCapacitorB2AAA4UEAAB1UE18NAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B95A30;

    // [ԭ��] public: virtual void __cdecl TransporterComponent::cacheValues(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
    // [����] ?cacheValues@TransporterComponent@@UEAAXAEAVCircuitSystem@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QE11cacheValuesB1AE20TransporterComponentB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B97340;

    // [ԭ��] public: virtual void __cdecl ComparatorCapacitor::cacheValues(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
    // [����] ?cacheValues@ComparatorCapacitor@@UEAAXAEAVCircuitSystem@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QE11cacheValuesB1AE19ComparatorCapacitorB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B94E50;

    // [ԭ��] public: virtual void __cdecl RepeaterCapacitor::cacheValues(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
    // [����] ?cacheValues@RepeaterCapacitor@@UEAAXAEAVCircuitSystem@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QE11cacheValuesB1AE17RepeaterCapacitorB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B96D20;

    // [ԭ��] public: virtual void __cdecl RedstoneTorchCapacitor::cacheValues(class CircuitSystem & __ptr64,class BlockPos const & __ptr64) __ptr64
    // [����] ?cacheValues@RedstoneTorchCapacitor@@UEAAXAEAVCircuitSystem@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QE11cacheValuesB1AE22RedstoneTorchCapacitorB2AAE22UEAAXAEAVCircuitSystemB2AAE12AEBVBlockPosB3AAAA1Z = 0x00B95830;

    // [ԭ��] private: int __cdecl RedstoneTorchCapacitor::FindStrongestStrength(class BlockPos const & __ptr64,class CircuitSystem & __ptr64,bool & __ptr64) __ptr64
    // [����] ?FindStrongestStrength@RedstoneTorchCapacitor@@AEAAHAEBVBlockPos@@AEAVCircuitSystem@@AEA_N@Z
    constexpr RVA MSSYM_B1QE21FindStrongestStrengthB1AE22RedstoneTorchCapacitorB2AAE17AEAAHAEBVBlockPosB2AAE17AEAVCircuitSystemB2AAA3AEAB1UA1NB1AA1Z = 0x00B95AA0;

    // [ԭ��] public: virtual void __cdecl Actor::setPos(class Vec3 const & __ptr64) __ptr64
    // [����] ?setPos@Actor@@UEAAXAEBVVec3@@@Z
    constexpr RVA MSSYM_B1QA6setPosB1AA5ActorB2AAE13UEAAXAEBVVec3B3AAAA1Z = 0x00554A20;

    // [ԭ��] private: class std::unique_ptr<class Actor,struct std::default_delete<class Actor> > __cdecl ActorFactory::_constructActor(struct ActorDefinitionIdentifier const & __ptr64,class Vec3 const & __ptr64,class Vec2 const & __ptr64) __ptr64
    // [����] ?_constructActor@ActorFactory@@AEAA?AV?$unique_ptr@VActor@@U?$default_delete@VActor@@@std@@@std@@AEBUActorDefinitionIdentifier@@AEBVVec3@@AEBVVec2@@@Z
    constexpr RVA MSSYM_MD5_4ad35b002b3931f6af40cb4fe59053ef = 0x005FDF40;

    // [ԭ��] private: void __cdecl Core::Random::_setSeed(unsigned int) __ptr64
    // [����] ?_setSeed@Random@Core@@AEAAXI@Z
    constexpr RVA MSSYM_B2QUA7setSeedB1AA6RandomB1AA4CoreB2AAA6AEAAXIB1AA1Z = 0x00163ED0;

    // [ԭ��] private: unsigned int __cdecl Core::Random::_genRandInt32(void) __ptr64
    // [����] ?_genRandInt32@Random@Core@@AEAAIXZ
    constexpr RVA MSSYM_B2QUE12genRandInt32B1AA6RandomB1AA4CoreB2AAA7AEAAIXZ = 0x001B0070;

    // [ԭ��] public: enum VanillaBiomeTypes __cdecl Biome::getBiomeType(void)const __ptr64
    // [����] ?getBiomeType@Biome@@QEBA?AW4VanillaBiomeTypes@@XZ
    constexpr RVA MSSYM_B1QE12getBiomeTypeB1AA5BiomeB2AAA4QEBAB1QE20AW4VanillaBiomeTypesB2AAA2XZ = 0x00840C80;

    // [ԭ��] public: virtual void __cdecl GrassBlock::tick(class BlockSource & __ptr64,class BlockPos const & __ptr64,class Random & __ptr64)const __ptr64
    // [����] ?tick@GrassBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@AEAVRandom@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AE10GrassBlockB2AAE20UEBAXAEAVBlockSourceB2AAE12AEBVBlockPosB2AAE10AEAVRandomB3AAAA1Z = 0x0093B500;

    // [ԭ��] public: class Dimension * __ptr64 __cdecl Level::getDimension(class AutomaticID<class Dimension,int>)const __ptr64
    // [����] ?getDimension@Level@@QEBAPEAVDimension@@V?$AutomaticID@VDimension@@H@@@Z
    constexpr RVA MSSYM_B1QE12getDimensionB1AA5LevelB2AAE17QEBAPEAVDimensionB2AAA1VB2QDE11AutomaticIDB1AE10VDimensionB2AAA1HB3AAAA1Z = 0x00A72D50;

    // [ԭ��] public: unsigned __int64 __cdecl NetworkIdentifier::getHash(void)const __ptr64
    // [����] ?getHash@NetworkIdentifier@@QEBA_KXZ
    constexpr RVA MSSYM_B1QA7getHashB1AE17NetworkIdentifierB2AAA4QEBAB1UA3KXZ = 0x00339FB0;

    // [ԭ��] public: virtual void __cdecl ServerNetworkHandler::handle(class NetworkIdentifier const & __ptr64,class CommandRequestPacket const & __ptr64) __ptr64
    // [����] ?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVCommandRequestPacket@@@Z
    constexpr RVA MSSYM_B1QA6handleB1AE20ServerNetworkHandlerB2AAE26UEAAXAEBVNetworkIdentifierB2AAE24AEBVCommandRequestPacketB3AAAA1Z = 0x003A03A0;

    // [ԭ��] public: virtual class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl AutomationPlayerCommandOrigin::getName(void)const __ptr64
    // [����] ?getName@AutomationPlayerCommandOrigin@@UEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
    constexpr RVA MSSYM_B1QA7getNameB1AE29AutomationPlayerCommandOriginB2AAA4UEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x0041EBA0;

    // [ԭ��] public: virtual enum CommandPermissionLevel __cdecl PlayerCommandOrigin::getPermissionsLevel(void)const __ptr64
    // [����] ?getPermissionsLevel@PlayerCommandOrigin@@UEBA?AW4CommandPermissionLevel@@XZ
    constexpr RVA MSSYM_B1QE19getPermissionsLevelB1AE19PlayerCommandOriginB2AAA4UEBAB1QE25AW4CommandPermissionLevelB2AAA2XZ = 0x0041E2C0;

    // [ԭ��] public: void __cdecl CommandRegistry::registerCommand(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,char const * __ptr64,enum CommandPermissionLevel,struct CommandFlag,struct CommandFlag) __ptr64
    // [����] ?registerCommand@CommandRegistry@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEBDW4CommandPermissionLevel@@UCommandFlag@@3@Z
    constexpr RVA MSSYM_MD5_8574de98358ff66b5a913417f44dd706 = 0x0042D260;

    // [ԭ��] public: struct MCRESULT __cdecl MinecraftCommands::executeCommand(class std::shared_ptr<class CommandContext>,bool)const __ptr64
    // [����] ?executeCommand@MinecraftCommands@@QEBA?AUMCRESULT@@V?$shared_ptr@VCommandContext@@@std@@_N@Z
    constexpr RVA MSSYM_B1QE14executeCommandB1AE17MinecraftCommandsB2AAA4QEBAB1QE10AUMCRESULTB2AAA1VB2QDA6sharedB1UA3ptrB1AE15VCommandContextB3AAAA3stdB3AAUA1NB1AA1Z = 0x0045C120;

    // [ԭ��] public: class std::unique_ptr<class CommandContext,struct std::default_delete<class CommandContext> > __cdecl CommandRequestPacket::createCommandContext(class NetworkIdentifier const & __ptr64,class Level & __ptr64,int)const __ptr64
    // [����] ?createCommandContext@CommandRequestPacket@@QEBA?AV?$unique_ptr@VCommandContext@@U?$default_delete@VCommandContext@@@std@@@std@@AEBVNetworkIdentifier@@AEAVLevel@@H@Z
    constexpr RVA MSSYM_MD5_607250778ae0b2889b9591dc98bd2cd0 = 0x0035C140;

    // [ԭ��] private: class std::unique_ptr<class Command,struct std::default_delete<class Command> > __cdecl CommandRegistry::createCommand(struct CommandRegistry::ParseToken const & __ptr64,class CommandOrigin const & __ptr64,int,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > & __ptr64,class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64)const __ptr64
    // [����] ?createCommand@CommandRegistry@@AEBA?AV?$unique_ptr@VCommand@@U?$default_delete@VCommand@@@std@@@std@@AEBUParseToken@1@AEBVCommandOrigin@@HAEAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@AEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@3@@Z
    constexpr RVA MSSYM_MD5_573632dacfa65053246fc05eeebd2c0e = 0x00425350;

    // [ԭ��] public: virtual enum CommandPermissionLevel __cdecl Player::getCommandPermissionLevel(void)const __ptr64
    // [����] ?getCommandPermissionLevel@Player@@UEBA?AW4CommandPermissionLevel@@XZ
    constexpr RVA MSSYM_B1QE25getCommandPermissionLevelB1AA6PlayerB2AAA4UEBAB1QE25AW4CommandPermissionLevelB2AAA2XZ = 0x00718760;

    // [ԭ��] public: virtual int __cdecl StoneSlabBlock::getVariant(class Block const & __ptr64)const __ptr64
    // [����] ?getVariant@StoneSlabBlock@@UEBAHAEBVBlock@@@Z
    constexpr RVA MSSYM_B1QE10getVariantB1AE14StoneSlabBlockB2AAE14UEBAHAEBVBlockB3AAAA1Z = 0x009D36D0;

    // [ԭ��] public: virtual int __cdecl WoodSlabBlock::getVariant(class Block const & __ptr64)const __ptr64
    // [����] ?getVariant@WoodSlabBlock@@UEBAHAEBVBlock@@@Z
    constexpr RVA MSSYM_B1QE10getVariantB1AE13WoodSlabBlockB2AAE14UEBAHAEBVBlockB3AAAA1Z = 0x00A11720;

    // [ԭ��] public: virtual bool __cdecl OceanMonumentFeature::isFeatureChunk(class BiomeSource const & __ptr64,class Random & __ptr64,class ChunkPos const & __ptr64,unsigned int) __ptr64
    // [����] ?isFeatureChunk@OceanMonumentFeature@@UEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@I@Z
    constexpr RVA MSSYM_B1QE14isFeatureChunkB1AE20OceanMonumentFeatureB2AAA4UEAAB1UE16NAEBVBiomeSourceB2AAE10AEAVRandomB2AAE12AEBVChunkPosB2AAA1IB1AA1Z = 0x00ACAB50;

    // [ԭ��] protected: virtual bool __cdecl RandomScatteredLargeFeature::isFeatureChunk(class BiomeSource const & __ptr64,class Random & __ptr64,class ChunkPos const & __ptr64,unsigned int) __ptr64
    // [����] ?isFeatureChunk@RandomScatteredLargeFeature@@MEAA_NAEBVBiomeSource@@AEAVRandom@@AEBVChunkPos@@I@Z
    constexpr RVA MSSYM_B1QE14isFeatureChunkB1AE27RandomScatteredLargeFeatureB2AAA4MEAAB1UE16NAEBVBiomeSourceB2AAE10AEAVRandomB2AAE12AEBVChunkPosB2AAA1IB1AA1Z = 0x00ADD600;

    // [ԭ��] public: virtual class Biome const * __ptr64 __cdecl LayerBiomeSource::getBiome(int,int)const __ptr64
    // [����] ?getBiome@LayerBiomeSource@@UEBAPEBVBiome@@HH@Z
    constexpr RVA MSSYM_B1QA8getBiomeB1AE16LayerBiomeSourceB2AAE13UEBAPEBVBiomeB2AAA2HHB1AA1Z = 0x0086A370;

    // [ԭ��] public: virtual class Biome const * __ptr64 __cdecl FixedBiomeSource::getBiome(int,int)const __ptr64
    // [����] ?getBiome@FixedBiomeSource@@UEBAPEBVBiome@@HH@Z
    constexpr RVA MSSYM_B1QA8getBiomeB1AE16FixedBiomeSourceB2AAE13UEBAPEBVBiomeB2AAA2HHB1AA1Z = 0x000BC3D0;

    // [ԭ��] public: class PlayerInventory & __ptr64 __cdecl Player::getSupplies(void) __ptr64
    // [����] ?getSupplies@Player@@QEAAAEAVPlayerInventory@@XZ
    constexpr RVA MSSYM_B1QE11getSuppliesB1AA6PlayerB2AAE23QEAAAEAVPlayerInventoryB2AAA2XZ = 0x00724CC0;

    // [ԭ��] public: class ItemStack const & __ptr64 __cdecl PlayerInventory::getItem(int,enum ContainerID)const __ptr64
    // [����] ?getItem@PlayerInventory@@QEBAAEBVItemStack@@HW4ContainerID@@@Z
    constexpr RVA MSSYM_B1QA7getItemB1AE15PlayerInventoryB2AAE17QEBAAEBVItemStackB2AAE14HW4ContainerIDB3AAAA1Z = 0x00729490;

    // [ԭ��] public: int __cdecl PlayerInventory::getContainerSize(enum ContainerID)const __ptr64
    // [����] ?getContainerSize@PlayerInventory@@QEBAHW4ContainerID@@@Z
    constexpr RVA MSSYM_B1QE16getContainerSizeB1AE15PlayerInventoryB2AAE18QEBAHW4ContainerIDB3AAAA1Z = 0x007293C0;

    // [ԭ��] public: void __cdecl PlayerInventory::setItem(int,class ItemStack const & __ptr64,enum ContainerID,bool) __ptr64
    // [����] ?setItem@PlayerInventory@@QEAAXHAEBVItemStack@@W4ContainerID@@_N@Z
    constexpr RVA MSSYM_B1QA7setItemB1AE15PlayerInventoryB2AAE19QEAAXHAEBVItemStackB2AAE13W4ContainerIDB3AAUA1NB1AA1Z = 0x00729470;

    // [ԭ��] public: virtual void __cdecl ItemStackBase::setNull(void) __ptr64
    // [����] ?setNull@ItemStackBase@@UEAAXXZ
    constexpr RVA MSSYM_B1QA7setNullB1AE13ItemStackBaseB2AAA7UEAAXXZ = 0x007F7D10;

    // [ԭ��] public: virtual void __cdecl FillingContainer::clearSlot(int) __ptr64
    // [����] ?clearSlot@FillingContainer@@UEAAXH@Z
    constexpr RVA MSSYM_B1QA9clearSlotB1AE16FillingContainerB2AAA6UEAAXHB1AA1Z = 0x0077CBB0;

    // [ԭ��] public: struct PlayerInventory::SlotData __cdecl PlayerInventory::getSelectedSlot(void)const __ptr64
    // [����] ?getSelectedSlot@PlayerInventory@@QEBA?AUSlotData@1@XZ
    constexpr RVA MSSYM_B1QE15getSelectedSlotB1AE15PlayerInventoryB2AAA4QEBAB1QE10AUSlotDataB1AA11B1AA2XZ = 0x00729590;

    // [ԭ��] public: struct Brightness __cdecl BlockSource::getRawBrightness(class BlockPos const & __ptr64,bool,bool)const __ptr64
    // [����] ?getRawBrightness@BlockSource@@QEBA?AUBrightness@@AEBVBlockPos@@_N1@Z
    constexpr RVA MSSYM_B1QE16getRawBrightnessB1AE11BlockSourceB2AAA4QEBAB1QE12AUBrightnessB2AAE12AEBVBlockPosB3AAUA2N1B1AA1Z = 0x00A16DF0;

    // [ԭ��] public: class Material const & __ptr64 __cdecl BlockSource::getMaterial(int,int,int)const __ptr64
    // [����] ?getMaterial@BlockSource@@QEBAAEBVMaterial@@HHH@Z
    constexpr RVA MSSYM_B1QE11getMaterialB1AE11BlockSourceB2AAE16QEBAAEBVMaterialB2AAA3HHHB1AA1Z = 0x00A1D7C0;

    // [ԭ��] public: class LevelChunk * __ptr64 __cdecl BlockSource::getChunk(class ChunkPos const & __ptr64)const __ptr64
    // [����] ?getChunk@BlockSource@@QEBAPEAVLevelChunk@@AEBVChunkPos@@@Z
    constexpr RVA MSSYM_B1QA8getChunkB1AE11BlockSourceB2AAE18QEBAPEAVLevelChunkB2AAE12AEBVChunkPosB3AAAA1Z = 0x00A15AE0;

    // [ԭ��] public: class DwellerComponent * __ptr64 __cdecl Actor::tryGetComponent<class DwellerComponent>(void) __ptr64
    // [����] ??$tryGetComponent@VDwellerComponent@@@Actor@@QEAAPEAVDwellerComponent@@XZ
    constexpr RVA MSSYM_B3QQDE15tryGetComponentB1AE17VDwellerComponentB3AAAA5ActorB2AAE24QEAAPEAVDwellerComponentB2AAA2XZ = 0x00570200;

    // [ԭ��] public: class Actor * __ptr64 __cdecl Level::fetchEntity(struct ActorUniqueID,bool)const __ptr64
    // [����] ?fetchEntity@Level@@QEBAPEAVActor@@UActorUniqueID@@_N@Z
    constexpr RVA MSSYM_B1QE11fetchEntityB1AA5LevelB2AAE13QEBAPEAVActorB2AAE14UActorUniqueIDB3AAUA1NB1AA1Z = 0x00A78690;

    // [ԭ��] public: class BlockPos __cdecl DwellerComponent::getVillageCenter(class Actor const & __ptr64)const __ptr64
    // [����] ?getVillageCenter@DwellerComponent@@QEBA?AVBlockPos@@AEBVActor@@@Z
    constexpr RVA MSSYM_B1QE16getVillageCenterB1AE16DwellerComponentB2AAA4QEBAB1QE10AVBlockPosB2AAA9AEBVActorB3AAAA1Z = 0x001F7C50;

    // [ԭ��] public: struct Tick const & __ptr64 __cdecl Level::getCurrentTick(void)const __ptr64
    // [����] ?getCurrentTick@Level@@QEBAAEBUTick@@XZ
    constexpr RVA MSSYM_B1QE14getCurrentTickB1AA5LevelB2AAE12QEBAAEBUTickB2AAA2XZ = 0x00A7D840;

    // [ԭ��] public: class Block const & __ptr64 __cdecl BlockPalette::getBlock(unsigned int const & __ptr64)const __ptr64
    // [����] ?getBlock@BlockPalette@@QEBAAEBVBlock@@AEBI@Z
    constexpr RVA MSSYM_B1QA8getBlockB1AE12BlockPaletteB2AAE13QEBAAEBVBlockB2AAA4AEBIB1AA1Z = 0x00A128B0;

    // [ԭ��] public: class Player * __ptr64 __cdecl Dimension::fetchNearestPlayer(float,float,float,float,bool) __ptr64
    // [����] ?fetchNearestPlayer@Dimension@@QEAAPEAVPlayer@@MMMM_N@Z
    constexpr RVA MSSYM_B1QE18fetchNearestPlayerB1AA9DimensionB2AAE14QEAAPEAVPlayerB2AAA4MMMMB1UA1NB1AA1Z = 0x00A64070;

    // [ԭ��] public: virtual bool __cdecl BegGoal::canUse(void) __ptr64
    // [����] ?canUse@BegGoal@@UEAA_NXZ
    constexpr RVA MSSYM_B1QA6canUseB1AA7BegGoalB2AAA4UEAAB1UA3NXZ = 0x00CC0290;

    // [ԭ��] public: virtual void __cdecl Actor::die(class ActorDamageSource const & __ptr64) __ptr64
    // [����] ?die@Actor@@UEAAXAEBVActorDamageSource@@@Z
    constexpr RVA MSSYM_B1QA3dieB1AA5ActorB2AAE26UEAAXAEBVActorDamageSourceB3AAAA1Z = 0x005675D0;

    // [ԭ��] public: virtual void __cdecl Actor::kill(void) __ptr64
    // [����] ?kill@Actor@@UEAAXXZ
    constexpr RVA MSSYM_B1QA4killB1AA5ActorB2AAA7UEAAXXZ = 0x00567540;

    // [ԭ��] public: virtual void __cdecl BlockActor::tick(class BlockSource & __ptr64) __ptr64
    // [����] ?tick@BlockActor@@UEAAXAEAVBlockSource@@@Z

    // [ԭ��] private: void __cdecl PistonBlockActor::_checkInceptionAchievement(class BlockActor & __ptr64,class BlockSource & __ptr64,class BlockPos const & __ptr64) __ptr64
    // [����] ?_checkInceptionAchievement@PistonBlockActor@@AEAAXAEAVBlockActor@@AEAVBlockSource@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B2QUE25checkInceptionAchievementB1AE16PistonBlockActorB2AAE19AEAAXAEAVBlockActorB2AAE15AEAVBlockSourceB2AAE12AEBVBlockPosB3AAAA1Z = 0x008C39E0;

    // [ԭ��] public: static void __cdecl BlockTypeRegistry::forEachBlock(class std::function<bool __cdecl(class BlockLegacy const & __ptr64)>)
    // [����] ?forEachBlock@BlockTypeRegistry@@SAXV?$function@$$A6A_NAEBVBlockLegacy@@@Z@std@@@Z
    constexpr RVA MSSYM_B1QE12forEachBlockB1AE17BlockTypeRegistryB2AAA4SAXVB2QDA8functionB3ADDA3A6AB1UE16NAEBVBlockLegacyB3AAAA1ZB1AA3stdB3AAAA1Z = 0x0095DEF0;

}

// �ļ�����
