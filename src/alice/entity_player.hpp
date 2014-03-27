#ifndef _ALICE_ENTITY_PLAYER_HPP_
#define _ALICE_ENTITY_PLAYER_HPP_

#include <string>

#include <cstdio>
#include <cstring>

#include <alice/entity.hpp>
#include <alice/parser.hpp>

namespace dota {
    /** Contains entity information about a single player */
    class entity_player {
        public:
            /** Constructor, creates a new player with given arguments */
            entity_player(parser* p, uint32_t playerId) : p(p), ePlayer(nullptr), ePlayerRessource(nullptr) {
                // Field id for player ressource
                char id[5];
                snprintf(id, 5, "%04d", playerId);
                this->id = id;

                // Find the player/-ressource entity
                uint32_t prId = p.getEntityIdFor("CDOTA_PlayerResource");
                uint32_t pId = p.getEntityIdFor("CDOTAPlayer");

                for (auto &e : p.getEntities()) {
                    if (!e.isInitialized())
                        continue;

                    switch (e.getClassId()) {
                        case prId:
                            // there is only one so we can simply assign it
                            ePlayerResource = &e;
                            break;
                        case pId:
                            // we need to find the correct player of this playerId
                            if (e.prop<int32_t>(".m_iPlayerID") == playerId)
                                ePlayer = &e;
                            break;
                    }
                }

                // Make sure we have the correct entities
                if (ePlayer == nullptr || ePlayerRessource == nullptr) {
                    // Throw Exception: Unable to find correct player entities for playerId
                }
            }

            /** Default copy constructor */
            entity_player(const entity_player&) = default;

            /** Default move constructor */
            entity_player(entity_player&&) = default;

            /** Default destructor */
            ~entity_player() = default;

            /** Returns the name of the player */
            std::string getName() {
                return ePlayerRessource->prop<std::string>(".m_iszPlayerNames."+id);
            }

            /** Whether the player is computer controlled or not */
            bool isBot() {
                return ePlayerResource->prop<uint32_t>(".m_bFakeClient."+id) == 1;
            }

            /** Whether the player has broadcaster status or not */
            bool isBroadcaster() {
                return ePlayerResource->prop<uint32_t>(".m_bIsBroadcaster."+id) == 1;
            }

            /** Returns whether the player is afk or not */
            bool isAfk() {
                return ePlayerResource->prop<uint32_t>(".m_bAFK."+id) == 1;
            }

            /** Whether the player has fully joined the server */
            bool hasJoined() {
                return ePlayerResource->prop<uint32_t>(".m_bFullyJoinedServer."+id) == 1;
            }

            /** Has the player repicked his hero? */
            bool hasRepicked() {
                return ePlayerResource->prop<uint32_t>(".m_bHasRepicked."+id) == 1;
            }

            /** Was the hero randomed? */
            bool hasRandomed() {
                return ePlayerResource->prop<uint32_t>(".m_bHasRandomed."+id) == 1;
            }

            /** Whether the player has an active battle bonus */
            bool hasBattleBonus() {
                return ePlayerResource->prop<uint32_t>(".m_bBattleBonusActive."+id) == 1;
            }

            /** The rate at which the bonus increases exp and drop chances if any */
            int32_t getBattleBonusRate() {
                return ePlayerResource->prop<int32_t>(".m_iBattleBonusRate."+id);
            }

            /** Returns the channel if the player is a broadcaster */
            uint32_t getBroadcasterChannel() {
                return ePlayerResource->prop<uint32_t>(".m_iBroadcasterChannel."+id);
            }

            /** Returns team */
            uint32_t getTeam() {
                return ePlayerResource->prop<uint32_t>(".m_iPlayerTeams."+id);
            }

            /** Returns ID of selected hero, -1 if none selected yet */
            int32_t getHeroId() {
                return ePlayerResource->prop<int32_t>(".m_nSelectedHeroID."+id);
            }

            /** The current amount of reliable gold */
            uint32_t getGoldReliable() {
                if (playerId < 5) {
                    return ePlayerResource->prop<uint32_t>(".RadiantOnlyData.m_iReliableGoldRadiant."+id);
                } else {
                    return ePlayerResource->prop<uint32_t>(".DirOnlyData.m_iReliableGoldDire."+id);
                }
            }

            /** The current amount of unreliable gold */
            uint32_t getGoldUnreliable() {
                if (playerId < 5) {
                    return ePlayerResource->prop<uint32_t>(".RadiantOnlyData.m_iUnreliableGoldRadiant."+id);
                } else {
                    return ePlayerResource->prop<uint32_t>(".DirOnlyData.m_iUnreliableGoldDire."+id);
                }
            }

            /** The number of hero kills */
            uint32_t getKills() {
                return ePlayerResource->prop<uint32_t>(".m_iKills."+id);
            }

            /** The number of kill assits */
            uint32_t getAssists() {
                return ePlayerResource->prop<uint32_t>(".m_iAssists."+id);
            }

            /** How many times the player died */
            uint32_t getDeaths() {
                return ePlayerResource->prop<uint32_t>(".m_iDeaths."+id);
            }

            /** The number of creep kills */
            uint32_t getLasthits() {
                return ePlayerResource->prop<uint32_t>(".m_iLastHitCount."+id);
            }

            /** Consecutive creep kills */
            uint32_t getLasthitsStreak() {
                return ePlayerResource->prop<uint32_t>(".m_iLastHitStreak."+id);
            }

            /** Returns number of creeps killed at once with a single attack */
            uint32_t getLasthitMultikill() {
                return ePlayerResource->prop<uint32_t>(".m_iLastHitMultikill."+id);
            }

            /** Number of nearby creeps that could have potentially been lasthitted */
            uint32_t getLasthitsMissed() {
                return ePlayerResource->prop<uint32_t>(".m_iNearbyCreepDeathCount."+id);
            }

            /** Number of creep denies */
            uint32_t getDenies() {
                return ePlayerResource->prop<uint32_t>(".m_iDenyCount."+id);
            }

            /** Hero kill streak */
            uint32_t getKillStreak() {
                return ePlayerResource->prop<uint32_t>(".m_iStreak."+id);
            }

            /** How many seconds the hero needs to respawn */
            int32_t getRespawnTimer() {
                return ePlayerResource->prop<int32_t>(".m_iRespawnSeconds."+id);
            }

            /** Returns the time when the player last bough back */
            int32_t getLastBuyback() {
                return ePlayerResource->prop<int32_t>(".m_iLastBuybackTime."+id);
            }

            /** Returns the cooldown time on the next buyback */
            float getBuybackCooldown() {
                return ePlayerResource->prop<float>(".m_flBuybackCooldownTime."+id);
            }

            /** Total gold earned by the player  */
            uint32_t getGoldEarned() {
                return ePlayerResource->prop<uint32_t>(".EndScoreAndSpectatorStats.m_iTotalEarnedGold."+id);
            }

            /** Total exp earned by the player */
            uint32_t getExperienceEarned() {
                return ePlayerResource->prop<uint32_t>(".EndScoreAndSpectatorStats.m_iTotalEarnedXP."+id);
            }

            /** The current hero level */
            uint32_t getLevel() {
                return ePlayerResource->prop<uint32_t>(".m_iLevel."+id);
            }
        private:
            /** Pointer to the parser */
            parser* p;
            /** Pointer to the underlying alice entity */
            entity* ePlayer;
            /** Pointer to the CDOTAPlayerResource entity */
            entity* ePlayerResource;

            /** Appended player index (e.g. 0001) */
            std::string id;
    };
}

#endif /* _ALICE_ENTITY_PLAYER_HPP_ */