#pragma once
namespace SymHook {
    //[1]??$tryGetComponent@VUserEntityIdentifierComponent@@@Actor@@QEAAPEAVUserEntityIdentifierComponent@@XZ;
    // public: class UserEntityIdentifierComponent * __ptr64 __cdecl
    // Actor::tryGetComponent<class UserEntityIdentifierComponent>(void) __ptr64
    constexpr uint64_t
        Actor_tryGetComponent_UserEntityIdentifierComponent_4bafed89 =
            0x0056B0C0;

    //[2]?_spawnStructureMob@Spawner@@AEAAXAEAVBlockSource@@AEBVBlockPos@@AEBUHardcodedSpawningArea@LevelChunk@@AEBVSpawnConditions@@@Z;
    // private: void __cdecl Spawner::_spawnStructureMob(class BlockSource &
    // __ptr64,class BlockPos const & __ptr64,struct
    // LevelChunk::HardcodedSpawningArea const & __ptr64,class SpawnConditions
    // const & __ptr64) __ptr64
    constexpr uint64_t Spawner_spawnStructureMob_98a1693e = 0x00F32620;

    //[3]?displayLocalizableMessage@CommandUtils@@YAX_NAEAVPlayer@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@4@@Z;
    // void __cdecl CommandUtils::displayLocalizableMessage(bool,class Player &
    // __ptr64,class std::basic_string<char,struct std::char_traits<char>,class
    // std::allocator<char> > const & __ptr64,class std::vector<class
    // std::basic_string<char,struct std::char_traits<char>,class
    // std::allocator<char> >,class std::allocator<class
    // std::basic_string<char,struct std::char_traits<char>,class
    // std::allocator<char> > > > const & __ptr64)
    constexpr uint64_t CommandUtils_displayLocalizableMessage_24be62e9 =
        0x006E30E0;

    //[4]?explode@Explosion@@QEAAXXZ;
    // public: void __cdecl Explosion::explode(void) __ptr64
    constexpr uint64_t Explosion_explode_5adcea90 = 0x00FA6B20;

    //[5]?fetchEntity@Level@@UEBAPEAVActor@@UActorUniqueID@@_N@Z;
    // public: virtual class Actor * __ptr64 __cdecl Level::fetchEntity(struct
    // ActorUniqueID,bool)const __ptr64
    constexpr uint64_t Level_fetchEntity_ff3466ce = 0x00F39570;

    //[6]?findNextSpawnBlockUnder@Spawner@@SA_NAEBVBlockSource@@AEAVBlockPos@@W4MaterialType@@W4SpawnBlockRequirements@@@Z;
    // public: static bool __cdecl Spawner::findNextSpawnBlockUnder(class
    // BlockSource const & __ptr64,class BlockPos & __ptr64,enum
    // MaterialType,enum SpawnBlockRequirements)
    constexpr uint64_t Spawner_findNextSpawnBlockUnder_65b36c80 = 0x00F395E0;

    //[7]?forEachBlock@BlockTypeRegistry@@SAXV?$function@$$A6A_NAEBVBlockLegacy@@@Z@std@@@Z;
    // public: static void __cdecl BlockTypeRegistry::forEachBlock(class
    // std::function<bool __cdecl(class BlockLegacy const & __ptr64)>)
    constexpr uint64_t BlockTypeRegistry_forEachBlock_7f891f2d = 0x00ED0040;

    //[8]?forEachPlayer@Level@@UEAAXV?$function@$$A6A_NAEAVPlayer@@@Z@std@@@Z;
    // public: virtual void __cdecl Level::forEachPlayer(class
    // std::function<bool __cdecl(class Player & __ptr64)>) __ptr64
    constexpr uint64_t Level_forEachPlayer_71a4f564 = 0x00F3A610;

    //[9]?getApproximateRadius@Village@@QEBAMXZ;
    // public: float __cdecl Village::getApproximateRadius(void)const __ptr64
    constexpr uint64_t Village_getApproximateRadius_626d2648 = 0x00D4F4C0;

    //[10]?getBaseComponent@CircuitSceneGraph@@QEAAPEAVBaseCircuitComponent@@AEBVBlockPos@@@Z;
    // public: class BaseCircuitComponent * __ptr64 __cdecl
    // CircuitSceneGraph::getBaseComponent(class BlockPos const & __ptr64)
    // __ptr64
    constexpr uint64_t CircuitSceneGraph_getBaseComponent_c4a5dbac = 0x01088760;

