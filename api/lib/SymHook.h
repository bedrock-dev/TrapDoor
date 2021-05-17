// 该文件内容由PDB工具生成。
// 注意：
// 反修饰后的符号原型可能有误，仅供参考！
// 过长的符号将由其对应的md5值表示该符号对应的标识符。
#pragma once

namespace SymHook {
    using RVA = unsigned int;


    constexpr RVA MSSYM_B1QE11fetchEntityB1AA5LevelB2AAE13UEBAPEAVActorB2AAE14UActorUniqueIDB3AAUA1NB1AA1Z = 0x00D2BC60;

    // [原型] public: virtual void __cdecl MinecraftEventing::fireEventPlayerMessageChat(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
    // [符号] ?fireEventPlayerMessageChat@MinecraftEventing@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z
    constexpr RVA MSSYM_MD5_c5508c07a9bc049d2b327ac921a4b334 = 0x00557990;

    constexpr RVA MSSYM_MD5_52e7de092fab8d042fb516e31fc9756f = 0x00D3E270;

    // [原型] void __cdecl CommandUtils::displayLocalizableMessage(bool,class Player & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > const & __ptr64)
    // [符号] ?displayLocalizableMessage@CommandUtils@@YAX_NAEAVPlayer@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@@Z
    constexpr RVA MSSYM_MD5_24be62e9330073695808606844de0d99 = 0x00672820;

    // [原型] public: virtual void __cdecl ServerLevel::tick(void) __ptr64
    // [符号] ?tick@ServerLevel@@UEAAXXZ
    constexpr RVA MSSYM_B1QA4tickB1AE11ServerLevelB2AAA7UEAAXXZ = 0x0068BC40;

    // [原型] public: virtual int __cdecl ServerPlayer::tickWorld(struct Tick const & __ptr64) __ptr64
    // [符号] ?tickWorld@ServerPlayer@@UEAAHAEBUTick@@@Z
    constexpr RVA MSSYM_B1QA9tickWorldB1AE12ServerPlayerB2AAE13UEAAHAEBUTickB3AAAA1Z = 0x0068BE70;

    // [原型] public: virtual void __cdecl Dimension::tick(void) __ptr64
    // [符号] ?tick@Dimension@@UEAAXXZ
    constexpr RVA MSSYM_B1QA4tickB1AA9DimensionB2AAA7UEAAXXZ = 0x00DA21A0;

    // [原型] public: void __cdecl LevelChunk::tick(class BlockSource & __ptr64,struct Tick const & __ptr64) __ptr64
    // [符号] ?tick@LevelChunk@@QEAAXAEAVBlockSource@@AEBUTick@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB2AAA8AEBUTickB3AAAA1Z = 0x00D012E0;

    // [原型] public: void __cdecl LevelChunk::tickBlocks(class BlockSource & __ptr64) __ptr64
    // [符号] ?tickBlocks@LevelChunk@@QEAAXAEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QE10tickBlocksB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z = 0x00D02020;

    // [原型] public: void __cdecl LevelChunk::tickBlockEntities(class BlockSource & __ptr64) __ptr64
    // [符号] ?tickBlockEntities@LevelChunk@@QEAAXAEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QE17tickBlockEntitiesB1AE10LevelChunkB2AAE20QEAAXAEAVBlockSourceB3AAAA1Z = 0x00D01CD0;

    // [原型] public: bool __cdecl BlockTickingQueue::tickPendingTicks(class BlockSource & __ptr64,struct Tick const & __ptr64,int,bool) __ptr64
    // [符号] ?tickPendingTicks@BlockTickingQueue@@QEAA_NAEAVBlockSource@@AEBUTick@@H_N@Z
    constexpr RVA MSSYM_B1QE16tickPendingTicksB1AE17BlockTickingQueueB2AAA4QEAAB1UE16NAEAVBlockSourceB2AAA8AEBUTickB2AAA1HB1UA1NB1AA1Z = 0x00D3FF80;

    // [原型] public: virtual void __cdecl Dimension::tickRedstone(void) __ptr64
    // [符号] ?tickRedstone@Dimension@@UEAAXXZ
    constexpr RVA MSSYM_B1QE12tickRedstoneB1AA9DimensionB2AAA7UEAAXXZ = 0x00DA2500;

