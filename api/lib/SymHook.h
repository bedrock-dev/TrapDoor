#pragma  once
namespace SymHook{
   //[1]??$tryGetComponent@VUserEntityIdentifierComponent@@@Actor@@QEAAPEAVUserEntityIdentifierComponent@@XZ;
   //public: class UserEntityIdentifierComponent * __ptr64 __cdecl Actor::tryGetComponent<class UserEntityIdentifierComponent>(void) __ptr64
    constexpr uint64_t  Actor_tryGetComponent_UserEntityIdentifierComponent_4bafed89 = 0x00D47B10;

   //[2]?_canOpenThis@ChestBlockActor@@MEBA_NAEAVBlockSource@@@Z;
   //protected: virtual bool __cdecl ChestBlockActor::_canOpenThis(class BlockSource & __ptr64)const __ptr64
    constexpr uint64_t  ChestBlockActor_canOpenThis_309ed47c = 0x01B29460;

   //[3]?_spawnStructureMob@Spawner@@AEAAXAEAVBlockSource@@AEBVBlockPos@@AEBUHardcodedSpawningArea@LevelChunk@@AEBVSpawnConditions@@@Z;
   //private: void __cdecl Spawner::_spawnStructureMob(class BlockSource & __ptr64,class BlockPos const & __ptr64,struct LevelChunk::HardcodedSpawningArea const & __ptr64,class SpawnConditions const & __ptr64) __ptr64
    constexpr uint64_t  Spawner_spawnStructureMob_98a1693e = 0x01B223A0;

   //[4]?displayLocalizableMessage@CommandUtils@@YAX_NAEAVPlayer@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@@Z;
   //void __cdecl CommandUtils::displayLocalizableMessage(bool,class Player & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > const & __ptr64)
    constexpr uint64_t  CommandUtils_displayLocalizableMessage_24be62e9 = 0x01396640;

   //[5]?explode@Explosion@@QEAAXXZ;
   //public: void __cdecl Explosion::explode(void) __ptr64
    constexpr uint64_t  Explosion_explode_5adcea90 = 0x01C9A920;

   //[6]?fetchEntity@Level@@UEBAPEAVActor@@UActorUniqueID@@_N@Z;
   //public: virtual class Actor * __ptr64 __cdecl Level::fetchEntity(struct ActorUniqueID,bool)const __ptr64
    constexpr uint64_t  Level_fetchEntity_ff3466ce = 0x018C8AE0;

   //[7]?findNextSpawnBlockUnder@Spawner@@SA_NAEBVBlockSource@@AEAVBlockPos@@W4MaterialType@@W4SpawnBlockRequirements@@@Z;
   //public: static bool __cdecl Spawner::findNextSpawnBlockUnder(class BlockSource const & __ptr64,class BlockPos & __ptr64,enum MaterialType,enum SpawnBlockRequirements)
    constexpr uint64_t  Spawner_findNextSpawnBlockUnder_65b36c80 = 0x01B22F40;

   //[8]?forEachBlock@BlockTypeRegistry@@SAXV?$function@$$A6A_NAEBVBlockLegacy@@@Z@std@@@Z;
   //public: static void __cdecl BlockTypeRegistry::forEachBlock(class std::function<bool __cdecl(class BlockLegacy const & __ptr64)>)
    constexpr uint64_t  BlockTypeRegistry_forEachBlock_7f891f2d = 0x0192CF90;

   //[9]?forEachPlayer@Level@@UEAAXV?$function@$$A6A_NAEAVPlayer@@@Z@std@@@Z;
   //public: virtual void __cdecl Level::forEachPlayer(class std::function<bool __cdecl(class Player & __ptr64)>) __ptr64
    constexpr uint64_t  Level_forEachPlayer_71a4f564 = 0x018C8F30;

   //[10]?getApproximateRadius@Village@@QEBAMXZ;
   //public: float __cdecl Village::getApproximateRadius(void)const __ptr64
    constexpr uint64_t  Village_getApproximateRadius_626d2648 = 0x015304E0;

   //[11]?getBaseComponent@CircuitSceneGraph@@QEAAPEAVBaseCircuitComponent@@AEBVBlockPos@@@Z;
   //public: class BaseCircuitComponent * __ptr64 __cdecl CircuitSceneGraph::getBaseComponent(class BlockPos const & __ptr64) __ptr64
    constexpr uint64_t  CircuitSceneGraph_getBaseComponent_c4a5dbac = 0x01CC0B40;

