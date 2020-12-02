/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

bool zmk_keymap_layer_active(uint8_t layer);
int zmk_keymap_layer_activate(uint8_t layer);
int zmk_keymap_layer_deactivate(uint8_t layer);
int zmk_keymap_layer_toggle(uint8_t layer);

int zmk_keymap_position_state_changed(uint32_t position, bool pressed, int64_t timestamp);
