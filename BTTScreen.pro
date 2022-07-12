QT += quick

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        module/QmlLanguage.cpp

HEADERS += \
    module/QmlLanguage.h

RESOURCES += qml.qrc

TRANSLATIONS += \
    language/BTTScreen_en_US.ts\
    language/BTTScreen_zh_CN.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    config/Notice_phrase.json \
    config/Preheat_Custom.json \
    config/UserDefine.json \
    language/BTTScreen_en_US.qm \
    language/BTTScreen_zh_CN.qm \
    main.qml \
    moonraker/API/APIs \
    moonraker/API/access/delete_user_request_api.json \
    moonraker/API/access/delete_user_returns.json \
    moonraker/API/access/get_user_returns.json \
    moonraker/API/access/post_login_request_api.json \
    moonraker/API/access/post_login_returns.json \
    moonraker/API/access/post_logout_request_api.json \
    moonraker/API/access/post_refresh_jwt_request_api.json \
    moonraker/API/access/post_refresh_jwt_returns.json \
    moonraker/API/access/post_user_request_api.json \
    moonraker/API/access/post_user_returns.json \
    moonraker/API/access/users/get_list_returns.json \
    moonraker/API/access/users/post_password_request_api.json \
    moonraker/API/access/users/post_password_returns.json \
    moonraker/API/api/get_job_returns.json \
    moonraker/API/api/get_login_returns.json \
    moonraker/API/api/get_printer_returns.json \
    moonraker/API/api/get_printerprofiles_returns.json \
    moonraker/API/api/get_server_returns.json \
    moonraker/API/api/get_settings_returns.json \
    moonraker/API/api/get_version_returns.json \
    moonraker/API/api/printer/post_command_request_api.json \
    moonraker/API/api/printer/post_command_returns.json \
    moonraker/API/machine/device_power/get_device_request_rpc.json \
    moonraker/API/machine/device_power/get_device_returns.json \
    moonraker/API/machine/device_power/get_devices_request_rpc.json \
    moonraker/API/machine/device_power/get_devices_returns.json \
    moonraker/API/machine/device_power/get_status_request_rpc.json \
    moonraker/API/machine/device_power/get_status_returns.json \
    moonraker/API/machine/device_power/post_device_request_rpc.json \
    moonraker/API/machine/device_power/post_device_returns.json \
    moonraker/API/machine/device_power/post_off_request_rpc.json \
    moonraker/API/machine/device_power/post_off_returns.json \
    moonraker/API/machine/device_power/post_on_request_rpc.json \
    moonraker/API/machine/device_power/post_on_returns.json \
    moonraker/API/machine/get_proc_stats_request_rpc.json \
    moonraker/API/machine/get_proc_stats_returns.json \
    moonraker/API/machine/get_system_info_request_rpc.json \
    moonraker/API/machine/get_system_info_returns.json \
    moonraker/API/machine/post_reboot_request_rpc.json \
    moonraker/API/machine/post_shutdown_request_rpc.json \
    moonraker/API/machine/services/post_restart_request_rpc.json \
    moonraker/API/machine/services/post_start_request_rpc.json \
    moonraker/API/machine/services/post_stop_request_rpc.json \
    moonraker/API/machine/update/get_status_request_rpc.json \
    moonraker/API/machine/update/get_status_returns.json \
    moonraker/API/machine/update/post_client_request_rpc.json \
    moonraker/API/machine/update/post_full_request_rpc.json \
    moonraker/API/machine/update/post_klipper_request_rpc.json \
    moonraker/API/machine/update/post_moonraker_request_rpc.json \
    moonraker/API/machine/update/post_recover_request_rpc.json \
    moonraker/API/machine/update/post_system_request_rpc.json \
    moonraker/API/printer/gcode/post_help_request_rpc.json \
    moonraker/API/printer/gcode/post_help_returns.json \
    moonraker/API/printer/gcode/post_script_request_rpc.json \
    moonraker/API/printer/get_info_request_rpc.json \
    moonraker/API/printer/get_info_returns.json \
    moonraker/API/printer/objects/get_list_request_rpc.json \
    moonraker/API/printer/objects/get_list_returns.json \
    moonraker/API/printer/objects/get_query_request_rpc.json \
    moonraker/API/printer/objects/get_query_returns.json \
    moonraker/API/printer/objects/post_subscribe_request_rpc.json \
    moonraker/API/printer/objects/post_subscribe_returns.json \
    moonraker/API/printer/post_emergency_stop_request_rpc.json \
    moonraker/API/printer/post_firmware_restart_request_rpc.json \
    moonraker/API/printer/post_restart_request_rpc.json \
    moonraker/API/printer/print/post_cancel_request_rpc.json \
    moonraker/API/printer/print/post_pause_request_rpc.json \
    moonraker/API/printer/print/post_resume_reques_rpc.json \
    moonraker/API/printer/print/post_start_request_rpc.json \
    moonraker/API/printer/query_endstops/get_status_request_rpc.json \
    moonraker/API/printer/query_endstops/get_status_returns.json \
    moonraker/API/server/database/delete_item_request_rpc.json \
    moonraker/API/server/database/delete_item_returns.json \
    moonraker/API/server/database/get_item_request_rpc.json \
    moonraker/API/server/database/get_item_returns.json \
    moonraker/API/server/database/get_list_request_rpc.json \
    moonraker/API/server/database/get_list_returns.json \
    moonraker/API/server/database/post_item_request_api.json \
    moonraker/API/server/database/post_item_request_rpc.json \
    moonraker/API/server/database/post_item_returns.json \
    moonraker/API/server/files/delete_directory_request_rpc.json \
    moonraker/API/server/files/delete_directory_returns.json \
    moonraker/API/server/files/delete_file_request_rpc.json \
    moonraker/API/server/files/delete_file_returns.json \
    moonraker/API/server/files/get_directory_request_rpc.json \
    moonraker/API/server/files/get_directory_returns.json \
    moonraker/API/server/files/get_list_request_rpc.json \
    moonraker/API/server/files/get_list_returns.json \
    moonraker/API/server/files/get_metadata_request_rpc.json \
    moonraker/API/server/files/get_metadata_returns.json \
    moonraker/API/server/files/post_copy_request_rpc.json \
    moonraker/API/server/files/post_copy_returns.json \
    moonraker/API/server/files/post_directory_request_rpc.json \
    moonraker/API/server/files/post_directory_returns.json \
    moonraker/API/server/files/post_move_request_rpc.json \
    moonraker/API/server/files/post_move_returns.json \
    moonraker/API/server/files/post_upload_returns.json \
    moonraker/API/server/get_config_request_rpc.json \
    moonraker/API/server/get_config_returns.json \
    moonraker/API/server/get_gcode_store_request_rpc.json \
    moonraker/API/server/get_gcode_store_returns.json \
    moonraker/API/server/get_info_request_rpc.json \
    moonraker/API/server/get_info_returns.json \
    moonraker/API/server/get_temperature_store_request_rpc.json \
    moonraker/API/server/get_temperature_store_returns.json \
    moonraker/API/server/history/delete_job_request_rpc.json \
    moonraker/API/server/history/delete_job_returns.json \
    moonraker/API/server/history/get_job_request_rpc.json \
    moonraker/API/server/history/get_job_returns.json \
    moonraker/API/server/history/get_list_request_rpc.json \
    moonraker/API/server/history/get_list_returns.json \
    moonraker/API/server/history/get_totals_request_rpc.json \
    moonraker/API/server/history/get_totals_returns.json \
    moonraker/API/server/mqtt/post_publish_request_api.json \
    moonraker/API/server/mqtt/post_publish_request_rpc.json \
    moonraker/API/server/mqtt/post_publish_returns.json \
    moonraker/API/server/mqtt/post_subscribe_request_api.json \
    moonraker/API/server/mqtt/post_subscribe_request_rpc.json \
    moonraker/API/server/mqtt/post_subscribe_returns.json \
    moonraker/API/server/post_restart_request_rpc.json \
    moonraker/Websocket/Authorized User Created.json \
    moonraker/Websocket/Authorized User Deleted.json \
    moonraker/Websocket/CPU Throttled.json \
    moonraker/Websocket/File List Changed.json \
    moonraker/Websocket/Gcode Response.json \
    moonraker/Websocket/Get Websocket ID_request.json \
    moonraker/Websocket/Get Websocket ID_returns.json \
    moonraker/Websocket/History Changed.json \
    moonraker/Websocket/Initialize/Initialize.json \
    moonraker/Websocket/Initialize/machine.proc_stats.json \
    moonraker/Websocket/Initialize/machine.system_info.json \
    moonraker/Websocket/Initialize/machine.update.status.json \
    moonraker/Websocket/Initialize/notify_status_update.json \
    moonraker/Websocket/Initialize/printer.gcode.help.json \
    moonraker/Websocket/Initialize/printer.info.json \
    moonraker/Websocket/Initialize/printer.objects.list.json \
    moonraker/Websocket/Initialize/printer.objects.subscribe.json \
    moonraker/Websocket/Initialize/server.config.json \
    moonraker/Websocket/Initialize/server.gcode_store.json \
    moonraker/Websocket/Initialize/server.history.list.json \
    moonraker/Websocket/Initialize/server.history.totals.json \
    moonraker/Websocket/Initialize/server.info.json \
    moonraker/Websocket/Initialize/server.temperature_store.json \
    moonraker/Websocket/Klippy Disconnected.json \
    moonraker/Websocket/Klippy Ready.json \
    moonraker/Websocket/Klippy Shutdown.json \
    moonraker/Websocket/Moonraker Process Statistic Update.json \
    moonraker/Websocket/Subscriptions.json \
    moonraker/Websocket/Update Manager Refreshed.json \
    moonraker/Websocket/Update Manager Response.json \
    moonraker/Websocket/Websocket notifications 1.json \
    moonraker/Websocket/Websocket notifications 2.json \
    qml_page/Common_Keyboard.qml \
    qml_page/Common_RemindDialog.qml \
    qml_page/Page_camera.qml \
    qml_page/Page_console.qml \
    qml_page/Page_extruder.qml \
    qml_page/Page_fan.qml \
    qml_page/Page_level.qml \
    qml_page/Page_main.qml \
    qml_page/Page_move.qml \
    qml_page/Page_print.qml \
    qml_page/Page_settings.qml \
    qml_page/Page_temperature.qml \
    qml_page/module_camera/Coordinate_view_panel.qml \
    qml_page/module_camera/Demo.jpeg \
    qml_page/module_camera/Function_Button.qml \
    qml_page/module_camera/flip_H.svg \
    qml_page/module_camera/flip_V.svg \
    qml_page/module_camera/flip_deg.svg \
    qml_page/module_camera/title_fan.svg \
    qml_page/module_camera/title_heatbed.svg \
    qml_page/module_camera/title_hotend.svg \
    qml_page/module_common/Halo.qml \
    qml_page/module_common/Preview_Submodule.qml \
    qml_page/module_common/Public_Back_Button.qml \
    qml_page/module_common/Trapezoidal.qml \
    qml_page/module_common/back.svg \
    qml_page/module_common/title_heatbed.svg \
    qml_page/module_common/title_hotend.svg \
    qml_page/module_console/Console_Input.qml \
    qml_page/module_console/Sender_Button.qml \
    qml_page/module_extruder/Function_Button.qml \
    qml_page/module_extruder/Preheat_Std.qml \
    qml_page/module_extruder/Preheat_Std_Submodule.qml \
    qml_page/module_extruder/SliderBase.qml \
    qml_page/module_extruder/down.svg \
    qml_page/module_extruder/title_hotend.svg \
    qml_page/module_extruder/up.svg \
    qml_page/module_fan/Function_Button.qml \
    qml_page/module_fan/SliderBase.qml \
    qml_page/module_fan/fan_close.svg \
    qml_page/module_fan/fan_full.svg \
    qml_page/module_fan/fan_half.svg \
    qml_page/module_keyboard/Caps_lock.svg \
    qml_page/module_keyboard/Cursor_Button.qml \
    qml_page/module_keyboard/General_Button.qml \
    qml_page/module_keyboard/Mode_ALL.qml \
    qml_page/module_keyboard/Mode_Number.qml \
    qml_page/module_keyboard/Result_Button.qml \
    qml_page/module_keyboard/Shift_lock.svg \
    qml_page/module_keyboard/Shift_lock_2.svg \
    qml_page/module_keyboard/Switch_Button.qml \
    qml_page/module_keyboard/Text_Dialog.qml \
    qml_page/module_keyboard/back_delete.svg \
    qml_page/module_keyboard/cancel.svg \
    qml_page/module_keyboard/checkmark.svg \
    qml_page/module_keyboard/left.svg \
    qml_page/module_keyboard/minus.svg \
    qml_page/module_keyboard/plus.svg \
    qml_page/module_keyboard/right.svg \
    qml_page/module_keyboard/space.svg \
    qml_page/module_level/Function_Button.qml \
    qml_page/module_level/Mode_ABL.qml \
    qml_page/module_level/Mode_MBL.qml \
    qml_page/module_level/Probe_Set.qml \
    qml_page/module_level/SliderBase.qml \
    qml_page/module_level/Std_Button.qml \
    qml_page/module_level/SuperSlider.qml \
    qml_page/module_level/SuperSliderButton.qml \
    qml_page/module_level/Switch_Button.qml \
    qml_page/module_level/add.svg \
    qml_page/module_level/cancel.svg \
    qml_page/module_level/checkmark.svg \
    qml_page/module_level/minus.svg \
    qml_page/module_level/point.svg \
    qml_page/module_level/settings.svg \
    qml_page/module_main/Coordinate_view_panel.qml \
    qml_page/module_main/Exit_Button.qml \
    qml_page/module_main/Exit_Dialog.qml \
    qml_page/module_main/Function_entrance.qml \
    qml_page/module_main/camera.svg \
    qml_page/module_main/extruder.svg \
    qml_page/module_main/fan.svg \
    qml_page/module_main/home_page_bottom.svg \
    qml_page/module_main/home_page_icon_user.svg \
    qml_page/module_main/level.svg \
    qml_page/module_main/move.svg \
    qml_page/module_main/print.svg \
    qml_page/module_main/settings.svg \
    qml_page/module_main/temperature.svg \
    qml_page/module_main/title_fan.svg \
    qml_page/module_main/title_heatbed.svg \
    qml_page/module_main/title_hotend.svg \
    qml_page/module_move/Function_Button.qml \
    qml_page/module_move/SliderBase.qml \
    qml_page/module_move/SuperSlider.qml \
    qml_page/module_move/SuperSliderButton.qml \
    qml_page/module_move/home_0.svg \
    qml_page/module_move/home_X.svg \
    qml_page/module_move/home_Y.svg \
    qml_page/module_move/home_Z.svg \
    qml_page/module_move/left.svg \
    qml_page/module_move/right.svg \
    qml_page/module_move/unlock.svg \
    qml_page/module_move/unlock_Disable.svg \
    qml_page/module_print/Coordinate_view_panel.qml \
    qml_page/module_print/Demo.jpeg \
    qml_page/module_print/Detail.qml \
    qml_page/module_print/Function_Button.qml \
    qml_page/module_print/LocalList.qml \
    qml_page/module_print/Menu.qml \
    qml_page/module_print/Printing_camera.qml \
    qml_page/module_print/Printing_control.qml \
    qml_page/module_print/Printing_preview.qml \
    qml_page/module_print/Printing_zStep.qml \
    qml_page/module_print/Submodule.qml \
    qml_page/module_print/VerticalSlider.qml \
    qml_page/module_print/HorizontalSlider.qml \
    qml_page/module_print/back.svg \
    qml_page/module_print/delete.svg \
    qml_page/module_print/enter.svg \
    qml_page/module_print/folder.svg \
    qml_page/module_print/history.svg \
    qml_page/module_print/info.svg \
    qml_page/module_print/main_page.svg \
    qml_page/module_print/menu.svg \
    qml_page/module_print/print.svg \
    qml_page/module_print/printing_icon_camera_close.svg \
    qml_page/module_print/printing_icon_camera_open.svg \
    qml_page/module_print/printing_icon_height.svg \
    qml_page/module_print/printing_icon_length.svg \
    qml_page/module_print/printing_icon_object.svg \
    qml_page/module_print/printing_icon_progress.svg \
    qml_page/module_print/printing_icon_rate.svg \
    qml_page/module_print/printing_icon_speed.svg \
    qml_page/module_print/printing_menu_adj.svg \
    qml_page/module_print/printing_menu_cam.svg \
    qml_page/module_print/printing_menu_extruder.svg \
    qml_page/module_print/printing_menu_pause.svg \
    qml_page/module_print/printing_menu_resume.svg \
    qml_page/module_print/printing_menu_stop.svg \
    qml_page/module_print/printing_menu_zStep.svg \
    qml_page/module_print/printing_zstep_down.svg \
    qml_page/module_print/printing_zstep_restore.svg \
    qml_page/module_print/printing_zstep_up.svg \
    qml_page/module_print/title_fan.svg \
    qml_page/module_print/title_heatbed.svg \
    qml_page/module_print/title_hotend.svg \
    qml_page/module_reminddialog/Mode_Dialog_One.qml \
    qml_page/module_reminddialog/Mode_Dialog_Two.qml \
    qml_page/module_reminddialog/Mode_Dialogs.qml \
    qml_page/module_reminddialog/Mode_Lock.qml \
    qml_page/module_reminddialog/Mode_Tose.qml \
    qml_page/module_reminddialog/Remind_Button.qml \
    qml_page/module_settings/Std_Button.qml \
    qml_page/module_settings/Subpage_account.qml \
    qml_page/module_settings/Subpage_language.qml \
    qml_page/module_settings/next.svg \
    qml_page/module_temperature/Function_Button.qml \
    qml_page/module_temperature/Preheat_Custom.qml \
    qml_page/module_temperature/Preheat_Custom_Editor.qml \
    qml_page/module_temperature/Preheat_Custom_Submodule.qml \
    qml_page/module_temperature/Preheat_Std.qml \
    qml_page/module_temperature/Preheat_Std_Submodule.qml \
    qml_page/module_temperature/SliderBase.qml \
    qml_page/module_temperature/SuperSlider.qml \
    qml_page/module_temperature/SuperSliderButton.qml \
    qml_page/module_temperature/add.svg \
    qml_page/module_temperature/add_Item.svg \
    qml_page/module_temperature/cancel.svg \
    qml_page/module_temperature/checkmark.svg \
    qml_page/module_temperature/cooldown.svg \
    qml_page/module_temperature/delete.svg \
    qml_page/module_temperature/delete_Disable.svg \
    qml_page/module_temperature/editor.svg \
    qml_page/module_temperature/minus.svg \
    qml_page/module_temperature/moveTop.svg \
    qml_page/module_temperature/moveTop_Disable.svg \
    qml_page/module_temperature/preheat.svg \
    qml_page/module_temperature/settings.svg \
    qml_page/module_temperature/title_heatbed.svg \
    qml_page/module_temperature/title_hotend.svg