    // [原型] public: void __cdecl EntitySystems::tick(class EntityRegistry & __ptr64) __ptr64
    // [符号] ?tick@EntitySystems@@QEAAXAEAVEntityRegistry@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AE13EntitySystemsB2AAE23QEAAXAEAVEntityRegistryB3AAAA1Z = 0x006F7E40;

    // [原型] public: bool __cdecl Actor::tick(class BlockSource & __ptr64) __ptr64
    // [符号] ?tick@Actor@@QEAA_NAEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AA5ActorB2AAA4QEAAB1UE16NAEAVBlockSourceB3AAAA1Z = 0x00957BE0;

    // [原型] public: virtual void __cdecl Actor::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64) __ptr64
    // [符号] ?getDebugText@Actor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z
    constexpr RVA MSSYM_MD5_f04fad6bac034f1e861181d3580320f2 = 0x00938010;

    // [原型] public: virtual class Vec3 const & __ptr64 __cdecl Actor::getPos(void)const __ptr64
    // [符号] ?getPos@Actor@@UEBAAEBVVec3@@XZ
    constexpr RVA MSSYM_B1QA6getPosB1AA5ActorB2AAE12UEBAAEBVVec3B2AAA2XZ = 0x0093AAB0;

    // [原型] public: virtual bool __cdecl Player::attack(class Actor & __ptr64) __ptr64
    // [符号] ?attack@Player@@UEAA_NAEAVActor@@@Z
    constexpr RVA MSSYM_B1QA6attackB1AA6PlayerB2AAA4UEAAB1UE10NAEAVActorB3AAAA1Z = 0x00981240;

    // [原型] public: void __cdecl Explosion::explode(void) __ptr64
    // [符号] ?explode@Explosion@@QEAAXXZ
    constexpr RVA MSSYM_B1QA7explodeB1AA9ExplosionB2AAA7QEAAXXZ = 0x00D27E50;

    // [原型] public: virtual void __cdecl Actor::setNameTag(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
    // [符号] ?setNameTag@Actor@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
    constexpr RVA MSSYM_B1QE10setNameTagB1AA5ActorB2AAA9UEAAXAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AAAA1Z = 0x00952990;

    // [原型] public: class Vec3 __cdecl Actor::getViewVector(float)const __ptr64
    // [符号] ?getViewVector@Actor@@QEBA?AVVec3@@M@Z
    constexpr RVA MSSYM_B1QE13getViewVectorB1AA5ActorB2AAA4QEBAB1QA6AVVec3B2AAA1MB1AA1Z = 0x0093B980;

    // [原型] public: virtual class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64 __cdecl Actor::getNameTag(void)const __ptr64
    // [符号] ?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
    constexpr RVA MSSYM_B1QE10getNameTagB1AA5ActorB2AAA8UEBAAEBVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x0093A780;

    // [原型] public: virtual void __cdecl ServerPlayer::setPlayerGameType(enum GameType) __ptr64
    // [符号] ?setPlayerGameType@ServerPlayer@@UEAAXW4GameType@@@Z
    constexpr RVA MSSYM_B1QE17setPlayerGameTypeB1AE12ServerPlayerB2AAE15UEAAXW4GameTypeB3AAAA1Z = 0x00689460;

    // [原型] public: class Block const & __ptr64 __cdecl BlockSource::getBlock(class BlockPos const & __ptr64)const __ptr64
    // [符号] ?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QA8getBlockB1AE11BlockSourceB2AAE13QEBAAEBVBlockB2AAE12AEBVBlockPosB3AAAA1Z = 0x00D2E470;

    // [原型] public: bool __cdecl BlockSource::setBlock(int,int,int,class Block const & __ptr64,int) __ptr64
    // [符号] ?setBlock@BlockSource@@QEAA_NHHHAEBVBlock@@H@Z
    constexpr RVA MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NHHHAEBVBlockB2AAA1HB1AA1Z = 0x00D3CE70;

