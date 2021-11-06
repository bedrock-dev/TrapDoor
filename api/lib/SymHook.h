#pragma  once
namespace SymHook{
   //[1]?_spawnStructureMob@Spawner@@AEAAXAEAVBlockSource@@AEBVBlockPos@@AEBUHardcodedSpawningArea@LevelChunk@@AEBVSpawnConditions@@@Z;
   //private: void __cdecl Spawner::_spawnStructureMob(class BlockSource & __ptr64,class BlockPos const & __ptr64,struct LevelChunk::HardcodedSpawningArea const & __ptr64,class SpawnConditions const & __ptr64) __ptr64
    constexpr uint64_t  Spawner_spawnStructureMob_98a1693e = 0x00F49FE0;

   //[2]?displayLocalizableMessage@CommandUtils@@YAX_NAEAVPlayer@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@@Z;
   //void __cdecl CommandUtils::displayLocalizableMessage(bool,class Player & __ptr64,class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > const & __ptr64)
    constexpr uint64_t  CommandUtils_displayLocalizableMessage_24be62e9 = 0x0071F230;

   //[3]?explode@Explosion@@QEAAXXZ;
   //public: void __cdecl Explosion::explode(void) __ptr64
    constexpr uint64_t  Explosion_explode_5adcea90 = 0x00FBB4A0;

   //[4]?fetchEntity@Level@@UEBAPEAVActor@@UActorUniqueID@@_N@Z;
   //public: virtual class Actor * __ptr64 __cdecl Level::fetchEntity(struct ActorUniqueID,bool)const __ptr64
    constexpr uint64_t  Level_fetchEntity_ff3466ce = 0x00F50E50;

   //[5]?findNextSpawnBlockUnder@Spawner@@SA_NAEBVBlockSource@@AEAVBlockPos@@W4MaterialType@@W4SpawnBlockRequirements@@@Z;
   //public: static bool __cdecl Spawner::findNextSpawnBlockUnder(class BlockSource const & __ptr64,class BlockPos & __ptr64,enum MaterialType,enum SpawnBlockRequirements)
    constexpr uint64_t  Spawner_findNextSpawnBlockUnder_65b36c80 = 0x00F50EC0;

   //[6]?forEachBlock@BlockTypeRegistry@@SAXV?$function@$$A6A_NAEBVBlockLegacy@@@Z@std@@@Z;
   //public: static void __cdecl BlockTypeRegistry::forEachBlock(class std::function<bool __cdecl(class BlockLegacy const & __ptr64)>)
    constexpr uint64_t  BlockTypeRegistry_forEachBlock_7f891f2d = 0x00EE8280;

   //[7]?forEachPlayer@Level@@UEAAXV?$function@$$A6A_NAEAVPlayer@@@Z@std@@@Z;
   //public: virtual void __cdecl Level::forEachPlayer(class std::function<bool __cdecl(class Player & __ptr64)>) __ptr64
    constexpr uint64_t  Level_forEachPlayer_71a4f564 = 0x00F51EF0;

   //[8]?getApproximateRadius@Village@@QEBAMXZ;
   //public: float __cdecl Village::getApproximateRadius(void)const __ptr64
    constexpr uint64_t  Village_getApproximateRadius_626d2648 = 0x00D73A90;

   //[9]?getBaseComponent@CircuitSceneGraph@@QEAAPEAVBaseCircuitComponent@@AEBVBlockPos@@@Z;
   //public: class BaseCircuitComponent * __ptr64 __cdecl CircuitSceneGraph::getBaseComponent(class BlockPos const & __ptr64) __ptr64
    constexpr uint64_t  CircuitSceneGraph_getBaseComponent_c4a5dbac = 0x0109A000;

   //[10]?getBedPOICount@Village@@QEBA_KXZ;
   //public: unsigned __int64 __cdecl Village::getBedPOICount(void)const __ptr64
    constexpr uint64_t  Village_getBedPOICount_016a7e2f = 0x00D73B70;

   //[11]?getBiome@BlockSource@@QEAAAEAVBiome@@AEBVBlockPos@@@Z;
   //public: class Biome & __ptr64 __cdecl BlockSource::getBiome(class BlockPos const & __ptr64) __ptr64
    constexpr uint64_t  BlockSource_getBiome_967864de = 0x00FC0ED0;

   //[12]?getBiomeType@Biome@@QEBA?AW4VanillaBiomeTypes@@XZ;
   //public: enum VanillaBiomeTypes __cdecl Biome::getBiomeType(void)const __ptr64
    constexpr uint64_t  Biome_getBiomeType_bb099b78 = 0x0103FB00;

   //[13]?getBlock@BlockSource@@UEBAAEBVBlock@@AEBVBlockPos@@@Z;
   //public: virtual class Block const & __ptr64 __cdecl BlockSource::getBlock(class BlockPos const & __ptr64)const __ptr64
    constexpr uint64_t  BlockSource_getBlock_b39e5e5d = 0x00FC14F0;