   //[12]?getBedPOICount@Village@@QEBA_KXZ;
   //public: unsigned __int64 __cdecl Village::getBedPOICount(void)const __ptr64
    constexpr uint64_t  Village_getBedPOICount_016a7e2f = 0x015305C0;

   //[13]?getBiome@BlockSource@@QEAAAEAVBiome@@AEBVBlockPos@@@Z;
   //public: class Biome & __ptr64 __cdecl BlockSource::getBiome(class BlockPos const & __ptr64) __ptr64
    constexpr uint64_t  BlockSource_getBiome_967864de = 0x01A28AB0;

   //[14]?getBiomeType@Biome@@QEBA?AW4VanillaBiomeTypes@@XZ;
   //public: enum VanillaBiomeTypes __cdecl Biome::getBiomeType(void)const __ptr64
    constexpr uint64_t  Biome_getBiomeType_bb099b78 = 0x01A33510;

   //[15]?getBlock@BlockActor@@QEBAPEBVBlock@@XZ;
   //public: class Block const * __ptr64 __cdecl BlockActor::getBlock(void)const __ptr64
    constexpr uint64_t  BlockActor_getBlock_64387bdc = 0x00E07660;

   //[16]?getBlock@BlockSource@@UEBAAEBVBlock@@AEBVBlockPos@@@Z;
   //public: virtual class Block const & __ptr64 __cdecl BlockSource::getBlock(class BlockPos const & __ptr64)const __ptr64
    constexpr uint64_t  BlockSource_getBlock_b39e5e5d = 0x01A28B00;

   //[17]?getBlock@BlockSource@@UEBAAEBVBlock@@HHH@Z;
   //public: virtual class Block const & __ptr64 __cdecl BlockSource::getBlock(int,int,int)const __ptr64
    constexpr uint64_t  BlockSource_getBlock_6df88a51 = 0x01A28BD0;

   //[18]?getCommandPermissionLevel@Player@@UEBA?AW4CommandPermissionLevel@@XZ;
   //public: virtual enum CommandPermissionLevel __cdecl Player::getCommandPermissionLevel(void)const __ptr64
    constexpr uint64_t  Player_getCommandPermissionLevel_40b0e608 = 0x01465520;

   //[19]?getDebugText@Actor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z;
   //public: virtual void __cdecl Actor::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64) __ptr64
    constexpr uint64_t  Actor_getDebugText_f04fad6b = 0x0142DA60;

   //[20]?getDimension@Level@@UEBAPEAVDimension@@V?$AutomaticID@VDimension@@H@@@Z;
   //public: virtual class Dimension * __ptr64 __cdecl Level::getDimension(class AutomaticID<class Dimension,int>)const __ptr64
    constexpr uint64_t  Level_getDimension_6fab9459 = 0x018C9570;

   //[21]?getHash@NetworkIdentifier@@QEBA_KXZ;
   //public: unsigned __int64 __cdecl NetworkIdentifier::getHash(void)const __ptr64
    constexpr uint64_t  NetworkIdentifier_getHash_d932dec8 = 0x00E083E0;

   //[22]?getMobToSpawn@BlockLegacy@@UEBAPEBVMobSpawnerData@@AEBVSpawnConditions@@AEAVBlockSource@@@Z;
   //public: virtual class MobSpawnerData const * __ptr64 __cdecl BlockLegacy::getMobToSpawn(class SpawnConditions const & __ptr64,class BlockSource & __ptr64)const __ptr64
    constexpr uint64_t  BlockLegacy_getMobToSpawn_dd8ce374 = 0x01916A70;

   //[23]?getName@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ;
   //public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl ItemStackBase::getName(void)const __ptr64
    constexpr uint64_t  ItemStackBase_getName_6d581a35 = 0x01A97760;

   //[24]?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ;
   //public: virtual class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64 __cdecl Actor::getNameTag(void)const __ptr64
    constexpr uint64_t  Actor_getNameTag_7044ab83 = 0x014308F0;

   //[25]?getPosition@Actor@@UEBAAEBVVec3@@XZ;
   //public: virtual class Vec3 const & __ptr64 __cdecl Actor::getPosition(void)const __ptr64
    constexpr uint64_t  Actor_getPosition_8f5a9c5f = 0x01430F50;

