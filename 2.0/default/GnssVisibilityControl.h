/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_HARDWARE_GNSS_VISIBILITY_CONTROL_V1_0_GNSSVISIBILITYCONTROL_H
#define ANDROID_HARDWARE_GNSS_VISIBILITY_CONTROL_V1_0_GNSSVISIBILITYCONTROL_H

#include "gnss_debug.h"

#ifdef GNSS_HIDL_DEBUG
#include "gps.h"
#else
#include <hardware/gps.h>
#endif

#include <android/hardware/gnss/visibility_control/1.0/IGnssVisibilityControl.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace gnss {
namespace visibility_control {
namespace V1_0 {
namespace implementation {

using ::android::sp;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::hardware::gnss::visibility_control::V1_0::IGnssVisibilityControlCallback;
using NfwNotification = ::android::hardware::gnss::visibility_control::V1_0::IGnssVisibilityControlCallback::NfwNotification;

struct GnssVisibilityControl : public IGnssVisibilityControl {
    GnssVisibilityControl(const GpsVisibilityControlInterface* gpsVisibilityControlIface);
    // Methods from ::android::hardware::gnss::visibility_control::V1_0::IGnssVisibilityControl
    // follow.
    Return<bool> enableNfwLocationAccess(const hidl_vec<hidl_string>& proxyApps) override;
    Return<bool> setCallback(const sp<V1_0::IGnssVisibilityControlCallback>& callback) override;

    static void noFrameworkNotifyCb(GnssNfwNotification* notification);
    static bool isInEmergencySessionCb();
    static GnssVisibilityControlCallbacks sGnssVisibilityControlCbs;

private:
    const GpsVisibilityControlInterface* mGnssVisibilityControlIface = nullptr;
    static sp<::android::hardware::gnss::visibility_control::V1_0::IGnssVisibilityControlCallback> sGnssVisibilityControlCbIface;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace visibility_control
}  // namespace gnss
}  // namespace hardware
}  // namespace android

#endif  // ANDROID_HARDWARE_GNSS_VISIBILITY_CONTROL_V1_0_GNSSVISIBILITYCONTROL_H