    //[11]?getBedPOICount@Village@@QEBA_KXZ;
    // public: unsigned __int64 __cdecl Village::getBedPOICount(void)const
    // __ptr64
    constexpr uint64_t Village_getBedPOICount_016a7e2f = 0x00D4F5A0;

    //[12]?getBiome@BlockSource@@QEAAAEAVBiome@@AEBVBlockPos@@@Z;
    // public: class Biome & __ptr64 __cdecl BlockSource::getBiome(class
    // BlockPos const & __ptr64) __ptr64
    constexpr uint64_t BlockSource_getBiome_967864de = 0x00FAC550;

    //[13]?getBiomeType@Biome@@QEBA?AW4VanillaBiomeTypes@@XZ;
    // public: enum VanillaBiomeTypes __cdecl Biome::getBiomeType(void)const
    // __ptr64
    constexpr uint64_t Biome_getBiomeType_bb099b78 = 0x0102DC20;

    //[14]?getBlock@BlockSource@@UEBAAEBVBlock@@AEBVBlockPos@@@Z;
    // public: virtual class Block const & __ptr64 __cdecl
    // BlockSource::getBlock(class BlockPos const & __ptr64)const __ptr64
    constexpr uint64_t BlockSource_getBlock_b39e5e5d = 0x00FACB80;

    //[15]?getBlock@BlockSource@@UEBAAEBVBlock@@HHH@Z;
    // public: virtual class Block const & __ptr64 __cdecl
    // BlockSource::getBlock(int,int,int)const __ptr64
    constexpr uint64_t BlockSource_getBlock_6df88a51 = 0x00FACC20;

    //[16]?getCommandPermissionLevel@Player@@UEBA?AW4CommandPermissionLevel@@XZ;
    // public: virtual enum CommandPermissionLevel __cdecl
    // Player::getCommandPermissionLevel(void)const __ptr64
    constexpr uint64_t Player_getCommandPermissionLevel_40b0e608 = 0x00B87340;

    //[17]?getDebugText@Actor@@UEAAXAEAV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z;
    // public: virtual void __cdecl Actor::getDebugText(class std::vector<class
    // std::basic_string<char,struct std::char_traits<char>,class
    // std::allocator<char> >,class std::allocator<class
    // std::basic_string<char,struct std::char_traits<char>,class
    // std::allocator<char> > > > & __ptr64) __ptr64
    constexpr uint64_t Actor_getDebugText_f04fad6b = 0x00B41280;

    //[18]?getDimension@Level@@UEBAPEAVDimension@@V?$AutomaticID@VDimension@@H@@@Z;
    // public: virtual class Dimension * __ptr64 __cdecl
    // Level::getDimension(class AutomaticID<class Dimension,int>)const __ptr64
    constexpr uint64_t Level_getDimension_6fab9459 = 0x00F3B3D0;

    //[19]?getHash@NetworkIdentifier@@QEBA_KXZ;
    // public: unsigned __int64 __cdecl NetworkIdentifier::getHash(void)const
    // __ptr64
    constexpr uint64_t NetworkIdentifier_getHash_d932dec8 = 0x0060C2B0;

    //[20]?getMobToSpawn@BlockLegacy@@UEBAPEBVMobSpawnerData@@AEBVSpawnConditions@@AEAVBlockSource@@@Z;
    // public: virtual class MobSpawnerData const * __ptr64 __cdecl
    // BlockLegacy::getMobToSpawn(class SpawnConditions const & __ptr64,class
    // BlockSource & __ptr64)const __ptr64
    constexpr uint64_t BlockLegacy_getMobToSpawn_dd8ce374 = 0x010C48D0;

    //[21]?getName@ItemStackBase@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ;
    // public: class std::basic_string<char,struct std::char_traits<char>,class
    // std::allocator<char> > __cdecl ItemStackBase::getName(void)const __ptr64
    constexpr uint64_t ItemStackBase_getName_6d581a35 = 0x00C8F2E0;

    //[22]?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ;
    // public: virtual class std::basic_string<char,struct
    // std::char_traits<char>,class std::allocator<char> > const & __ptr64
    // __cdecl Actor::getNameTag(void)const __ptr64
    constexpr uint64_t Actor_getNameTag_7044ab83 = 0x00B444C0;

