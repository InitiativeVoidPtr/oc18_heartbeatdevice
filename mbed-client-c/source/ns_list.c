#include "ns_list.h"



/* Pointer to the link member in entry e */
#define NS_LIST_LINK_(e, offset) ((ns_list_link_t *)((char *)(e) + offset))

/* Lvalue of the next link pointer in entry e */
#define NS_LIST_NEXT_(e, offset) (NS_LIST_LINK_(e, offset)->next)

/* Lvalue of the prev link pointer in entry e */
#define NS_LIST_PREV_(e, offset) (NS_LIST_LINK_(e, offset)->prev)

/* Convert a pointer to a link member back to the entry;
 * works for linkptr either being a ns_list_link_t pointer, or its next pointer,
 * as the next pointer is first in the ns_list_link_t */
#define NS_LIST_ENTRY_(linkptr, offset) ((void *)((char *)(linkptr) - offset))

NS_LIST_FN void ns_list_init_(ns_list_t *list)
{
    list->first_entry = NULL;
    list->last_nextptr = &list->first_entry;
}

NS_LIST_FN void ns_list_link_init_(ns_list_link_t *link)
{
    NS_FUNNY_INTPTR_OK
    link->next = NS_LIST_POISON;
    link->prev = NS_LIST_POISON;
    NS_FUNNY_INTPTR_RESTORE
}

NS_LIST_FN void ns_list_add_to_start_(ns_list_t *list, ns_list_offset_t offset, void *restrict entry)
{
    void *next;

    NS_LIST_PREV_(entry, offset) = &list->first_entry;
    NS_LIST_NEXT_(entry, offset) = next = list->first_entry;

    if (next) {
        NS_LIST_PREV_(next, offset) = &NS_LIST_NEXT_(entry, offset);
    } else {
        list->last_nextptr = &NS_LIST_NEXT_(entry, offset);
    }

    list->first_entry = entry;
}

NS_LIST_FN void ns_list_add_after_(ns_list_t *list, ns_list_offset_t offset, void *current, void *restrict entry)
{
    void *next;

    NS_LIST_PREV_(entry, offset) = &NS_LIST_NEXT_(current, offset);
    NS_LIST_NEXT_(entry, offset) = next = NS_LIST_NEXT_(current, offset);

    if (next) {
        NS_LIST_PREV_(next, offset) = &NS_LIST_NEXT_(entry, offset);
    } else {
        list->last_nextptr = &NS_LIST_NEXT_(entry, offset);
    }

    NS_LIST_NEXT_(current, offset) = entry;
}

NS_LIST_FN void ns_list_add_before_(ns_list_offset_t offset, void *current, void *restrict entry)
{
    void **prev_nextptr;

    NS_LIST_NEXT_(entry, offset) = current;
    NS_LIST_PREV_(entry, offset) = prev_nextptr = NS_LIST_PREV_(current, offset);
    *prev_nextptr = entry;
    NS_LIST_PREV_(current, offset) = &NS_LIST_NEXT_(entry, offset);
}

NS_LIST_FN void ns_list_add_to_end_(ns_list_t *list, ns_list_offset_t offset, void *restrict entry)
{
    void **prev_nextptr;

    NS_LIST_NEXT_(entry, offset) = NULL;
    NS_LIST_PREV_(entry, offset) = prev_nextptr = list->last_nextptr;
    *prev_nextptr = entry;
    list->last_nextptr = &NS_LIST_NEXT_(entry, offset);
}

NS_LIST_FN void *ns_list_get_next_(ns_list_offset_t offset, const void *current)
{
    return NS_LIST_NEXT_(current, offset);
}

NS_LIST_FN void *ns_list_get_previous_(const ns_list_t *list, ns_list_offset_t offset, const void *current)
{
    if (current == list->first_entry) {
        return NULL;
    }

    // Tricky. We don't have a direct previous pointer, but a pointer to the
    // pointer that points to us - ie &head->first_entry OR &{prev}->next.
    // This makes life easier on insertion and removal, but this is where we
    // pay the price.

    // We have to check manually for being the first entry above, so we know it's
    // a real link's next pointer. Then next is the first field of
    // ns_list_link_t, so we can use the normal offset value.

    return NS_LIST_ENTRY_(NS_LIST_PREV_(current, offset), offset);
}

NS_LIST_FN void *ns_list_get_last_(const ns_list_t *list, ns_list_offset_t offset)
{
    if (!list->first_entry) {
        return NULL;
    }

    // See comments in ns_list_get_previous_()
    return NS_LIST_ENTRY_(list->last_nextptr, offset);
}

NS_LIST_FN void ns_list_remove_(ns_list_t *list, ns_list_offset_t offset, void *removed)
{
    void *next;
    void **prev_nextptr;

    next = NS_LIST_NEXT_(removed, offset);
    prev_nextptr = NS_LIST_PREV_(removed, offset);
    if (next) {
        NS_LIST_PREV_(next, offset) = prev_nextptr;
    } else {
        list->last_nextptr = prev_nextptr;
    }
    *prev_nextptr = next;

    ns_list_link_init_(NS_LIST_LINK_(removed, offset));
}

NS_LIST_FN void ns_list_replace_(ns_list_t *list, ns_list_offset_t offset, void *current, void *restrict replacement)
{
    void *next;
    void **prev_nextptr;

    NS_LIST_PREV_(replacement, offset) = prev_nextptr = NS_LIST_PREV_(current, offset);
    NS_LIST_NEXT_(replacement, offset) = next = NS_LIST_NEXT_(current, offset);

    if (next) {
        NS_LIST_PREV_(next, offset) = &NS_LIST_NEXT_(replacement, offset);
    } else {
        list->last_nextptr = &NS_LIST_NEXT_(replacement, offset);
    }
    *prev_nextptr = replacement;

    ns_list_link_init_(NS_LIST_LINK_(current, offset));
}

NS_LIST_FN void ns_list_concatenate_(ns_list_t *dst, ns_list_t *src, ns_list_offset_t offset)
{
    ns_list_link_t *src_first;

    src_first = (ns_list_link_t*) src->first_entry;
    if (!src_first) {
        return;
    }

    *dst->last_nextptr = src_first;
    NS_LIST_PREV_(src_first, offset) = dst->last_nextptr;
    dst->last_nextptr = src->last_nextptr;

    ns_list_init_(src);
}

NS_LIST_FN uint_fast16_t ns_list_count_(const ns_list_t *list, ns_list_offset_t offset)
{
    uint_fast16_t count = 0;

    for (void *p = list->first_entry; p; p = NS_LIST_NEXT_(p, offset)) {
        count++;
    }

    return count;
}