#include "alsa.h"

void alsa_set_volume(int volume, bool is_relative) {
  long min, max;
  snd_mixer_t *handle;
  snd_mixer_elem_t *elem;

  snd_mixer_open(&handle, 0);
  snd_mixer_attach(handle, CARD_NAME.c_str());
  snd_mixer_selem_register(handle, NULL, NULL);
  snd_mixer_load(handle);

  // get master element
  snd_mixer_selem_id_t *sid;
  snd_mixer_selem_id_alloca(&sid);
  snd_mixer_selem_id_set_index(sid, 0);
  snd_mixer_selem_id_set_name(sid, SELEM_NAME.c_str());
  elem = snd_mixer_find_selem(handle, sid);

  // get the volume range
  snd_mixer_selem_get_playback_volume_range(elem, &min, &max);

  // adjust the volume relatively or absolutely
  long curr_volume;
  snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_MONO, &curr_volume);

  // absolute
  volume = (max - min) * volume / 100;
  // relative
  if (is_relative) {
    volume += curr_volume;
  }

  // clamp
  if (volume < min) {
    volume = min;
  } else if (volume > max) {
    volume = max;
  }

  snd_mixer_selem_set_playback_volume_all(elem, volume);
  snd_mixer_close(handle);
}

void alsa_set_mute(int mute_state) {
  snd_mixer_t *handle;
  snd_mixer_selem_id_t *sid;

  snd_mixer_open(&handle, 0);
  snd_mixer_attach(handle, CARD_NAME.c_str());
  snd_mixer_selem_register(handle, NULL, NULL);
  snd_mixer_load(handle);

  snd_mixer_selem_id_alloca(&sid);
  snd_mixer_selem_id_set_index(sid, 0);
  snd_mixer_selem_id_set_name(sid, SELEM_NAME.c_str());
  snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

  if (mute_state == 1 || mute_state == 0) {
    snd_mixer_selem_set_playback_switch_all(elem, !mute_state);
  } else {
    snd_mixer_selem_get_playback_switch(elem, SND_MIXER_SCHN_MONO, &mute_state);
    snd_mixer_selem_set_playback_switch_all(elem, !mute_state);
  }

  snd_mixer_close(handle);
}