    //[23]?getPos@Actor@@UEBAAEBVVec3@@XZ;
    // public: virtual class Vec3 const & __ptr64 __cdecl
    // Actor::getPos(void)const __ptr64
    constexpr uint64_t Actor_getPos_cecb628b = 0x00B449E0;

    //[24]?getRegion@Actor@@QEBAAEAVBlockSource@@XZ;
    // public: class BlockSource & __ptr64 __cdecl Actor::getRegion(void)const
    // __ptr64
    constexpr uint64_t Actor_getRegion_757c8f63 = 0x00B44D30;

    //[25]?getViewVector@Actor@@QEBA?AVVec3@@M@Z;
    // public: class Vec3 __cdecl Actor::getViewVector(float)const __ptr64
    constexpr uint64_t Actor_getViewVector_01c92121 = 0x00B45DC0;

    //[26]?handle@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBVCommandRequestPacket@@@Z;
    // public: virtual void __cdecl ServerNetworkHandler::handle(class
    // NetworkIdentifier const & __ptr64,class CommandRequestPacket const &
    // __ptr64) __ptr64
    constexpr uint64_t ServerNetworkHandler_handle_1a4c2996 = 0x00642D70;

    //[27]?processPendingAdds@CircuitSceneGraph@@AEAAXXZ;
    // private: void __cdecl CircuitSceneGraph::processPendingAdds(void) __ptr64
    constexpr uint64_t CircuitSceneGraph_processPendingAdds_9d2954e5 =
        0x0108ABB0;

    //[28]?registerCommand@CommandRegistry@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEBDW4CommandPermissionLevel@@UCommandFlag@@3@Z;
    // public: void __cdecl CommandRegistry::registerCommand(class
    // std::basic_string<char,struct std::char_traits<char>,class
    // std::allocator<char> > const & __ptr64,char const * __ptr64,enum
    // CommandPermissionLevel,struct CommandFlag,struct CommandFlag) __ptr64
    constexpr uint64_t CommandRegistry_registerCommand_8574de98 = 0x006F5FE0;

    //[29]?removeComponent@CircuitSceneGraph@@AEAAXAEBVBlockPos@@@Z;
    // private: void __cdecl CircuitSceneGraph::removeComponent(class BlockPos
    // const & __ptr64) __ptr64
    constexpr uint64_t CircuitSceneGraph_removeComponent_1f06081d = 0x0108C060;

    //[30]?setBlock@BlockSource@@QEAA_NHHHAEBVBlock@@H@Z;
    // public: bool __cdecl BlockSource::setBlock(int,int,int,class Block const
    // & __ptr64,int) __ptr64
    constexpr uint64_t BlockSource_setBlock_71ce9a25 = 0x00FBAD90;

    //[31]?setItem@HopperBlockActor@@UEAAXHAEBVItemStack@@@Z;
    // public: virtual void __cdecl HopperBlockActor::setItem(int,class
    // ItemStack const & __ptr64) __ptr64
    constexpr uint64_t HopperBlockActor_setItem_c0e5f3ce = 0x01269DD0;

    //[32]?setNameTag@Actor@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z;
    // public: virtual void __cdecl Actor::setNameTag(class
    // std::basic_string<char,struct std::char_traits<char>,class
    // std::allocator<char> > const & __ptr64) __ptr64
    constexpr uint64_t Actor_setNameTag_2f9772d3 = 0x00B618B0;

    //[33]?setPlayerGameType@ServerPlayer@@UEAAXW4GameType@@@Z;
    // public: virtual void __cdecl ServerPlayer::setPlayerGameType(enum
    // GameType) __ptr64
    constexpr uint64_t ServerPlayer_setPlayerGameType_058d8c73 = 0x006FBF10;

    //[34]?spawnParticleEffect@Level@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVVec3@@PEAVDimension@@@Z;
    // public: virtual void __cdecl Level::spawnParticleEffect(class
    // std::basic_string<char,struct std::char_traits<char>,class
    // std::allocator<char> > const & __ptr64,class Vec3 const & __ptr64,class
    // Dimension * __ptr64) __ptr64
    constexpr uint64_t Level_spawnParticleEffect_52e7de09 = 0x00F485B0;

    //[35]?tick@Actor@@QEAA_NAEAVBlockSource@@@Z;
    // public: bool __cdecl Actor::tick(class BlockSource & __ptr64) __ptr64
    constexpr uint64_t Actor_tick_8589defc = 0x00B68FF0;

