// Copyright 2026 Samuele Panzeri
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Store split handedness in EEPROM. The master is then auto-detected:
// whichever half is connected to USB becomes the master. Flash each half
// once with the matching bootloader target to write its handedness byte:
//   qmk flash -kb samsdactyl/promicro -km default -bl avrdude-split-right
//   qmk flash -kb samsdactyl/promicro -km default -bl avrdude-split-left
#define EE_HANDS
