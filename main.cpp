#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

// Simplify tuple of doubles to `sipcall` type
typedef std::tuple<double, double> sipcall;

/**
 * Returns the maximum number of concurrent calls from a vector of sipcall values
 *
 * @helper
 * @param {std::vector<sipcall>}  calls The calls from which to compute the max concurrent calls value
 * @returns {int} The maximum number of concurrent calls
 */
int getMaximumConcurrentCalls(std::vector<sipcall> calls) {
  int maximumConcurrentCalls = 0;
  // Container of concurrent calls currently being tracked
  std::vector<sipcall> ongoingCalls;
  // Iterate calls
  for (auto call : calls) {
    int trackedIndex = 0;
    // Stop tracking any calls that are no longer concurrent
    for (auto trackedCall : ongoingCalls) {
      if (std::get<1>(trackedCall) < std::get<0>(call)) {
        ongoingCalls.erase(ongoingCalls.begin() + trackedIndex);
      }
      trackedIndex++;
    }
    // Add current call to calls being tracked
    ongoingCalls.push_back(call);
    // Check if we have new max
    int currentConcurrentCalls = static_cast<int>(ongoingCalls.size());
    if (currentConcurrentCalls > maximumConcurrentCalls) {
      maximumConcurrentCalls = currentConcurrentCalls;
    }
  }
  return maximumConcurrentCalls;
}


/**
 * Creates a sipcall from 2 double values representing the start and end times of the call
 *
 * @helper
 * @param[in] {double} start The start time of the call
 * @param[in] {double} end The end time of the call
 * @returns {std::tuple<double, double>|sipcall} A sipcall
 */
sipcall createCall(double start, double end) {
  return std::make_tuple(start, end);
}

/**
 * Adds a sip call to a vector of sipcall values
 *
 * @helper
 * @param[in|out] {std::tuple<double, double>|sipcall} calls A vector of sipcalls to which to add a call
 * @param[in] {double} start The start time of the call
 * @param[in] {double} end The end time of the call
 */
void addCall(std::vector<sipcall> &calls, double start, double end) {
  calls.push_back(createCall(start, end));
}

// Calls are just tuples of doubles representing a start and end time 
std::vector<sipcall> calls;

int main() {
  // Add calls
  addCall(calls, 1.02, 5.20);
  addCall(calls, 3.02, 6.20);
  addCall(calls, 10.02, 12.20);
  addCall(calls, 1.02, 3.20);
  addCall(calls, 9.02, 55.20);
  addCall(calls, 4.02, 9.20);
  // Sort by start time
  std::sort(calls.begin(), calls.end(), [](sipcall a, sipcall b) {
    return std::get<0>(a) < std::get<0>(b);
  });
  // get max concurrent calls
  int maximumConcurrentCalls = getMaximumConcurrentCalls(calls);

  std::cout << "The Maximum number of Concurrent Calls is:\n"
            << maximumConcurrentCalls << std::endl;
  return 0;
}
