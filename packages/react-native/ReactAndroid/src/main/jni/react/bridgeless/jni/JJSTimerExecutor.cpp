// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.

#include "JJSTimerExecutor.h"

#include <fb/fbjni.h>
#include <jni.h>

namespace facebook {
namespace react {

void JJSTimerExecutor::setTimerManager(
    std::weak_ptr<TimerManager> timerManager) {
  assert(timerManager && "`timerManager` must not be `nullptr`.");
  timerManager_ = timerManager;
}

void JJSTimerExecutor::callTimers(WritableNativeArray *timerIDs) {
  if (auto timerManager = timerManager_.lock()) {
    for (const auto &timerID : timerIDs->consume()) {
      timerManager->callTimer((uint32_t)timerID.asInt());
    }
  }
}

void JJSTimerExecutor::registerNatives() {
  registerHybrid({
      makeNativeMethod("callTimers", JJSTimerExecutor::callTimers),
  });
}

} // namespace react
} // namespace facebook