   //[26]?getPosition@LevelChunk@@QEBAAEBVChunkPos@@XZ;
   //public: class ChunkPos const & __ptr64 __cdecl LevelChunk::getPosition(void)const __ptr64
    constexpr uint64_t  LevelChunk_getPosition_5b2499b2 = 0x0159FA40;

   //[27]?getRegion@Actor@@QEBAAEAVBlockSource@@XZ;
   //public: class BlockSource & __ptr64 __cdecl Actor::getRegion(void)const __ptr64
    constexpr uint64_t  Actor_getRegion_757c8f63 = 0x01431060;

   //[28]?getViewVector@Actor@@QEBA?AVVec3@@M@Z;
   //public: class Vec3 __cdecl Actor::getViewVector(float)const __ptr64
    constexpr uint64_t  Actor_getViewVector_01c92121 = 0x01431A60;

   //[29]?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVCommandRequestPacket@@@Z;
   //public: virtual void __cdecl ServerNetworkHandler::handle(class NetworkIdentifier const & __ptr64,class CommandRequestPacket const & __ptr64) __ptr64
    constexpr uint64_t  ServerNetworkHandler_handle_1a4c2996 = 0x00DC3E80;

   //[30]?processPendingAdds@CircuitSceneGraph@@AEAAXXZ;
   //private: void __cdecl CircuitSceneGraph::processPendingAdds(void) __ptr64
    constexpr uint64_t  CircuitSceneGraph_processPendingAdds_9d2954e5 = 0x01CC11E0;

   //[31]?registerCommand@CommandRegistry@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEBDW4CommandPermissionLevel@@UCommandFlag@@3@Z;
   //public: void __cdecl CommandRegistry::registerCommand(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,char const * __ptr64,enum CommandPermissionLevel,struct CommandFlag,struct CommandFlag) __ptr64
    constexpr uint64_t  CommandRegistry_registerCommand_8574de98 = 0x013908F0;

   //[32]?removeComponent@CircuitSceneGraph@@AEAAXAEBVBlockPos@@@Z;
   //private: void __cdecl CircuitSceneGraph::removeComponent(class BlockPos const & __ptr64) __ptr64
    constexpr uint64_t  CircuitSceneGraph_removeComponent_1f06081d = 0x01CC1B10;

   //[33]?removeItem@Container@@UEAAXHH@Z;
   //public: virtual void __cdecl Container::removeItem(int,int) __ptr64
    constexpr uint64_t  Container_removeItem_99dc40a0 = 0x015020E0;

   //[34]?setBlock@BlockSource@@QEAA_NHHHAEBVBlock@@HPEAVActor@@@Z;
   //public: bool __cdecl BlockSource::setBlock(int,int,int,class Block const & __ptr64,int,class Actor * __ptr64) __ptr64
    constexpr uint64_t  BlockSource_setBlock_30b3a288 = 0x01A2C560;

   //[35]?setItem@HopperBlockActor@@UEAAXHAEBVItemStack@@@Z;
   //public: virtual void __cdecl HopperBlockActor::setItem(int,class ItemStack const & __ptr64) __ptr64
    constexpr uint64_t  HopperBlockActor_setItem_c0e5f3ce = 0x01C5E8C0;

   //[36]?setNameTag@Actor@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z;
   //public: virtual void __cdecl Actor::setNameTag(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
    constexpr uint64_t  Actor_setNameTag_2f9772d3 = 0x01443DA0;

   //[37]?setPlayerGameType@ServerPlayer@@UEAAXW4GameType@@@Z;
   //public: virtual void __cdecl ServerPlayer::setPlayerGameType(enum GameType) __ptr64
    constexpr uint64_t  ServerPlayer_setPlayerGameType_058d8c73 = 0x01453670;

   //[38]?spawnParticleEffect@Level@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVVec3@@PEAVDimension@@@Z;
   //public: virtual void __cdecl Level::spawnParticleEffect(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class Vec3 const & __ptr64,class Dimension * __ptr64) __ptr64
    constexpr uint64_t  Level_spawnParticleEffect_52e7de09 = 0x018D2940;

   //[39]?tick@Actor@@QEAA_NAEAVBlockSource@@@Z;
   //public: bool __cdecl Actor::tick(class BlockSource & __ptr64) __ptr64
    constexpr uint64_t  Actor_tick_8589defc = 0x01448570;

