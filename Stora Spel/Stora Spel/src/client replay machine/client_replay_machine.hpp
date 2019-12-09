#ifndef CLIENT_REPLAY_MACHINE_HPP_
#define CLIENT_REPLAY_MACHINE_HPP_

#include <vector>

#include "geometric_replay.hpp"

class Engine;

class ClientReplayMachine {
 private:
  GeometricReplay* primary_replay_;
  unsigned int replay_length_sec_;
  unsigned int replay_frames_per_sec_;

  std::vector<GeometricReplay*> stored_replays_;
  unsigned int selected_replay_index_;
  Engine* engine_;

 public:
  ClientReplayMachine(unsigned int in_replay_length_sec,
                      unsigned int in_frames_per_sec);
  ~ClientReplayMachine();

  void RecordFrame(entt::registry& in_registry);
  void NotifyDestroyedObject(EntityID in_id, entt::registry& in_registry);
  void StoreAndClearReplay();

  unsigned int NumberOfStoredReplays() const;
  unsigned int ReplayLength() const { return replay_length_sec_; }
  int CurrentlySelectedReplay() const;
  bool SelectReplay(unsigned int in_index);
  void ResetSelectedReplay();

  bool LoadFrame(entt::registry& in_registry);
  bool IsEmpty() { return stored_replays_.empty(); }

  void SetEngine(Engine* in_engine_ptr);
  void ReceiveGameEvent(GameEvent event);

  void ResetMachine();

  std::string GetDebugString() {
    std::string ret_str = "";

    for (unsigned int i = 0; i < this->stored_replays_.size(); i++) {
      ret_str += this->stored_replays_.at(i)->GetGeometricReplayTree();
    }

    return ret_str;
  }
};

#endif  // !CLIENT_REPLAY_MACHINE_HPP_
