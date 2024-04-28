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
- [ ] Rework rotary encoder so that it can control volume + RGB lightness, hue, saturation, speed without the need for
      more layers.
- [ ] Enable all (or at least more) RGB effects.
- [ ] Assign RGB effects to specific keys individually.
- [ ] Since RGB controls will be assigned to the rotary encoder + specific effect keys, remove all RGB control
      duplicates.
- [ ] Make indicator lights smarter, since they can sometimes be confused with RGB effects. Try to make them just be
      ignored on RGB effects, or maybe somehow force them to be contrasting with the current RGB effect in place.
- [ ] Host controlled colors
    - Possibly through custom Via commands (since we want both Via and the host-controlled colors, but they conflict if
      we want to use raw HID).
    - [ ] Implement Discord microphone/deafen status indicator in F13/F14 (which are the keys I use at toggle hotkeys
          in Discord).
- [ ] Dynamic caps/scroll/num/nkro lock indicators. They are currently hardcoded via `#define` but it might be
      interesting to infer the actual indicator LED indices from current keymap (ideally even accounting for remaps via
      Via).
- [ ] Add some sort of quick language switch for Windows so that I can switch between EN and ES layouts easily.