    // [原型] public: bool __cdecl BlockSource::setBlock(class BlockPos const & __ptr64,class Block const & __ptr64,int,struct ActorBlockSyncMessage const * __ptr64) __ptr64
    // [符号] ?setBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@HPEBUActorBlockSyncMessage@@@Z
    constexpr RVA MSSYM_B1QA8setBlockB1AE11BlockSourceB2AAA4QEAAB1UE13NAEBVBlockPosB2AAA9AEBVBlockB2AAE26HPEBUActorBlockSyncMessageB3AAAA1Z = 0x00D3CAF0;

    // [原型] public: void __cdecl BlockSource::updateNeighborsAt(class BlockPos const & __ptr64) __ptr64
    // [符号] ?updateNeighborsAt@BlockSource@@QEAAXAEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z = 0x00D41410;

    // [原型] public: virtual enum EventResult __cdecl VanillaServerGameplayEventListener::onBlockPlacedByPlayer(class Player & __ptr64,class Block const & __ptr64,class BlockPos const & __ptr64,bool) __ptr64
    // [符号] ?onBlockPlacedByPlayer@VanillaServerGameplayEventListener@@UEAA?AW4EventResult@@AEAVPlayer@@AEBVBlock@@AEBVBlockPos@@_N@Z
    constexpr RVA MSSYM_B1QE21onBlockPlacedByPlayerB1AE34VanillaServerGameplayEventListenerB2AAA4UEAAB1QE14AW4EventResultB2AAE10AEAVPlayerB2AAA9AEBVBlockB2AAE12AEBVBlockPosB3AAUA1NB1AA1Z = 0x002DEBD0;

    // [原型] public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Block::toDebugString(void)const __ptr64
    // [符号] ?toDebugString@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
    constexpr RVA MSSYM_B1QE13toDebugStringB1AA5BlockB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x00E51FD0;

    // [原型] public: virtual class AABB const & __ptr64 __cdecl BlockLegacy::getOutline(class BlockSource & __ptr64,class BlockPos const & __ptr64,class AABB & __ptr64)const __ptr64
    // [符号] ?getOutline@BlockLegacy@@UEBAAEBVAABB@@AEAVBlockSource@@AEBVBlockPos@@AEAV2@@Z
    constexpr RVA MSSYM_B1QE10getOutlineB1AE11BlockLegacyB2AAE12UEBAAEBVAABBB2AAE15AEAVBlockSourceB2AAE12AEBVBlockPosB2AAA5AEAV2B2AAA1Z = 0x00E492F0;

    // [原型] public: void __cdecl BlockLegacy::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64,class BlockPos const & __ptr64)const __ptr64
    // [符号] ?getDebugText@BlockLegacy@@QEBAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_MD5_794b421b4bf67101f7418cd0d78bad83 = 0x00E47830;

    // [原型] public: virtual void __cdecl BlockActor::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64,class BlockPos const & __ptr64) __ptr64
    // [符号] ?getDebugText@BlockActor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_MD5_b5a16de43d7486d6e9b23cfb126773a7 = 0x00EA4DF0;

    // [原型] public: class Block const * __ptr64 __cdecl BlockLegacy::tryGetStateFromLegacyData(unsigned short)const __ptr64
    // [符号] ?tryGetStateFromLegacyData@BlockLegacy@@QEBAPEBVBlock@@G@Z
    constexpr RVA MSSYM_B1QE25tryGetStateFromLegacyDataB1AE11BlockLegacyB2AAE13QEBAPEBVBlockB2AAA1GB1AA1Z = 0x00E53020;

    // [原型] public: class Biome & __ptr64 __cdecl BlockSource::getBiome(class BlockPos const & __ptr64) __ptr64
    // [符号] ?getBiome@BlockSource@@QEAAAEAVBiome@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QA8getBiomeB1AE11BlockSourceB2AAE13QEAAAEAVBiomeB2AAE12AEBVBlockPosB3AAAA1Z = 0x00D2E380;

    // [原型] public: void __cdecl Village::tick(struct Tick,class BlockSource & __ptr64) __ptr64
    // [符号] ?tick@Village@@QEAAXUTick@@AEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QA4tickB1AA7VillageB2AAE10QEAAXUTickB2AAE15AEAVBlockSourceB3AAAA1Z = 0x00B35440;

