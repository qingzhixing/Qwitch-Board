//
// Created by qingzhixing on 2025/5/15.
//

#include "nvs_controller.hpp"

Preferences prefs;

void nvs_controller_init() {
    prefs.begin(NVS_NAMESPACE, false);
    // 首次运行时写入默认值
    if (!prefs.isKey("initialized")) {
        prefs.putBool("initialized", true);
    }
    if (!prefs.isKey("reboot_time")) {
        prefs.putShort("reboot_time", 0);
    } else {
        auto t = prefs.getShort("reboot_time");
        t++;
        prefs.putShort("reboot_time", t);
    }
    prefs.end();
}
