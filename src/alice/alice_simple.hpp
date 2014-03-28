/**
 * @file alice_simple.hpp
 * @author Robin Dietrich <me (at) invokr (dot) org>
 * @version 1.0
 *
 * @par License
 *    Alice Replay Parser
 *    Copyright 2014 Robin Dietrich
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef _ALICE_SIMPLE_HPP_
#define _ALICE_SIMPLE_HPP_

#include <string>

#include <alice/config.hpp>
#include <alice/parser.hpp>

// Make sure we have all extra libraries available
static_assert(DOTA_EXTRA, "Error: Addon libraries not available. Please compile Alice with BUILD_ADDONS=1.");

namespace dota {
    /** Class providing a high-level API to entities / objects for Alice */
    class alice_simple {
        public:
            /** The different possible types of dem_streams */
            enum stream_type {
                USE_FILE = 0,
                USE_MEMORY
            };

            /** Initializes the API by loading the given replay */
            alice_simple(std::string replay, stream_type s = USE_FILE) : p(nullptr), players(32, nullptr) {
                // Settings object for the parser
                settings parser_settings {
                    false, // forward_dem        -> Unessecary because any content is internal
                    false, // forward_net        -> Same as forward_dem
                    false, // forward_net_intern -> Nope
                    true,  // forward_user       -> Keep User-Messages ready
                    true,  // parse_stringtables -> Yes, we block the ones we don't require specifically
                    {},    // blocked            -> We don't need these tables
                    true,  // parse_entities     -> Very much nessecary
                    false, // track_entities     -> Not needed in this case, we access all information directly
                    true,  // forward_entities   -> Nessecary to assign certain entities to their parents
                    false, // skip_unused        -> No, we block the ones we don't require specifically
                    {      // blocked            -> We don't need these entities

                        // CParticleSystem
                        // CEnvDeferredLight
                        // CEnvTonemapController
                        // CDOTAPropCustomTexture
                        // CDOTAGameManagerProxy
                        // CFogController
                        // CBaseAnimating
                        // CDOTAWearableItem

                    }
                };

                // Initialize the parser with the given arguments
                switch (s) {
                    case USE_FILE:
                        p = new parser(parser_settings, new dem_stream_file);
                        p->open(replay);
                        break;
                    case USE_MEMORY:
                        p = new parser(parser_settings, new dem_stream_memory);
                        p->open(replay);
                        break;
                    default:
                        // Throw exception: Unkown parser type specified
                        break;
                }

                // Register to subscribe to further entities
                handlerRegisterCallback(p->getHandler(), msgStatus, REPLAY_FLATTABLES, alice_simple, handleReady)
            }

            /** Releases all alocated ressources */
            ~alice_simple() {
                if (p != nullptr)
                    delete p;
            }

            /** Prevent copying */
            alice_simple(const alice_simple&) = delete;

            /** Prevent moving */
            alice_simple(alice_simple&&) = delete;

            /** Returns number of currently active players */
            uint32_t countPlayers() {
                uint32_t c = 0;
                while (players[c] != nullptr && c < 31) {
                    ++c;
                }
                return c;
            }

            /** Returns pointer to specified player */
            uint32_t getPlayer(uint32_t id) {
                return players[id];
            }
        private:
            /** The APIs very own parser object */
            parser* p;
            /** Keeps track of all the players */
            std::vector<entity_player*> players;

            /** This function is called when all flattables have been parsed */
            void handleReady(handlerCbType(msgStatus) msg) {
                // contains basic game data
                handlerRegisterCallback(p->getHandler(), msgEntity, p->getEntityIdFor("CDOTAGamerulesProxy"), alice_simple, handleGame);

                // contains player ressources
                handlerRegisterCallback(p->getHandler(), msgEntity, p->getEntityIdFor("CDOTA_PlayerResource"), alice_simple, handlePlayers);

                // items bough from players (base entities and specific entities with addon fields)
                handlerRegisterCallback(p->getHandler(), msgEntity, p->getEntityIdFor("CDOTA_Item"), alice_simple, handleItemsBase);
                for (auto &itemId : p->findEntityIdFor("CDOTA_Item_")) {
                    handlerRegisterCallback(p->getHandler(), msgEntity, itemId, alice_simple, handleItemsAddon);
                }
            }

            /** Handles the creation of the gamerules proxy object */
            void handleGame(handlerCbType(msgEntity) msg) {
                // TODO: entity_game.hpp
            }

            /** Handles the player ressource object and creates new player entity representations */
            void handlePlayers(handlerCbType(msgEntity) msg) {
                char id[5];
                entity* ePlayerRessource = msg->msg;

                // check the connection state of all 32 players
                for (int i = 0; i < 32; ++i) {
                    snprintf(id, 5, "%04d", i);

                    if (ePlayerRessource->prop<uint32_t>(std::string(".m_iConnectionState.")+id) == 1)
                        continue;

                    if (players[i] != nullptr)
                        players[i] = new entity_player(p, i);
                }

                // TODO: check gametime from handle game
            }

            /** Handle all basic items that don't have special properties */
            void handleItemsBase(handlerCbType(msgEntity) msg) {
                // TODO: entity_item.hpp
            }

            /** handle all special items that have additional / unique properties */
            void handleItemsAddon(handlerCbType(msgEntity) msg) {
                // TODO: entity_item.hpp
            }
    };
}

#endif /* _ALICE_SIMPLE_HPP_ */