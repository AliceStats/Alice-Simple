#ifndef _ALICE_ENTITY_GAME_HPP_
#define _ALICE_ENTITY_GAME_HPP_

#include <vector>
#include <string>

#include <alice/entity.hpp>

namespace dota {
    /** Contains method to access general game information */
    class entity_game {
        public:
            /** Constructor */
            entity_game(entity* eGame) : eGame(eGame) {

            }

            /** Default copy constructor */
            entity_game(const entity_game&) = default;

            /** Default move constructor */
            entity_game(entity_game&&) = default;

            /** Default destructor */
            ~entity_game() = default;

            /** Get the ID of this match */
            uint32_t getMatchId() {
                // .dota_gamerules_data.m_unMatchID
            }

            /** Returns name of this lobby */
            std::string getLobbyName() {
                // .dota_gamerules_data.m_lobbyGameName
            }

            /** Returns the number of players that joined the lobby */
            uint32_t getExpectedPlayers() {
                // .dota_gamerules_data.m_nExpectedPlayers
            }

            /** Returns the number of players that correctly joined the game */
            uint32_t getConnectedPlayers() {
                // .dota_gamerules_data.m_nLoadedPlayers
            }

            /** Returns Dire wins if this game is in a series */
            uint32_t getDireWins() {
                // .dota_gamerules_data.m_nDireSeriesWins
            }

            /** Returns Radiant wins if this game is in a series */
            uint32_t getRadiantWins() {
                // .dota_gamerules_data.m_nRadiantSeriesWins
            }

            /** Returns league ID if applicable */
            uint32_t getLeagueID() {
                // .dota_gamerules_data.m_lobbyLeagueID
            }

            /** Returns the game mode */
            uint32_t getGameMode() {
                 // .dota_gamerules_data.m_iGameMode
            }

            /** Returns whether this game is running the stable mode */
            bool isStableMode() {
                // .dota_gamerules_data.m_bIsStableMode
            }

            /** Returns the time at which the game has been started */
            uint32_t getGameDate() {
                // .dota_gamerules_data.m_iNetTimeOfDay
            }

            /** Returns the current state of the game */
            uint32_t getState() {
                // .dota_gamerules_data.m_nGameState
            }

            /** Returns the current hero pick state based on the game mode */
            uint32_t getPickState() {
                 // .dota_gamerules_data.m_nHeroPickState
            }

            /** Returns the team that started picking */
            uint32_t getPickTeamStart() {
                // .dota_gamerules_data.m_iStartingTeam
            }

            /** Returns the current team picking */
            uint32_t getPickTeamActive() {
                // .dota_gamerules_data.m_iActiveTeam
            }

            /** Returns player numbers of captains */
            std::vector<int32_t> getCaptains() {
                // .dota_gamerules_data.m_iCaptainPlayerIDs.0000 - 1
            }

            /** Returns the pick / ban order */
            uint32_t getPickBanOrder() {
                // .dota_gamerules_data.m_iCMModePickBanOrder
            }

            /** Returns extra pick time remaining for the radiant */
            float getRadiantPickTime() {
                // .dota_gamerules_data.m_fExtraTimeRemaining.0000
            }

            /** Returns extra pick time remaining for the dire */
            float getDirePicktime() {
                // .dota_gamerules_data.m_fExtraTimeRemaining.0001
            }

            /** Returns banned heroes in order, always 10, - 1 if not applicable */
            std::vector<int32_t> getBanned() {
                // .dota_gamerules_data.m_BannedHeroes.0000 - 09
            }

            /** Returns number of returned heroes */
            std::vector<int32_t> getSelected() {
                // .dota_gamerules_data.m_SelectedHeroes.0000 - 09
            }

            /** Returns current ingame time */
            float getTime() {
                // .dota_gamerules_data.m_fGameTime
            }

            /** Returns overall time spend including picking / pre-game phase */
            float getTimeAbsolute() {
                return getTime() - getTimeGamestart();
            }

            /** The time the game loaded */
            float getTimeLoaded() {
                 // .dota_gamerules_data.m_flGameLoadTime
            }

            /** Get the time the pregame started */
            float getTimePregame() {
                // .dota_gamerules_data.m_flPreGameStartTime
            }

            /** Get the time the game started */
            float getTimeGamestart() {
                // .dota_gamerules_data.m_flGameStartTime
            }

            /** Time the game ended if applicable */
            float getTimeEnd() {
                // .dota_gamerules_data.m_flGameEndTime
            }

            /** Whether the game is currently paused */
            bool isPaused() {
                // .dota_gamerules_data.m_bGamePaused
            }

            /** The team who paused the game */
            uint32_t getPauseTeam() {
                // .dota_gamerules_data.m_iPauseTeam
            }

            /** Cooldown of radiant glyph if applicable */
            float getGlyphCooldownRadiant() {
                // .dota_gamerules_data.m_fGoodGlyphCooldown
            }

            /** Cooldown of dire glpyh if applicable */
            float getGlyphCooldownDire() {
                // .dota_gamerules_data.m_fBadGlyphCooldown
            }

            /** Returns the team that called GG */
            uint32_t getGGTeam() {
                // .dota_gamerules_data.m_nGGTeam
            }

            /** Time the game ends because one team called GG */
            float getGGTime() {
                // .dota_gamerules_data.m_flGGEndsAtTime
            }

            /** Whether this night is caused due to nightstalker using his ultimate */
            bool isNightstalkerNight() {
                // .dota_gamerules_data.m_bIsNightstalkerNight
            }

            /** Returns the winner of the game if applicable */
            uint32_t getWinner() {
                // .dota_gamerules_data.m_nGameWinner
            }

            // CDOTAGamerulesProxy

            // Bad / Good 0 - 8
            // TODO:
            // - .dota_gamerules_data.m_ItemStockInfoBad.0000.fStockDuration
            // - .dota_gamerules_data.m_ItemStockInfoBad.0000.fStockTime
            // - .dota_gamerules_data.m_ItemStockInfoBad.0000.iMaxCount
            // - .dota_gamerules_data.m_ItemStockInfoBad.0000.iStockCount
            // - .dota_gamerules_data.m_ItemStockInfoBad.0000.usItemIndex

            // CDOTAGameManagerProxy
            // TODO:
            // - .dota_gamemanager_data.m_StableHeroAvailable. 0 - 127
        private:
            /** Points at the CDOTAGamerulesProxy entity */
            entity* eGame;
    };
}

#endif // _ALICE_ENTITY_GAME_HPP_