   //[14]?getCommandPermissionLevel@Player@@UEBA?AW4CommandPermissionLevel@@XZ;
   //public: virtual enum CommandPermissionLevel __cdecl Player::getCommandPermissionLevel(void)const __ptr64
    constexpr uint64_t  Player_getCommandPermissionLevel_40b0e608 = 0x00BAD9E0;

   //[15]?getDebugText@Actor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z;
   //public: virtual void __cdecl Actor::getDebugText(class std::vector<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >,class std::allocator<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > > > & __ptr64) __ptr64
    constexpr uint64_t  Actor_getDebugText_f04fad6b = 0x00B680D0;

   //[16]?getDimension@Level@@UEBAPEAVDimension@@V?$AutomaticID@VDimension@@H@@@Z;
   //public: virtual class Dimension * __ptr64 __cdecl Level::getDimension(class AutomaticID<class Dimension,int>)const __ptr64
    constexpr uint64_t  Level_getDimension_6fab9459 = 0x00F52CA0;

   //[17]?getHash@NetworkIdentifier@@QEBA_KXZ;
   //public: unsigned __int64 __cdecl NetworkIdentifier::getHash(void)const __ptr64
    constexpr uint64_t  NetworkIdentifier_getHash_d932dec8 = 0x0064CE10;

   //[18]?getMobToSpawn@BlockLegacy@@UEBAPEBVMobSpawnerData@@AEBVSpawnConditions@@AEAVBlockSource@@@Z;
   //public: virtual class MobSpawnerData const * __ptr64 __cdecl BlockLegacy::getMobToSpawn(class SpawnConditions const & __ptr64,class BlockSource & __ptr64)const __ptr64
    constexpr uint64_t  BlockLegacy_getMobToSpawn_dd8ce374 = 0x010D5DA0;

   //[19]?getName@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ;
   //public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl ItemStackBase::getName(void)const __ptr64
    constexpr uint64_t  ItemStackBase_getName_6d581a35 = 0x00CB25F0;

   //[20]?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ;
   //public: virtual class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64 __cdecl Actor::getNameTag(void)const __ptr64
    constexpr uint64_t  Actor_getNameTag_7044ab83 = 0x00B6B200;

   //[21]?getPos@Actor@@UEBAAEBVVec3@@XZ;
   //public: virtual class Vec3 const & __ptr64 __cdecl Actor::getPos(void)const __ptr64
    constexpr uint64_t  Actor_getPos_cecb628b = 0x00B6B730;

   //[22]?getViewVector@Actor@@QEBA?AVVec3@@M@Z;
   //public: class Vec3 __cdecl Actor::getViewVector(float)const __ptr64
    constexpr uint64_t  Actor_getViewVector_01c92121 = 0x00B6CAD0;

   //[23]?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVCommandRequestPacket@@@Z;
   //public: virtual void __cdecl ServerNetworkHandler::handle(class NetworkIdentifier const & __ptr64,class CommandRequestPacket const & __ptr64) __ptr64
    constexpr uint64_t  ServerNetworkHandler_handle_1a4c2996 = 0x00682E00;

   //[24]?processPendingAdds@CircuitSceneGraph@@AEAAXXZ;
   //private: void __cdecl CircuitSceneGraph::processPendingAdds(void) __ptr64
    constexpr uint64_t  CircuitSceneGraph_processPendingAdds_9d2954e5 = 0x0109C110;

   //[25]?registerCommand@CommandRegistry@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEBDW4CommandPermissionLevel@@UCommandFlag@@3@Z;
   //public: void __cdecl CommandRegistry::registerCommand(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,char const * __ptr64,enum CommandPermissionLevel,struct CommandFlag,struct CommandFlag) __ptr64
    constexpr uint64_t  CommandRegistry_registerCommand_8574de98 = 0x00731900;

   //[26]?removeComponent@CircuitSceneGraph@@AEAAXAEBVBlockPos@@@Z;
   //private: void __cdecl CircuitSceneGraph::removeComponent(class BlockPos const & __ptr64) __ptr64
    constexpr uint64_t  CircuitSceneGraph_removeComponent_1f06081d = 0x0109D5B0;

   //[27]?setBlock@BlockSource@@QEAA_NHHHAEBVBlock@@H@Z;
   //public: bool __cdecl BlockSource::setBlock(int,int,int,class Block const & __ptr64,int) __ptr64
    constexpr uint64_t  BlockSource_setBlock_71ce9a25 = 0x00FCFC40;

   //[28]?setItem@HopperBlockActor@@UEAAXHAEBVItemStack@@@Z;
   //public: virtual void __cdecl HopperBlockActor::setItem(int,class ItemStack const & __ptr64) __ptr64
    constexpr uint64_t  HopperBlockActor_setItem_c0e5f3ce = 0x01261D10;

   //[29]?setNameTag@Actor@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z;
   //public: virtual void __cdecl Actor::setNameTag(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64) __ptr64
    constexpr uint64_t  Actor_setNameTag_2f9772d3 = 0x00B86FA0;

   //[30]?setPlayerGameType@ServerPlayer@@UEAAXW4GameType@@@Z;
   //public: virtual void __cdecl ServerPlayer::setPlayerGameType(enum GameType) __ptr64
    constexpr uint64_t  ServerPlayer_setPlayerGameType_058d8c73 = 0x00737370;

