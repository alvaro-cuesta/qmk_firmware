# Personal Keychron V6 ISO Encoder with Knob for Álvaro Cuesta

This keymap is based on the default Keychron layout, which has some Keychron-specific niceties along with Via supprt.

## Custom features

- [x] Fix macro keys (circle, triangle, square, cross) in Win so that they're no longer transparent into the Mac layouts
      and instead always function as F13-16
- [x] Add an additional layer for both Mac and Windows. This layer is empty (transparent) and currently not reachable, 
      but can be configured through Via. This means default Windows layer is now 3 instead of 2.
- [x] Remap keys for default Windows layout:
    - Replace screenshot (right above `ins`) with simple and default `Print Screen`.
    - Replace Cortana (right above `home`) with `Scroll Lock`.
    - Replace `RGB MOD` (right above `pgup`) with `Pause`.
    - Power off with `Fn+Pause`.
    - Via macro 0 with `Fn+Cross`.
    - Menu (application) key when pressing `FN+Win`.
- [x] Enable num-lock LED indicator. This was enabled on factory firmware as far as I know, but for some reason it was
      disabled in QMK source.
- [x] Enable scroll-lock key and LED indicator. It is positioned in the microphone key (Cortana in Windows) just like
      in traditional keyboards.
- [x] Enable NKRO LED indicator. If NKRO is on, the `N` key will be lit.
- [x] Additional rotary encoder RGB controls. By default `Fn+RotCw` will increase brightness and `Fn+RotCcw` will
      decrease it. This adds a few additional controls so that:
    - `Fn+M+RotCw/Ccw` will in/decrease effect.
    - `Fn+,+RotCw/Ccw` will in/decrease hue.
    - `Fn+.+RotCw/Ccw` will in/decrease saturation.
    - `Fn+-+RotCw/Ccw` will in/decrease speed.
- [x] Force indicators to be off even when colored by an RGB effect (see `FORCE_TURN_OFF_INDICATORS` define). This
      reduces confusion on whether the indicator is on or off.
- [x] Enabled more RGB effects, disabled some ugly ones, and set some nice defaults for RGB matrix.
- [x] Reduce RGB matrix parameter (HSV) change speed since we can control it with the rotary encoder, which is faster
      than pressing keys. In turn this allows for more precision with the rotary encoder.
- Reorganize RGB keymap now that RGB controls are assigned to the rotary encoder (thus having lots of duplicates in the
  FN1 keymap that are already covered by the rotary encoder).
    - [X] Assign individual RGB effects to specific keys. `1-'`: simple effects. `Q-O`: rainbow effects. `A-K`: 
          reactive effects. `Z-B`: raindrop effects.
        - [ ] Reorganize so similar effects are close together vertically and horizontally.
    - [ ] Assign preset colors to specific keys.
- [ ] Host controlled colors
    - Possibly through custom Via commands (since we want both Via and the host-controlled colors, but they conflict if
      we want to use raw HID) or just raw HID (`raw_hid_receive`).
    - [ ] Implement Discord microphone/deafen status indicator in F13/F14 (which are the keys I use at toggle hotkeys
          in Discord).
- [ ] Dynamic caps/scroll/num/nkro lock indicators. They are currently hardcoded via `#define` but it might be
      interesting to infer the actual indicator LED indices from current keymap (ideally even accounting for remaps via
      Via).
- [ ] Add some sort of quick language switch for Windows so that I can switch between EN and ES layouts easily.
      (`LGUI(KC_SPACE)`?)
- [ ] Better HSV mapping (`rgb_matrix_hsv_to_rgb`) since LED response across RGB is not linear, which leads to worse
      colors. Or perhaps I need to hook onto the RGB function and map there.
