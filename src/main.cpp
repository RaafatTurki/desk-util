#include "src/utils/alsa.h"
#include <src/utils/utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <optional>

using std::optional;

const char *argp_program_version = "audio_control 1.0";
const char *argp_program_bug_address = "<raafat.turki@proton.me>";

static char doc[] = "The all-in-one CLI that makes a cozy wm setup";

static struct argp_option argp_opts[] = {
  {"volume",      'V', "LEVEL",   0, "Set the volume level (0-100)"},
  {"volume-rel",  'v', "LEVEL",   0, "Set the relative volume level (0-100)"},
  {"mute",        'M', "[STATE]", 0, "Mute the audio (0|1)"},
  {"mute-toggle", 'm', 0,         0, "Toggle the audio"},
  {"brightness",  'b', "LEVEL",   0, "Set the brightness level (0-100)"},
  {0}
};

struct options {
  optional<int> volume_level;
  optional<bool> volume_is_relative;
  optional<int> mute_state;

  optional<int> brightness_level;
};

static error_t argp_parse_opts(int key, char *arg, struct argp_state *state) {
  struct options *args = (struct options *)state->input;

  switch (key) {
    case 'V':
      args->volume_level = optional(strtol(arg, NULL, 10));
      args->volume_is_relative = optional(false);
      break;
    case 'v':
      args->volume_level = optional(strtol(arg, NULL, 10));
      args->volume_is_relative = optional(true);
      break;
    case 'M':
      args->mute_state = optional(strtol(arg, NULL, 10));
      break;
    case 'm':
      args->mute_state = optional(-1);
      break;
    case 'b':
      args->brightness_level = strtol(arg, NULL, 10);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = {argp_opts, argp_parse_opts, NULL, doc};

int main(int argc, char *argv[]) {
  struct options opts;
  argp_parse(&argp, argc, argv, 0, 0, &opts);

  // alsa volume
  if (opts.volume_level.has_value()) {
    alsa_set_volume(opts.volume_level.value(), opts.volume_is_relative.value());
  }

  // alsa mute
  if (opts.mute_state.has_value()) {
    alsa_set_mute(opts.mute_state.value());
  }

  return 0;
}
