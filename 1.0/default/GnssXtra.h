#ifndef VENDOR_SPRD_HARDWARE_GNSS_V1_0_GNSSXTRA_H
#define VENDOR_SPRD_HARDWARE_GNSS_V1_0_GNSSXTRA_H

#include <ThreadCreationWrapper.h>
#include <vendor/sprd/hardware/gnss/1.0/IGnssXtra.h>
#include <hardware/gps.h>
#include <hidl/Status.h>

namespace vendor {
namespace sprd {
namespace hardware {
namespace gnss {
namespace V1_0 {
namespace implementation {

using ::android::hardware::gnss::V1_0::IGnssXtra;
using ::android::hardware::gnss::V1_0::IGnssXtraCallback;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;

using ::android::hardware::Return;
using ::android::hardware::Void;

using ::android::hardware::hidl_vec;
using ::android::hardware::hidl_string;
using ::android::sp;

/*
 * This interface is used by the GNSS HAL to request the framework to download XTRA data.
 * Also contains wrapper methods to allow methods from IGnssXtraCallback interface to be passed
 * into the conventional implementation of the GNSS HAL.
 */
struct GnssXtra : public IGnssXtra {
    GnssXtra(const GpsXtraInterface* xtraIface);
    ~GnssXtra();

    /*
     * Methods from ::android::hardware::gnss::V1_0::IGnssXtra follow.
     * These declarations were generated from IGnssXtra.hal.
     */
    Return<bool> setCallback(const sp<IGnssXtraCallback>& callback) override;
    Return<bool> injectXtraData(const hidl_string& xtraData) override;

    /*
     * Callback methods to be passed into the conventional GNSS HAL by the default implementation.
     * These methods are not part of the IGnssXtra base class.
     */
    static pthread_t createThreadCb(const char* name, void (*start)(void*), void* arg);
    static void gnssXtraDownloadRequestCb();

    /*
     * Holds function pointers to the callback methods.
     */
    static GpsXtraCallbacks sGnssXtraCb;

 private:
    const GpsXtraInterface* mGnssXtraIface = nullptr;
    static sp<IGnssXtraCallback> sGnssXtraCbIface;
    static std::vector<std::unique_ptr<ThreadFuncArgs>> sThreadFuncArgsList;
    static bool sInterfaceExists;
};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IGnssXtra* HIDL_FETCH_IGnssXtra(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace gnss
}  // namespace hardware
}  // namespace sprd
}  // namespace vendor

#endif  // VENDOR_SPRD_HARDWARE_GNSS_V1_0_GNSSXTRA_H