    // [原型] public: float __cdecl Village::getApproximateRadius(void)const __ptr64
    // [符号] ?getApproximateRadius@Village@@QEBAMXZ
    constexpr RVA MSSYM_B1QE20getApproximateRadiusB1AA7VillageB2AAA7QEBAMXZ = 0x00B2E740;

    // [原型] public: unsigned __int64 __cdecl Village::getBedPOICount(void)const __ptr64
    // [符号] ?getBedPOICount@Village@@QEBA_KXZ
    constexpr RVA MSSYM_B1QE14getBedPOICountB1AA7VillageB2AAA4QEBAB1UA3KXZ = 0x00B2E8B0;

    // [原型] public: virtual class MobSpawnerData const * __ptr64 __cdecl BlockLegacy::getMobToSpawn(class SpawnConditions const & __ptr64,class BlockSource & __ptr64)const __ptr64
    // [符号] ?getMobToSpawn@BlockLegacy@@UEBAPEBVMobSpawnerData@@AEBVSpawnConditions@@AEAVBlockSource@@@Z
    constexpr RVA MSSYM_B1QE13getMobToSpawnB1AE11BlockLegacyB2AAE22UEBAPEBVMobSpawnerDataB2AAE19AEBVSpawnConditionsB2AAE15AEAVBlockSourceB3AAAA1Z = 0x00E485E0;

    // [原型] private: void __cdecl Spawner::_spawnStructureMob(class BlockSource & __ptr64,class BlockPos const & __ptr64,struct LevelChunk::HardcodedSpawningArea const & __ptr64,class SpawnConditions const & __ptr64) __ptr64
    // [符号] ?_spawnStructureMob@Spawner@@AEAAXAEAVBlockSource@@AEBVBlockPos@@AEBUHardcodedSpawningArea@LevelChunk@@AEBVSpawnConditions@@@Z
    constexpr RVA MSSYM_B2QUE17spawnStructureMobB1AA7SpawnerB2AAE20AEAAXAEAVBlockSourceB2AAE12AEBVBlockPosB2AAE25AEBUHardcodedSpawningAreaB1AE10LevelChunkB2AAE19AEBVSpawnConditionsB3AAAA1Z = 0x00EC3B40;

    // [原型] public: static bool __cdecl Spawner::findNextSpawnBlockUnder(class BlockSource const & __ptr64,class BlockPos & __ptr64,enum MaterialType,enum SpawnBlockRequirements)
    // [符号] ?findNextSpawnBlockUnder@Spawner@@SA_NAEBVBlockSource@@AEAVBlockPos@@W4MaterialType@@W4SpawnBlockRequirements@@@Z
    constexpr RVA MSSYM_B1QE23findNextSpawnBlockUnderB1AA7SpawnerB2AAA2SAB1UE16NAEBVBlockSourceB2AAE12AEAVBlockPosB2AAE14W4MaterialTypeB2AAE24W4SpawnBlockRequirementsB3AAAA1Z = 0x00EC5B40;

    // [原型] public: virtual void __cdecl HopperBlockActor::setItem(int,class ItemStack const & __ptr64) __ptr64
    // [符号] ?setItem@HopperBlockActor@@UEAAXHAEBVItemStack@@@Z
    constexpr RVA MSSYM_B1QA7setItemB1AE16HopperBlockActorB2AAE19UEAAXHAEBVItemStackB3AAAA1Z = 0x00E94310;

    // [原型] public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl ItemStackBase::getName(void)const __ptr64
    // [符号] ?getName@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ
    constexpr RVA MSSYM_B1QA7getNameB1AE13ItemStackBaseB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ = 0x00A126A0;

    // [原型] public: bool __cdecl Item::useOn(class ItemStack & __ptr64,class Actor & __ptr64,int,int,int,unsigned char,float,float,float)const __ptr64
    // [符号] ?useOn@Item@@QEBA_NAEAVItemStack@@AEAVActor@@HHHEMMM@Z
    constexpr RVA MSSYM_B1QA5useOnB1AA4ItemB2AAA4QEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA7HHHEMMMB1AA1Z = 0x00BE6E70;

