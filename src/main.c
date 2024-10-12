#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "t.h"

#include "Library.h"

#ifdef _WIN32
#include <Windows.h>
#else
extern char **environ;
#endif

bool check_env_variable(const char *var_name) {
  char *env_value;

#ifdef _WIN32
  size_t len;
  char *buffer = NULL;
  if (_dupenv_s(&buffer, &len, var_name) == 0 && buffer != NULL) {
    env_value = buffer;
    bool result = (strcmp(env_value, "1") == 0);
    free(buffer);
    return result;
  }
  return false;
#else
  for (char **env = environ; *env != 0; env++) {
    char *this_env = *env;
    if (strncmp(this_env, var_name, strlen(var_name)) == 0 &&
        this_env[strlen(var_name)] == '=') {
      env_value = this_env + strlen(var_name) + 1;
      return strcmp(env_value, "1") == 0;
    }
  }
  return false;
#endif
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: %s <path to core> <paths to plugin>", argv[0]);
    exit(EXIT_SUCCESS);
  }

  const bool V = check_env_variable("V");

  if (V) {
    puts("Loading core");
  }
  const Library core = LibraryOpen(argv[1]);
  tInit init = (tInit)LibraryGet(core, "tInit");
  tRegisterPlugin registerPlugin =
      (tRegisterPlugin)LibraryGet(core, "tRegisterPlugin");
  tStart start = (tStart)LibraryGet(core, "tStart");

  const T t = init();
  if (!t) {
    if (V) {
      puts("Failed to initialize core");
    }
    abort();
  }

  if (V) {
    puts("Loading plugins");
  }
  for (int i = 2; i < argc; i++) {
    if (V) {
      printf("  %s: start\n", argv[i]);
    }
    Library tmp = LibraryOpen(argv[i]);
    const TPlugin plugin = (TPlugin)LibraryGet(tmp, "plugin");
    if (V) {
      printf("  %s: loaded\n", argv[i]);
    }
    if (registerPlugin(t, plugin)) {
      if (V) {
        printf("Failed to register plugin: %s\n", argv[i]);
      }
      abort();
    }
    if (V) {
      printf("  %s: done\n", argv[i]);
    }
  }
  if (V) {
    puts("done");
  }
  if (start(t)) {
    if (V) {
      puts("Failed to start");
    }
    abort();
  }
}
