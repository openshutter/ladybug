#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "thread.h"

#include "ladybug_ble.h"

char ble_init_thread_stack[THREAD_STACKSIZE_MAIN];

void *init_ble_handle(void *arg) {
  ( void ) arg;
  ( void ) init_ble();
  return NULL;
}

int main(void) {
  ( void ) printf("\n\nOpenshutter Ladybug BLE Test\n\n");

  thread_create(
      ble_init_thread_stack,
      sizeof(ble_init_thread_stack),
      THREAD_PRIORITY_MAIN - 1,
      THREAD_CREATE_STACKTEST,
      init_ble_handle,
      NULL,
      "ble_init_thread");

  char line_buf[SHELL_DEFAULT_BUFSIZE];
  shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

  return 0;
}
