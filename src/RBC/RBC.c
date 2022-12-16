#include "../RBC/RBC.h"
#include "../common/alloc_macro.h"
#include "../common/string_handlers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Itinerary **get_malloc_itinerary_list(size_t *itinerary_number,
                                      socket_data socket_input) {
  struct timeval timeout;
  timeout.tv_sec = 1;
  timeout.tv_usec = 0;
  malloc_macro_def(Itinerary **, itinerary_list, sizeof(*itinerary_list));
  size_t index = 1;
  do {
    int sfd = socket_open(socket_input, AF_INET);
    if (setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) <
        0) {
      perror("socket timeout receive");
      abort();
    }
    int train_name_size = snprintf(NULL, 0, "T%zu", index) + 1;
    char train_name[train_name_size];
    sprintf(train_name, "T%zu", index);
    socket_write(&sfd, train_name, train_name_size);

    char *itinerary_str = socket_read_malloc(&sfd, "\0");
    if (!strcmp(itinerary_str, "")) {
      index--;
      break;
    }
    realloc_macro(Itinerary **, itinerary_list,
                  index * sizeof(*itinerary_list));
    itinerary_list[index - 1] =
        get_malloc_itinerary_from(itinerary_str, ", ", train_name);
  } while (index++);
  *itinerary_number = index;
  return itinerary_list;
}

int create_socket_server(char *socket_path, int max_connected_clients) {
  socket_data socket_input;
  socket_input.socket_path = socket_path;
  socket_input.max_connected_clients = max_connected_clients;
  socket_input.user = SERVER;

  return socket_open(socket_input, AF_UNIX);
}

int get_request(int sfd, const char *delim, char **train_name,
                char **platform) {
  int bla = -1;
  int *client_sfd = &bla;
  socket_accept(&sfd, client_sfd);
  char *request = socket_read_malloc(client_sfd, "\0");
  char **split_request = get_malloc_token_list(request, delim);
  free(request);
  *train_name = split_request[0];
  *platform = split_request[1];
  free(split_request);
  return *client_sfd;
}

Itinerary *get_itinerary_by_train(Itinerary *itinerary_list,
                                  size_t itinerary_number, char *train) {
  for (size_t index = 0; index < itinerary_number; index++) {
    if (!strcmp(itinerary_list[index].train, train)) {
      return &itinerary_list[index];
    }
  }

  perror("itinerary with train not found");
  abort();
}