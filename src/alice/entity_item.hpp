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

}

#endif // _ALICE_ENTITY_ITEM_HPP_