# samsdactyl

A hand-wired Dactyl-Manuform 6x6 with an extra **4-key function row** under the bottom letters
and a **6-key thumb cluster** (2 large + 4 small 1u keys) per hand. Split, each half driven by a
Pro Micro, linked over TRRS serial. Derived from `handwired/dactyl_manuform/6x6`.

* Keyboard Maintainer: [Samuele Panzeri](https://github.com/spanzeri)
* Hardware Supported: 2x Pro Micro (ATmega32u4), TRRS soft-serial split
* 80 keys total: 5 finger rows (6 each) + 4 function keys + 6 thumb keys, per hand

## Hardware / wiring

Per hand: 6 columns × 7 rows, diodes `COL2ROW`. Split link is soft serial on `D1`.
The pins are identical to the stock `handwired/dactyl_manuform/6x6` — only the **layout** of the
bottom two rows differs (this board packs a 4-key function row + 6 thumb keys where the stock
board has 2 keys + a split thumb).

| Signal | Pins |
|--------|------|
| Columns (col 0 → 5) | `D4, C6, D7, E6, B4, B5` |
| Rows (row 0/top → row 6/thumb) | `F5, F6, F7, B1, B3, B2, B6` |
| Serial (TRRS) | `D1` |

The left half occupies matrix rows 0–6, the right half rows 7–13 (row pins are reused; the
handedness offset is applied in firmware). Finger rows (0–4 / 7–11) are the stock dactyl matrix.
The custom bottom two rows are wired as follows:

| Physical keys                    | Left matrix              | Right matrix              |
|----------------------------------|--------------------------|---------------------------|
| Function row (under Shift/Z/X/C) | `[5,0] [5,1] [5,2] [5,3]`| `[12,2] [12,3] [12,4] [12,5]` |
| Large thumb (2, top of cluster)  | `[5,4] [5,5]`            | `[12,0] [12,1]`           |
| Small thumb (4× 1u)              | `[6,2] [6,3] [6,4] [6,5]`| `[13,0] [13,1] [13,2] [13,3]` |

The two small-thumb clusters are **not** mirror images of each other — the column order differs
per half, so each was mapped on the bench. By visual position:

```
right half                             left half
top-left = [13,0]  top-right = [13,1]  top-left = [6,4]  top-right = [6,5]
bot-left = [13,2]  bot-right = [13,3]  bot-left = [6,2]  bot-right = [6,3]
```

If a thumb key ever lands in the wrong place, fix it in `info.json`'s `LAYOUT_6x6` (and mirror the
change into `samsdactyl.via.json`) — not in `keymap.c`. The layout describes the copper; the
keymap just lists keycodes in layout order. Use the `matrixtest` keymap (below) to find a key's
true `(row, col)`.

## Layers

Three layers (`default` keymap). `LOWER`/`RAISE` are momentary (`MO`) — **hold** them while
pressing another key; tapping one alone does nothing. They sit on the bottom row of the small
thumb cluster: `LOWER` on the right half, `RAISE` on the left.

* **_QWERTY** — F-row; number row (`` ` `` … `0 -`, `=` sits by `P`); QWERTY; a function row of
  `GUI / Pause / PgUp / PgDn` (left) and arrow keys (right); thumbs `Space Del / Ctrl [ / Alt RAISE`
  (left) and `Enter Bspc / ] Home / LOWER End` (right).
* **_LOWER** — shifted-number symbols, a right-hand numpad (`7 8 9 / 4 5 6 / 1 2 3 / 0`),
  brackets/parens, nav cluster on the left home row, `PrtSc`.
* **_RAISE** — F-keys, arrows on the left home row, media/transport + volume on the right,
  `Num / Ins / ScrLk / Mute`.

## Build

    qmk compile -kb samsdactyl/promicro -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the
[make guide](https://docs.qmk.fm/#/getting_started_make_guide). New to QMK? Start with the
[Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flash (split handedness)

This build uses `EE_HANDS` (`promicro/config.h`), so the **master is auto-detected** — whichever
half is plugged into USB becomes master, and a half plugged in alone works standalone. The
handedness byte is written to EEPROM at flash time, so flash each half **once** with its matching
split target:

    # right half
    qmk flash -kb samsdactyl/promicro -km default -bl avrdude-split-right

    # left half
    qmk flash -kb samsdactyl/promicro -km default -bl avrdude-split-left

Trigger the bootloader when prompted (double-tap RST, or briefly short RST→GND). After the
one-time split flash, later updates can use a plain
`qmk flash -kb samsdactyl/promicro -km default` — the EEPROM handedness persists.

### Flashing troubleshooting (Linux)

If flashing hangs at *"Detecting USB port, reset your controller now…"* and nothing happens when
you reset, the caterina bootloader port is being grabbed by **ModemManager** during its ~8 s
window:

    sudo systemctl stop ModemManager        # for the session
    sudo dmesg -w                           # (2nd terminal) watch the ttyACM* appear on reset

Also make sure you can access the port — add yourself to the `uucp` group
(`sudo usermod -aG uucp $USER`, then re-login) or run the flash under `sudo`. Trigger the reset
*after* the command is already waiting; double-tap RST→GND if the window closes too fast.

## VIA

VIA is enabled on the `default` keymap (`VIA_ENABLE = yes`). The app needs the bundled definition
`samsdactyl.via.json` (its `vendorId`/`productId` `0x444D`/`0x3636` match the firmware):

1. Open <https://usevia.app> in Chrome/Edge (needs WebHID).
2. Settings (gear) → enable **Show Design tab**.
3. **Design** tab → load `samsdactyl.via.json`.
4. Plug in the keyboard → **Configure** tab → **Authorize device**.

## Mapping the matrix (`matrixtest` keymap)

`keymaps/matrixtest/` is a throwaway diagnostic that silences all finger rows and makes the
right-hand bottom two rows print unique characters, so each physical key reveals its exact
`(row, col)`:

```
matrix row 12 (function row + large thumb): 1 2 3 4 5 6   (cols 0–5)
matrix row 13 (small thumb):                7 8 9 0 - =   (cols 0–5)
```

Flash it (`-km matrixtest`), press the bottom keys in a text editor, and read off the columns.
It was used to nail down the small-thumb wiring; keep it for mapping the left half, or delete
`keymaps/matrixtest/` for a clean tree.

## Bootloader

Enter the bootloader by:

* **Physical reset** — briefly short RST to GND on the Pro Micro (double-tap for caterina)
* **Keycode** — press a key mapped to `QK_BOOT` (not currently in the keymap; add one in VIA if
  you want on-board reset)

## Notes

* `KC_GRV` occupies the top-left of the number row (it replaced an invalid `KC_NAGR` from the
  initial draft) — remap in VIA if you intended something else.
* The `blackpill_f411/` variant is inherited from the base dactyl and uses different (STM32) pins
  and a hardware handedness pin; it is not used by this Pro Micro build.
