#ifndef GRR_CLIENT_MINICOMM_CLIENT_ACTIONS_FIND_H_
#define GRR_CLIENT_MINICOMM_CLIENT_ACTIONS_FIND_H_

#include <memory>
#include <vector>

#include "grr/client/minicomm/client_action.h"
#include "grr/client/minicomm/file_operations.h"

namespace grr {
class Find : public ClientAction {
 public:
  Find() {}

  void ProcessRequest(ActionContext* context) override;

 private:
  // A FileFilter takes a file's basename and stat result, and returns true if
  // the file should be filtered.
  typedef std::function<bool(const std::string&, const StatEntry&)> FileFilter;

  // Recurse through the directory tree beginning at path, sending a FindSpec
  // back to the server for each file or directory which is not
  // filtered. Returns true on success. In case of error, sets an error message
  // in context and returns false.
  //
  // remaining_depth: How deep to recurse, remaining_depth=1 indicates to check
  //                  the direct contents of path, remaining_depths=2 indicates
  //                  to check the direct contents of path, and the direct
  //                  contents of any subdirectories within path.
  // cross_devices: Whether to cross device boundaries while recursing.
  bool ProcessRecursive(const std::vector<FileFilter>& filters,
                        std::unique_ptr<OpenedPath> path, int remaining_depth,
                        bool cross_devices, ActionContext* context);
};
}  // namespace grr

#endif  // GRR_CLIENT_MINICOMM_CLIENT_ACTIONS_FIND_H_