    // [原型] public: class BaseCircuitComponent * __ptr64 __cdecl CircuitSceneGraph::getBaseComponent(class BlockPos const & __ptr64) __ptr64
    // [符号] ?getBaseComponent@CircuitSceneGraph@@QEAAPEAVBaseCircuitComponent@@AEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QE16getBaseComponentB1AE17CircuitSceneGraphB2AAE28QEAAPEAVBaseCircuitComponentB2AAE12AEBVBlockPosB3AAAA1Z = 0x00E0AFA0;

    // [原型] public: enum VanillaBiomeTypes __cdecl Biome::getBiomeType(void)const __ptr64
    // [符号] ?getBiomeType@Biome@@QEBA?AW4VanillaBiomeTypes@@XZ
    constexpr RVA MSSYM_B1QE12getBiomeTypeB1AA5BiomeB2AAA4QEBAB1QE20AW4VanillaBiomeTypesB2AAA2XZ = 0x00EC5F00;

    // [原型] public: virtual class Dimension * __ptr64 __cdecl Level::getDimension(class AutomaticID<class Dimension,int>)const __ptr64
    // [符号] ?getDimension@Level@@UEBAPEAVDimension@@V?$AutomaticID@VDimension@@H@@@Z
    constexpr RVA MSSYM_B1QE12getDimensionB1AA5LevelB2AAE17UEBAPEAVDimensionB2AAA1VB2QDE11AutomaticIDB1AE10VDimensionB2AAA1HB3AAAA1Z = 0x00D2EE30;

    // [原型] public: unsigned __int64 __cdecl NetworkIdentifier::getHash(void)const __ptr64
    // [符号] ?getHash@NetworkIdentifier@@QEBA_KXZ
    constexpr RVA MSSYM_B1QA7getHashB1AE17NetworkIdentifierB2AAA4QEBAB1UA3KXZ = 0x005B5E70;

    // [原型] public: virtual void __cdecl ServerNetworkHandler::handle(class NetworkIdentifier const & __ptr64,class CommandRequestPacket const & __ptr64) __ptr64
    // [符号] ?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVCommandRequestPacket@@@Z
    constexpr RVA MSSYM_B1QA6handleB1AE20ServerNetworkHandlerB2AAE26UEAAXAEBVNetworkIdentifierB2AAE24AEBVCommandRequestPacketB3AAAA1Z = 0x005E3F00;

    // [原型] public: void __cdecl CommandRegistry::registerCommand(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,char const * __ptr64,enum CommandPermissionLevel,struct CommandFlag,struct CommandFlag) __ptr64
    // [符号] ?registerCommand@CommandRegistry@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEBDW4CommandPermissionLevel@@UCommandFlag@@3@Z
    constexpr RVA MSSYM_MD5_8574de98358ff66b5a913417f44dd706 = 0x00683A90;

    // [原型] public: virtual enum CommandPermissionLevel __cdecl Player::getCommandPermissionLevel(void)const __ptr64
    // [符号] ?getCommandPermissionLevel@Player@@UEBA?AW4CommandPermissionLevel@@XZ
    constexpr RVA MSSYM_B1QE25getCommandPermissionLevelB1AA6PlayerB2AAA4UEBAB1QE25AW4CommandPermissionLevelB2AAA2XZ = 0x009872F0;

    // [原型] public: class PlayerInventory & __ptr64 __cdecl Player::getSupplies(void) __ptr64
    // [符号] ?getSupplies@Player@@QEAAAEAVPlayerInventory@@XZ
    constexpr RVA MSSYM_B1QE11getSuppliesB1AA6PlayerB2AAE23QEAAAEAVPlayerInventoryB2AAA2XZ = 0x00988F80;

    // [原型] public: virtual void __cdecl ItemStackBase::setNull(void) __ptr64
    // [符号] ?setNull@ItemStackBase@@UEAAXXZ
    constexpr RVA MSSYM_B1QA7setNullB1AE13ItemStackBaseB2AAA7UEAAXXZ = 0x00A1A510;