   //[31]?spawnParticleEffect@Level@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVVec3@@PEAVDimension@@@Z;
   //public: virtual void __cdecl Level::spawnParticleEffect(class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const & __ptr64,class Vec3 const & __ptr64,class Dimension * __ptr64) __ptr64
    constexpr uint64_t  Level_spawnParticleEffect_52e7de09 = 0x00F5FAC0;

   //[32]?tick@Actor@@QEAA_NAEAVBlockSource@@@Z;
   //public: bool __cdecl Actor::tick(class BlockSource & __ptr64) __ptr64
    constexpr uint64_t  Actor_tick_8589defc = 0x00B8F1B0;

   //[33]?tick@Dimension@@UEAAXXZ;
   //public: virtual void __cdecl Dimension::tick(void) __ptr64
    constexpr uint64_t  Dimension_tick_39d89862 = 0x01023050;

   //[34]?tick@LevelChunk@@QEAAXAEAVBlockSource@@AEBUTick@@@Z;
   //public: void __cdecl LevelChunk::tick(class BlockSource & __ptr64,struct Tick const & __ptr64) __ptr64
    constexpr uint64_t  LevelChunk_tick_9d729ccd = 0x010233F0;

   //[35]?tick@ServerLevel@@UEAAXXZ;
   //public: virtual void __cdecl ServerLevel::tick(void) __ptr64
    constexpr uint64_t  ServerLevel_tick_86efb826 = 0x00739E00;

   //[36]?tick@Village@@QEAAXUTick@@AEAVBlockSource@@@Z;
   //public: void __cdecl Village::tick(struct Tick,class BlockSource & __ptr64) __ptr64
    constexpr uint64_t  Village_tick_2a1ecbf8 = 0x00D79DA0;

   //[37]?tickBlockEntities@LevelChunk@@QEAAXAEAVBlockSource@@@Z;
   //public: void __cdecl LevelChunk::tickBlockEntities(class BlockSource & __ptr64) __ptr64
    constexpr uint64_t  LevelChunk_tickBlockEntities_41f9b2ca = 0x01023D90;

   //[38]?tickBlocks@LevelChunk@@QEAAXAEAVBlockSource@@@Z;
   //public: void __cdecl LevelChunk::tickBlocks(class BlockSource & __ptr64) __ptr64
    constexpr uint64_t  LevelChunk_tickBlocks_66280c26 = 0x010240E0;

   //[39]?tickEntitySystems@Level@@UEAAXXZ;
   //public: virtual void __cdecl Level::tickEntitySystems(void) __ptr64
    constexpr uint64_t  Level_tickEntitySystems_251e10ba = 0x00F61AA0;

   //[40]?tickPendingTicks@BlockTickingQueue@@QEAA_NAEAVBlockSource@@AEBUTick@@H_N@Z;
   //public: bool __cdecl BlockTickingQueue::tickPendingTicks(class BlockSource & __ptr64,struct Tick const & __ptr64,int,bool) __ptr64
    constexpr uint64_t  BlockTickingQueue_tickPendingTicks_e4625213 = 0x00FD13A0;

   //[41]?tickRedstone@Dimension@@UEAAXXZ;
   //public: virtual void __cdecl Dimension::tickRedstone(void) __ptr64
    constexpr uint64_t  Dimension_tickRedstone_c8a7e6e5 = 0x01024770;

   //[42]?tickWorld@ServerPlayer@@UEAAXAEBUTick@@@Z;
   //public: virtual void __cdecl ServerPlayer::tickWorld(struct Tick const & __ptr64) __ptr64
    constexpr uint64_t  ServerPlayer_tickWorld_4b6718a8 = 0x0073A030;

   //[43]?toDebugString@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ;
   //public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl Block::toDebugString(void)const __ptr64
    constexpr uint64_t  Block_toDebugString_522cb860 = 0x010DE910;

   //[44]?tryGetStateFromLegacyData@BlockLegacy@@QEBAPEBVBlock@@G@Z;
   //public: class Block const * __ptr64 __cdecl BlockLegacy::tryGetStateFromLegacyData(unsigned short)const __ptr64
    constexpr uint64_t  BlockLegacy_tryGetStateFromLegacyData_ad225111 = 0x010DF8B0;

   //[45]?updateNeighborsAt@BlockSource@@QEAAXAEBVBlockPos@@@Z;
   //public: void __cdecl BlockSource::updateNeighborsAt(class BlockPos const & __ptr64) __ptr64
    constexpr uint64_t  BlockSource_updateNeighborsAt_4c3f8cf7 = 0x00FD1F90;

   //[46]?useOn@Item@@QEBA_NAEAVItemStack@@AEAVActor@@HHHEMMM@Z;
   //public: bool __cdecl Item::useOn(class ItemStack & __ptr64,class Actor & __ptr64,int,int,int,unsigned char,float,float,float)const __ptr64
    constexpr uint64_t  Item_useOn_35e33f80 = 0x00DED330;

}
