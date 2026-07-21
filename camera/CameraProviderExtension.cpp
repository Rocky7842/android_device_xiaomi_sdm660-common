/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CameraProviderExtension.h"

#include <fstream>

#define TORCH_BRIGHTNESS "/sys/devices/platform/soc/800f000.qcom,spmi/spmi-0/spmi0-03/800f000.qcom,spmi:qcom,pm660l@3:qcom,leds@d300/leds/led:torch_0/brightness"
#define TORCH_MAX_BRIGHTNESS "/sys/devices/platform/soc/800f000.qcom,spmi/spmi-0/spmi0-03/800f000.qcom,spmi:qcom,pm660l@3:qcom,leds@d300/leds/led:torch_0/max_brightness"
#define TOGGLE_SWITCH "/sys/devices/platform/soc/800f000.qcom,spmi/spmi-0/spmi0-03/800f000.qcom,spmi:qcom,pm660l@3:qcom,leds@d300/leds/led:switch_0/brightness"

/**
 * Write value to path and close file.
 */
template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
}

/**
 * Read value from the path and close file.
 */
template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    file >> result;
    return file.fail() ? def : result;
}

bool supportsTorchStrengthControlExt() {
    return true;
}

bool supportsSetTorchModeExt() {
    return false;
}

int32_t getTorchDefaultStrengthLevelExt() {
    return getTorchMaxStrengthLevelExt();
}

int32_t getTorchMaxStrengthLevelExt() {
    return get(TORCH_MAX_BRIGHTNESS, 0);
}

int32_t getTorchStrengthLevelExt() {
    return get(TORCH_BRIGHTNESS, 0);
}

void setTorchStrengthLevelExt(int32_t torchStrength, bool enabled) {
    set(TOGGLE_SWITCH, 0);
    set(TORCH_BRIGHTNESS, torchStrength);
    if (enabled)
        set(TOGGLE_SWITCH, 255);
}

void setTorchModeExt(bool enabled) {
    int32_t strength = getTorchDefaultStrengthLevelExt();
    setTorchStrengthLevelExt(enabled ? strength : 0, enabled);
}
