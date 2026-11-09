#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"
#include "linked_list_iterator.h"
#include <assert.h>


typedef struct link link_t;
struct link
{
    value_t value;
    link_t *next;
    link_t *prev;
};

// Double linked list makes the struct more complex but makes most of the list operations easier.
struct list
{
    link_t *first;
    link_t *last;
};

//use double pointer to always have a value
struct list_iterator
{
    ioopm_list_t *list;
    link_t **prev_ptr;
};

ioopm_list_t *ioopm_list_create(void)
{
    ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));
    list->first = NULL;
    list->last = NULL;
    return list;
}

static link_t *link_destroy(link_t *link)
{
    link_t *next = link->next;
    free(link);
    return next;
}
// Is longer due to the list being double linked
static value_t unlink(ioopm_list_t *list, link_t *link)
{
    if (link->prev)
    {
        link->prev->next = link->next;
    }
    else
    {
        list->first = link->next;
    }

    if (link->next)
    {
        link->next->prev = link->prev;
    }
    else
    {
        list->last = link->prev;
    }

    value_t res = link->value;
    free(link);
    return res;
}

void ioopm_list_destroy(ioopm_list_t *list)
{
    link_t *link = list->first;
    while (link)
    {
        link = link_destroy(link);
    }
    free(list);
}

static link_t *link_create(link_t *next, link_t *prev, value_t value)
{
    link_t *link = calloc(1, sizeof(link_t));
    link->next = next;
    link->prev = prev;
    link->value = value;
    return link;
}

// Is longer due to the list being double linked
static link_t *link_add(ioopm_list_t *list, link_t *next, link_t *prev, value_t value)
{
    link_t *new = link_create(next, prev, value);

    if (prev)
    {
        prev->next = new;
    }
    else
    {
        list->first = new;
    }
    if (next)
    {
        next->prev = new;
    }
    else
    {
        list->last = new;
    }
    return new;
}

void ioopm_list_append(ioopm_list_t *list, value_t value)
{
    link_add(list, NULL, list->last, value);
}

void ioopm_list_prepend(ioopm_list_t *list, value_t value)
{
    link_add(list, list->first, NULL, value);
}

value_t ioopm_list_head(ioopm_list_t *list)
{
    return list->first->value;
}

value_t ioopm_list_last(ioopm_list_t *list)
{
    return list->last->value;
}

//There is always a preivous pointer even if there are no links
static link_t **list_find_previous_ptr(ioopm_list_t *list, size_t index)
{
    link_t **ptr = &list->first;

    for (size_t i = 0; i < index; i++)
    {
        assert(*ptr && "Index out of bounds");
        ptr = &(*ptr)->next;
    }

    return ptr;
}

void ioopm_list_insert(ioopm_list_t *list, size_t index, value_t value)
{
    link_t **prev = list_find_previous_ptr(list, index);

    if (*prev)
    {
        link_add(list, *prev, (*prev)->prev, value);
    }
    else
    {
        link_add(list, NULL, list->last, value);
    }
}

value_t ioopm_list_remove(ioopm_list_t *list, size_t index)
{
    assert(!ioopm_list_is_empty(list) && "tried to remove from empty list");

    link_t **prev = list_find_previous_ptr(list, index);
    return unlink(list, *prev);
}

value_t ioopm_list_get(ioopm_list_t *list, size_t index)
{
    link_t **prev = list_find_previous_ptr(list, index);

    assert(*prev && "Index out of bounds");

    return (*prev)->value;
}

size_t ioopm_list_size(ioopm_list_t *list)
{
    size_t size = 0;
    link_t *current = list->first;
    while (current)
    {
        current = current->next;
        size++;
    }
    return size;
}

bool ioopm_list_is_empty(ioopm_list_t *list)
{
    return !list->first;
}

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l)
{
    ioopm_list_iterator_t *it = calloc(1, sizeof(ioopm_list_iterator_t));
    it->prev_ptr = &l->first;
    it->list = l;
    return it;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter)
{
    return !*iter->prev_ptr;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter)
{
    if (!ioopm_list_iterator_at_end(iter))
    {
        iter->prev_ptr = &(*iter->prev_ptr)->next;
    }
}

value_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    return (*iter->prev_ptr)->value;
}

value_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter)
{
    link_t *to_remove = *iter->prev_ptr;
    return unlink(iter->list, to_remove);
}

void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, value_t value)
{
    if (ioopm_list_iterator_at_end(iter))
    {
        link_add(iter->list, NULL, iter->list->last, value);
    }
    else
    {
        link_t *current = *iter->prev_ptr;

        link_t *new = link_add(iter->list, current, current->prev, value);

        iter->prev_ptr = &new->next;
    }
}
