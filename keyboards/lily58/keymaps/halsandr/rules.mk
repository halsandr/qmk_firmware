LTO_ENABLE = yes            # Link Time Optimization enabled
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE = yes            # OLED display
CAPS_WORD_ENABLE = yes      # Enable Caps Word

WPM_ENABLE = yes            # Enable Words Per Minute
WPM_SAMPLE_SECONDS = 10     # This defines how many seconds of typing to average, when calculating WPM
WPM_LAUNCH_CONTROL = yes    # WPM values will be calculated using partial buffers when typing begins

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/wpm_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/base_2_reader.c \
        ./lib/wpm_graph.c \
        # ./lib/logo_reader.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/timelogger.c \
        # ./lib/rgb_state_reader.c \
        # ./lib/keylogger.c \
        # ./lib/host_led_state_reader.c \

CONVERT_TO = helios