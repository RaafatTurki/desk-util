#pragma once

#include <alsa/asoundlib.h>
#include <string>

using std::string;

const string SELEM_NAME = "Master";
const string CARD_NAME = "default";

void alsa_set_volume(int volume, bool is_relative);
void alsa_set_mute(int mute_state);
