if(CONFIG_ZMK_DISPLAY AND CONFIG_NICE_VIEW_WIDGET_STATUS)
  zephyr_library_include_directories(${CMAKE_SOURCE_DIR}/include)

  # Framebuffer-only sources: keep the minimal set needed for the SSD1306/Corne port.
  # Avoid LVGL-generated images and fonts which pull LVGL into the build.
  zephyr_library_sources(
    ./src/main.c
    ./src/utils/oled_fb.c
    ./src/utils/draw_animation1.c
    ./src/utils/draw_animation2.c
    ./src/utils/draw_battery.c
    ./src/utils/draw_bluetooth_logo.c
    ./src/utils/draw_bluetooth_logo_outlined.c
    ./src/utils/draw_bluetooth_searching.c
    ./src/utils/draw_usb_logo.c
    ./src/utils/rotate_connectivity_canvas.c
    ./src/utils/rotate_main2_canvas.c
    ./src/images/animation1_frames_mono.c
    ./src/images/animation2_frames_mono.c
  )

  if(NOT CONFIG_ZMK_SPLIT OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    zephyr_library_sources(
      ./src/central/initialize_listeners.c
      ./src/central/render.c
    )
  else()
    zephyr_library_sources(
      ./src/peripheral/initialize_listeners.c
      ./src/peripheral/render.c
    )
  endif()
endif()