    //[36]?tick@Dimension@@UEAAXXZ;
    // public: virtual void __cdecl Dimension::tick(void) __ptr64
    constexpr uint64_t Dimension_tick_39d89862 = 0x0100FCD0;

    //[37]?tick@LevelChunk@@QEAAXAEAVBlockSource@@AEBUTick@@@Z;
    // public: void __cdecl LevelChunk::tick(class BlockSource & __ptr64,struct
    // Tick const & __ptr64) __ptr64
    constexpr uint64_t LevelChunk_tick_9d729ccd = 0x01010070;

    //[38]?tick@ServerLevel@@UEAAXXZ;
    // public: virtual void __cdecl ServerLevel::tick(void) __ptr64
    constexpr uint64_t ServerLevel_tick_86efb826 = 0x006FF110;

    //[39]?tick@Village@@QEAAXUTick@@AEAVBlockSource@@@Z;
    // public: void __cdecl Village::tick(struct Tick,class BlockSource &
    // __ptr64) __ptr64
    constexpr uint64_t Village_tick_2a1ecbf8 = 0x00D55AD0;

    //[40]?tickBlockEntities@LevelChunk@@QEAAXAEAVBlockSource@@@Z;
    // public: void __cdecl LevelChunk::tickBlockEntities(class BlockSource &
    // __ptr64) __ptr64
    constexpr uint64_t LevelChunk_tickBlockEntities_41f9b2ca = 0x01010A50;

    //[41]?tickBlocks@LevelChunk@@QEAAXAEAVBlockSource@@@Z;
    // public: void __cdecl LevelChunk::tickBlocks(class BlockSource & __ptr64)
    // __ptr64
    constexpr uint64_t LevelChunk_tickBlocks_66280c26 = 0x01010DA0;

    //[42]?tickEntitySystems@Level@@UEAAXXZ;
    // public: virtual void __cdecl Level::tickEntitySystems(void) __ptr64
    constexpr uint64_t Level_tickEntitySystems_251e10ba = 0x00F4A5D0;

    //[43]?tickPendingTicks@BlockTickingQueue@@QEAA_NAEAVBlockSource@@AEBUTick@@H_N@Z;
    // public: bool __cdecl BlockTickingQueue::tickPendingTicks(class
    // BlockSource & __ptr64,struct Tick const & __ptr64,int,bool) __ptr64
    constexpr uint64_t BlockTickingQueue_tickPendingTicks_e4625213 = 0x00FBC5B0;

    //[44]?tickRedstone@Dimension@@UEAAXXZ;
    // public: virtual void __cdecl Dimension::tickRedstone(void) __ptr64
    constexpr uint64_t Dimension_tickRedstone_c8a7e6e5 = 0x01011480;

    //[45]?tickWorld@ServerPlayer@@UEAAXAEBUTick@@@Z;
    // public: virtual void __cdecl ServerPlayer::tickWorld(struct Tick const &
    // __ptr64) __ptr64
    constexpr uint64_t ServerPlayer_tickWorld_4b6718a8 = 0x006FF340;

    //[46]?toDebugString@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ;
    // public: class std::basic_string<char,struct std::char_traits<char>,class
    // std::allocator<char> > __cdecl Block::toDebugString(void)const __ptr64
    constexpr uint64_t Block_toDebugString_522cb860 = 0x010CD6F0;

    //[47]?tryGetStateFromLegacyData@BlockLegacy@@QEBAPEBVBlock@@G@Z;
    // public: class Block const * __ptr64 __cdecl
    // BlockLegacy::tryGetStateFromLegacyData(unsigned short)const __ptr64
    constexpr uint64_t BlockLegacy_tryGetStateFromLegacyData_ad225111 =
        0x010CE700;

    //[48]?updateNeighborsAt@BlockSource@@QEAAXAEBVBlockPos@@@Z;
    // public: void __cdecl BlockSource::updateNeighborsAt(class BlockPos const
    // & __ptr64) __ptr64
    constexpr uint64_t BlockSource_updateNeighborsAt_4c3f8cf7 = 0x00FBD290;

    //[49]?useOn@Item@@QEBA_NAEAVItemStack@@AEAVActor@@HHHEMMM@Z;
    // public: bool __cdecl Item::useOn(class ItemStack & __ptr64,class Actor &
    // __ptr64,int,int,int,unsigned char,float,float,float)const __ptr64
    constexpr uint64_t Item_useOn_35e33f80 = 0x00DD5900;

}  // namespace SymHook