   //[40]?tick@Dimension@@UEAAXXZ;
   //public: virtual void __cdecl Dimension::tick(void) __ptr64
    constexpr uint64_t  Dimension_tick_39d89862 = 0x018E2140;

   //[41]?tick@LevelChunk@@QEAAXAEAVBlockSource@@AEBUTick@@@Z;
   //public: void __cdecl LevelChunk::tick(class BlockSource & __ptr64,struct Tick const & __ptr64) __ptr64
    constexpr uint64_t  LevelChunk_tick_9d729ccd = 0x01B09270;

   //[42]?tick@ServerLevel@@UEAAXXZ;
   //public: virtual void __cdecl ServerLevel::tick(void) __ptr64
    constexpr uint64_t  ServerLevel_tick_86efb826 = 0x015566D0;

   //[43]?tick@Village@@QEAAXUTick@@AEAVBlockSource@@@Z;
   //public: void __cdecl Village::tick(struct Tick,class BlockSource & __ptr64) __ptr64
    constexpr uint64_t  Village_tick_2a1ecbf8 = 0x01531ED0;

   //[44]?tickBlockEntities@LevelChunk@@QEAAXAEAVBlockSource@@@Z;
   //public: void __cdecl LevelChunk::tickBlockEntities(class BlockSource & __ptr64) __ptr64
    constexpr uint64_t  LevelChunk_tickBlockEntities_41f9b2ca = 0x01B09C40;

   //[45]?tickBlocks@LevelChunk@@QEAAXAEAVBlockSource@@@Z;
   //public: void __cdecl LevelChunk::tickBlocks(class BlockSource & __ptr64) __ptr64
    constexpr uint64_t  LevelChunk_tickBlocks_66280c26 = 0x01B09F90;

   //[46]?tickEntitySystems@Level@@UEAAXXZ;
   //public: virtual void __cdecl Level::tickEntitySystems(void) __ptr64
    constexpr uint64_t  Level_tickEntitySystems_251e10ba = 0x018D40F0;

   //[47]?tickPendingTicks@BlockTickingQueue@@QEAA_NAEAVBlockSource@@AEBUTick@@H_N@Z;
   //public: bool __cdecl BlockTickingQueue::tickPendingTicks(class BlockSource & __ptr64,struct Tick const & __ptr64,int,bool) __ptr64
    constexpr uint64_t  BlockTickingQueue_tickPendingTicks_e4625213 = 0x01B6CFD0;

   //[48]?tickRedstone@Dimension@@UEAAXXZ;
   //public: virtual void __cdecl Dimension::tickRedstone(void) __ptr64
    constexpr uint64_t  Dimension_tickRedstone_c8a7e6e5 = 0x018E2500;

   //[49]?tickWorld@ServerPlayer@@UEAAXAEBUTick@@@Z;
   //public: virtual void __cdecl ServerPlayer::tickWorld(struct Tick const & __ptr64) __ptr64
    constexpr uint64_t  ServerPlayer_tickWorld_4b6718a8 = 0x01453A90;

   //[50]?toDebugString@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ;
   //public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Block::toDebugString(void)const __ptr64
    constexpr uint64_t  Block_toDebugString_522cb860 = 0x01A1FCB0;

   //[51]?tryGetStateFromLegacyData@BlockLegacy@@QEBAPEBVBlock@@G@Z;
   //public: class Block const * __ptr64 __cdecl BlockLegacy::tryGetStateFromLegacyData(unsigned short)const __ptr64
    constexpr uint64_t  BlockLegacy_tryGetStateFromLegacyData_ad225111 = 0x01918F20;

   //[52]?updateNeighborsAt@BlockSource@@QEAAXAEBVBlockPos@@@Z;
   //public: void __cdecl BlockSource::updateNeighborsAt(class BlockPos const & __ptr64) __ptr64
    constexpr uint64_t  BlockSource_updateNeighborsAt_4c3f8cf7 = 0x01A2CE30;

   //[53]?useOn@Item@@QEBA_NAEAVItemStack@@AEAVActor@@HHHEAEBVVec3@@@Z;
   //public: bool __cdecl Item::useOn(class ItemStack & __ptr64,class Actor & __ptr64,int,int,int,unsigned char,class Vec3 const & __ptr64)const __ptr64
    constexpr uint64_t  Item_useOn_51392594 = 0x01AA4970;

}
