# Waveshare ESP32-S3-LCD-1.47 support

Adds a `waveshare147` build environment for the **Waveshare ESP32-S3-LCD-1.47**
board — the USB-A stick with the round 1.47″ 172×320 IPS display
(ST7789V3, SPI). Also sold pre-assembled as the "Nerd Miner 2 — Large Screen"
by bitcoinmerch.com.

## Why this exists

This board was **not supported** by NerdMiner before 2025, and there was still
no stock variant for it. People who flashed their stick with a community web
flasher (the closest option back then, e.g. the `NerdminerV2` build) got a
**permanently black screen**: the miner keeps mining fine, but the panel never
initialises, because no stock pin map matches this board (its LCD lives on the
high GPIO block 39–48, not on 11/12 or the LilyGo parallel bus).

## Board details

| Item | Value |
|---|---|
| Display | 1.47″ round IPS, 172×320, ST7789V3, SPI |
| LCD pins | MOSI=45, SCLK=40, CS=42, DC=41, RST=39, BL=48 |
| Button | BOOT = GPIO0 (plus hardwired RESET) |
| Flash / PSRAM | 4 MB quad flash, no usable PSRAM (`memory_type = qio_qspi`) |
| USB | Type-A, native USB-Serial-JTAG |

## Building

```bash
pio run -e waveshare147
```

Binary lands in `.pio/build/waveshare147/firmware.bin`
(the post-build script also writes a merged factory image to `firmware/`).

## Flashing

**Update an already-working stick (keeps WiFi, pool config and stats):**
flash the app partition only — everything else survives:

```bash
esptool --chip esp32s3 --port <PORT> --baud 921600 \
    write_flash 0x10000 .pio/build/waveshare147/firmware.bin
```

**Recover a stick flashed with the wrong variant** (black screen, any
firmware): the same command works without erasing flash — the existing
config.json and WiFi credentials are kept. If the config is also broken,
either use the device's config portal (it opens automatically when WiFi
credentials fail: AP `NerdMinerAP`, password `MineYourCoins`,
setup page at http://192.168.4.1), or do a full erase and start fresh:

```bash
esptool --chip esp32s3 --port <PORT> erase_flash
esptool --chip esp32s3 --port <PORT> write_flash 0x0 firmware/waveshare147_factory_merged.bin
```

## Notes

- WiFi is 2.4 GHz only (like every ESP32).
- In the config portal, the pool address field wants a **bare host or IP** —
  no `stratum+tcp://` prefix, no leading spaces. Using the pool's IP
  (e.g. `38.51.144.232` for public-pool.io) avoids DNS quirks entirely.
- The USB data lines are GPIO19/20 — never drive them in custom code, or you
  lose the USB connection until you reboot with BOOT held.
