/*
 * Copyright (C) 2008, 2009, 2010 Kaspar Schleiser <kaspar@schleiser.de>
 * Copyright (C) 2013 INRIA
 * Copyright (C) 2013 Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Default application that shows a lot of functionality of RIOT
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "thread.h"

char ble_init_thread_stack[THREAD_STACKSIZE_SMALL];
char shell_thread_stack[THREAD_STACKSIZE_MAIN];

void *init_ble_handle(void *arg) {
  ( void ) arg;
  ( void ) init_ble();
  return NULL;
}

void *shell_handle(void *arg) {
  ( void ) arg;
  char line_buf[SHELL_DEFAULT_BUFSIZE];
  ( void ) shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
  return NULL;
}


int main(void) {
  ( void ) puts("Welcome to Shutterbug!");

  thread_create(
      ble_init_thread_stack,
      sizeof(ble_init_thread_stack),
      THREAD_PRIORITY_MAIN - 1,
      THREAD_CREATE_STACKTEST,
      init_ble_handle,
      NULL,
      "ble_init_thread");

  thread_create(
      ble_init_thread_stack,
      sizeof(shell_thread_stack),
      THREAD_PRIORITY_MAIN - 1,
      THREAD_CREATE_STACKTEST,
      shell_handle,
      NULL,
      "shell_thread");

  return 0;
}