    // [原型] public: struct Brightness __cdecl BlockSource::getRawBrightness(class BlockPos const & __ptr64,bool,bool)const __ptr64
    // [符号] ?getRawBrightness@BlockSource@@QEBA?AUBrightness@@AEBVBlockPos@@_N1@Z
    constexpr RVA MSSYM_B1QE16getRawBrightnessB1AE11BlockSourceB2AAA4QEBAB1QE12AUBrightnessB2AAE12AEBVBlockPosB3AAUA2N1B1AA1Z = 0x00D30F40;

    // [原型] public: class Material const & __ptr64 __cdecl BlockSource::getMaterial(int,int,int)const __ptr64
    // [符号] ?getMaterial@BlockSource@@QEBAAEBVMaterial@@HHH@Z
    constexpr RVA MSSYM_B1QE11getMaterialB1AE11BlockSourceB2AAE16QEBAAEBVMaterialB2AAA3HHHB1AA1Z = 0x00D30070;

    // [原型] public: class DwellerComponent * __ptr64 __cdecl Actor::tryGetComponent<class DwellerComponent>(void) __ptr64
    // [符号] ??$tryGetComponent@VDwellerComponent@@@Actor@@QEAAPEAVDwellerComponent@@XZ
    constexpr RVA MSSYM_B3QQDE15tryGetComponentB1AE17VDwellerComponentB3AAAA5ActorB2AAE24QEAAPEAVDwellerComponentB2AAA2XZ = 0x002F22B0;

    // [原型] public: class BlockPos __cdecl DwellerComponent::getVillageCenter(class Actor const & __ptr64)const __ptr64
    // [符号] ?getVillageCenter@DwellerComponent@@QEBA?AVBlockPos@@AEBVActor@@@Z
    constexpr RVA MSSYM_B1QE16getVillageCenterB1AE16DwellerComponentB2AAA4QEBAB1QE10AVBlockPosB2AAA9AEBVActorB3AAAA1Z = 0x00759A50;

    // [原型] public: static void __cdecl BlockTypeRegistry::forEachBlock(class std::function<bool __cdecl(class BlockLegacy const & __ptr64)>)
    // [符号] ?forEachBlock@BlockTypeRegistry@@SAXV?$function@$$A6A_NAEBVBlockLegacy@@@Z@std@@@Z
    constexpr RVA MSSYM_B1QE12forEachBlockB1AE17BlockTypeRegistryB2AAA4SAXVB2QDA8functionB3ADDA3A6AB1UE16NAEBVBlockLegacyB3AAAA1ZB1AA3stdB3AAAA1Z = 0x00CDF790;

    // [原型] private: void __cdecl CircuitSceneGraph::removeComponent(class BlockPos const & __ptr64) __ptr64
    // [符号] ?removeComponent@CircuitSceneGraph@@AEAAXAEBVBlockPos@@@Z
    constexpr RVA MSSYM_B1QE15removeComponentB1AE17CircuitSceneGraphB2AAE17AEAAXAEBVBlockPosB3AAAA1Z = 0x00E0D530;

    // [原型] private: void __cdecl CircuitSceneGraph::processPendingAdds(void) __ptr64
    // [符号] ?processPendingAdds@CircuitSceneGraph@@AEAAXXZ
    constexpr RVA MSSYM_B1QE18processPendingAddsB1AE17CircuitSceneGraphB2AAA7AEAAXXZ = 0x00E0C640;

    // [原型] public: __cdecl SPSCQueue<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,512>::SPSCQueue<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,512>(unsigned __int64) __ptr64
    // [符号] ??0?$SPSCQueue@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@$0CAA@@@QEAA@_K@Z
    constexpr RVA MSSYM_B2QQA10B2QDA9SPSCQueueB1AA1VB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB3AADA40CAAB3AAAA4QEAAB2AUA1KB1AA1Z = 0x002740F0;

    // [原型] private: bool __cdecl SPSCQueue<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,512>::inner_enqueue<0,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64>(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
    // [符号] ??$inner_enqueue@$0A@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@?$SPSCQueue@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@$0CAA@@@AEAA_NAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z
    constexpr RVA MSSYM_MD5_b5c9e566146b3136e6fb37f0c080d91e = 0x00273CC0;

}

// 文件结束
