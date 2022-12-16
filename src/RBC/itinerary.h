#pragma once
#include "../RBC/railway.h"
#include <stdbool.h>
#include <sys/types.h>


/**
 * @brief Contains data of itinerary of train.
 *
 * @param train Train name string, which identifies the itinerary for train.
 * @param current Current platform number in platform_ids. Can't be greater
 *        then platform_number.
 * @param next Next platform number in platform_ids. Can't be greater
 *        then platform_number and less then current.
 * @param platform_number Total number of platforms in platforms_ids.
 * @param platform_ids Array of identity strings of platforms. Must be sort
 *        in order to transfer.
 */
struct itinerary {
  char *train;
  size_t current;
  size_t next;
  size_t platform_number;
  char **platform_ids;
};
typedef struct itinerary Itinerary;

/**
 * @brief Get the malloc itinerary from itinerary_str, delimited by delim,
 *        and with identity name train.
 * 
 * @param itinerary_str Sequence of platform ids, delimited by delim.
 * @param delim Delimiter of platform ids in itinerary_str.
 * @param train Identity string of itinerary.
 * @return Itinerary* Constructed itinerary from itinerary_str.
 */
Itinerary *get_malloc_itinerary_from(char *itinerary_str, const char *delim,
                                     char *train);

/**
 * @brief Move to next platform from current.
 * 
 * @param railway Railway on which train moves.
 * @param itinerary Itinerary of train.
 * @param platform Platform id, on which should move train (should be next in
 *        itinerary).
 * @return true Train can move on platform.
 * @return false Train should wait for transfer of another train.
 */
bool move_to_next_platform(Railway *railway, Itinerary *itinerary,
                           char *platform);

/**
 * @brief Check if train on last platform.
 * 
 * @param itinerary Itinerary of train.
 * @return true Train on last platform.
 * @return false Train isn't reached last platform.
 */
bool is_on_last_platform_of(Itinerary itinerary);
