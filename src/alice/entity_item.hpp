#ifndef _ALICE_ENTITY_ITEM_HPP_
#define _ALICE_ENTITY_ITEM_HPP_

namespace dota {
    /** Data related ot items that have a maximum number of stocks */
    struct item_stock {
        /** ID of the item in question */
        uint32_t item;
        /** The time until this item is restocked */
        float restock_duration;
        /** The time the next item will be added to the stock */
        float restock_date;
        /** Maximum number of items in stock at any given point */
        uint32_t items_max;
        /** Current number of items in stock */
        uint32_t items_current;
    };

    /** A single item entity */
    class item {
        public:
            /** Creates an item from it's entity */
            item(entity* item) : item(item) {

            }

            /** Entity ID of the owner */
            // .m_hOwnerEntity

            /** The owners team */
            // .m_iTeamNum

            /** When this item was purchaes */
            // .m_flPurchaseTime

            /** Who purchased this item */
            // .m_hPurchaser

            /** Name of the item */
            // .m_iName

            /** Whether this item can be activated */
            // .m_bActivated

            /** Level of the item (e.g. 1-3 for necronomicon) */
            // .m_iLevel

            /** Current toggle state */
            // .m_bToggleState

            /** Time the item comes off cooldown */
            // .m_fCooldown

            /** If the item has a cooldown, how long is it */
            // .m_flCooldownLength

            /** Cast range */
            // .m_iCastRange

            /** Mana Cost */
            // .m_iManaCost

            /** Initial number of charges */
            // .m_iInitialCharges

            /** Current charges */
            // .m_iCurrentCharges

            /** If this items requires charges to be cast */
            // .m_bRequiresCharges

            /** Combinable with other items? */
            // .m_bCombinable

            /** Is this item stackable? */
            // .m_bStackable

            /** Is this a recipe? */
            // .m_bRecipe

            /** Can this item be shared? */
            // .m_iSharability

            /** Droppable (e.g. Aegis) ? */
            // .m_bDroppable

            /** Puchasable (e.g. Aegis) ? */
            // .m_bPurchasable

            /** Sellable */
            // .m_bSellable

            /** If this item is dissasemblable */
            // .m_bDisassemblable

            /** If you can alert your teammates about this ite, */
            // .m_bAlertable
        private:
            /** Points at the entity containing the item */
            entity* item;
    };
}

#endif // _ALICE_ENTITY_ITEM_HPP_