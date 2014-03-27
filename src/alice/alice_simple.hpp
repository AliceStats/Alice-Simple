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
            alice_simple(std::string replay, stream_type s = USE_FILE) : p(nullptr) {
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
        private:
            /** The APIs very own parser object */
            parser* p;
    };
}

#endif /* _ALICE_SIMPLE_HPP_ */